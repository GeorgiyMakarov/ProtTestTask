#ifndef BUFFERWITHSIGNAL_H
#define BUFFERWITHSIGNAL_H

#include "../include/boost_1_81_0/boost/signals2.hpp"
#include "buffer_with_signals_interface.h"

#include <mutex>
#include <iostream>

namespace BufferWithSignalsEmptyParams {
    //максимальный размер итоговой строки
    //(содержит 64 элемента, все элементы четные)
    const int capacity = 64 * 2;
}

class BufferWithSignals : public BufferWithSignalsInterface
{
public:
    BufferWithSignals(int capacity = BufferWithSignalsEmptyParams::capacity);
    BufferWithSignals(const std::string& data, int capacity = BufferWithSignalsEmptyParams::capacity);
    BufferWithSignals(std::string&& data, int capacity = BufferWithSignalsEmptyParams::capacity);

    std::string takeData() override;
    void setData(const std::string& data) override;
    void setData(std::string&& data) override;
    bool isEmpty() const override;
    size_t getSize() const override;

private:
    std::string data_;
    mutable std::mutex mutex_;

    void reserveSpace(int empty_capacity, int data_size = 0);

    //невиртуальные налоги setData для использования в конструкторе
    void internalSetData(const std::string& data);
    void internalSetData(std::string&& data);
};

#endif // BUFFERWITHSIGNAL_H
