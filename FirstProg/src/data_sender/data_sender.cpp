#include <thread>
#include "data_sender.h"

DataSender::DataSender(std::shared_ptr<BufferWithSignalsInterface> buffer)
    :buffer_(buffer)
{
    createThread();
}

DataSender::DataSender(std::shared_ptr<BufferWithSignalsInterface> buffer,
                       std::shared_ptr<DataTransmitInterface> transmitter)
    :buffer_(buffer)
{
    transmitters_.push_back(transmitter);
    createThread();
}

DataSender::DataSender(std::shared_ptr<BufferWithSignalsInterface> buffer,
                       std::list<std::shared_ptr<DataTransmitInterface>> transmitters)
    :buffer_(buffer)
{
    //добавляем передатчики
    for (auto& transmitter : transmitters) {
        connectTransmitterIfNotDuplicate(transmitter);
    }
    createThread();
}

void DataSender::addNewTask() {
    io_service_.post(boost::bind(&DataSender::handleTask, this));
}

void DataSender::handleTask() {
    std::lock_guard lock(mutex_);
    if (!buffer_.expired()) {
        auto buffer = buffer_.lock();
        if (!buffer->isEmpty()) data_ = buffer_.lock()->takeData();
    }
    for (auto& transmitter : transmitters_) {
        if (!transmitter.expired()) {
            auto tr = transmitter.lock();
            if (tr.get()) {
                tr->sendData(data_);
            }
        }
    }
}

void DataSender::waitForNewTask() {
    while (true) {
        io_service_.restart();
        io_service_.run();
    }
}

void DataSender::connectBufferSignal() {
    if (!buffer_.expired()) {
        auto buffer = buffer_.lock();
        if (buffer) buff_connection_ = buffer->Filled.connect(boost::bind(&DataSender::addNewTask, this));
    }
}

void DataSender::disconnectBufferSignal() {
    if (buff_connection_.connected()) buff_connection_.disconnect();
}

void DataSender::connectTransmitter(std::shared_ptr<DataTransmitInterface> transmitter) {
    std::lock_guard lock(mutex_);
    connectTransmitterIfNotDuplicate(transmitter);
}

void DataSender::disconnectTransmitter(std::shared_ptr<DataTransmitInterface> transmitter) {
    std::lock_guard lock(mutex_);
    auto it = find_if(transmitters_.begin(),
                      transmitters_.end(),
                      [&](auto& item) {return item.lock().get() == transmitter.get();});
    if (it != transmitters_.end()) transmitters_.erase(it);
}

void DataSender::createThread() {
    connectBufferSignal();
    std::thread t(&DataSender::waitForNewTask, this);
    t.detach();
}

void DataSender::connectTransmitterIfNotDuplicate(std::shared_ptr<DataTransmitInterface>& new_transmitter) {
    auto it = std::find_if(transmitters_.begin(),
                           transmitters_.end(),
                           [&](auto& item) {return item.lock().get() == new_transmitter.get();});
    if (it == transmitters_.end()) transmitters_.push_back(new_transmitter);
}

