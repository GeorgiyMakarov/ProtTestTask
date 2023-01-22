#include "data_getter.h"
#include <thread>

DataGetter::DataGetter()
    :is_started_(false)
    ,request_for_stop_(false)
{
}

DataGetter::DataGetter(std::shared_ptr<BufferWithSignalsInterface> buffer,
           std::shared_ptr<DataHandlerInterface> handler,
           std::shared_ptr<DataRecieverInterface> reciever)
    :buffer_(buffer)
    ,handler_(handler)
    ,reciever_(reciever)
    ,is_started_(false)
    ,request_for_stop_(false)
{
}

void DataGetter::setBuffer(std::shared_ptr<BufferWithSignalsInterface> buffer) {
    std::lock_guard<std::mutex> lock(mutex_);
    buffer_ = buffer;
}

void DataGetter::setHandler(std::shared_ptr<DataHandlerInterface> handler) {
    std::lock_guard<std::mutex> lock(mutex_);
    handler_ = handler;
}

void DataGetter::setReciever(std::shared_ptr<DataRecieverInterface> reciever) {
    std::lock_guard<std::mutex> lock(mutex_);
    reciever_ = reciever;
}

bool DataGetter::checkBuffer() const {
    return !buffer_.expired();
}

bool DataGetter::checkHandler() const {
    return !handler_.expired();
}

bool DataGetter::checkReciever() const {
    return !reciever_.expired();
}

bool DataGetter::checkWorking() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return is_started_;
}

void DataGetter::start() {
    std::lock_guard<std::mutex> lock(mutex_);
    std::thread t(&DataGetter::work, this);
    t.detach();
}

void DataGetter::stop() {
    request_for_stop_ = true;
}

void DataGetter::work() {
    is_started_ = true;
    while(!request_for_stop_) {
        if (checkBuffer() && checkHandler() && checkReciever()) {
            auto reciever = reciever_.lock();
            auto handler = handler_.lock();
            auto buffer = buffer_.lock();
            std::string data = reciever->getData();
            data = handler->handleData(data);
            if (!data.empty()) {
                if(!buffer->isEmpty()) {std::cout << "data lost" << std::endl;}
                buffer->setData(std::move(data));
            }
        }
        else {
            stop();
            //handle error?
        }
    }
    request_for_stop_ = false;
    is_started_ = false;
}
