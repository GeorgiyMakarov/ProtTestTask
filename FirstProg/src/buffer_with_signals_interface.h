#ifndef BUFFERINTERFACE_H
#define BUFFERINTERFACE_H

#include <string>
#include <utility>

#include "../include/boost_1_81_0/boost/signals2.hpp"

class BufferWithSignalsInterface {
public:
    virtual ~BufferWithSignalsInterface() {};

    virtual std::string takeData() = 0;
    virtual void setData(const std::string& data) = 0;
    virtual void setData(std::string&& data) = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t getSize() const = 0;

    boost::signals2::signal<void()> Filled;
    boost::signals2::signal<void()> Cleared;
};

#endif // BUFFERINTERFACE_H
