#include "buffer_with_signals.h"

BufferWithSignals::BufferWithSignals(int capacity)
{
    data_.reserve(capacity);
}

BufferWithSignals::BufferWithSignals(const std::string& data, int capacity) {
    reserveSpace(capacity, data.size());
    internalSetData(data);
}

BufferWithSignals::BufferWithSignals(std::string&& data, int capacity) {
    reserveSpace(capacity, data.size());
    internalSetData(data);
}

std::string BufferWithSignals::takeData() {
    std::lock_guard<std::mutex> lock(mutex_);
    std::string temp = std::move(data_);
    data_.clear();
    return std::move(temp);
}

void BufferWithSignals::setData(const std::string& data) {
    mutex_.lock();
    internalSetData(data);
    mutex_.unlock();
    Filled();
}

void BufferWithSignals::setData(std::string &&data) {
//    std::lock_guard<std::mutex> lock(mutex_);
    mutex_.lock();
    internalSetData(std::move(data));
    mutex_.unlock();
    Filled();
}

bool BufferWithSignals::isEmpty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.empty();
}

size_t BufferWithSignals::getSize() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.size();
}

void BufferWithSignals::reserveSpace(int empty_capacity, int data_size) {
    data_.reserve(std::max(empty_capacity, data_size));
}

void BufferWithSignals::internalSetData(std::string &&data) {
    data_ = data;
}

void BufferWithSignals::internalSetData(const std::string &data) {
    data_ = data;
}
