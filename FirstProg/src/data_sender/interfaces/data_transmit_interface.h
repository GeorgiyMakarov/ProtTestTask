#ifndef DATA_PRINTER_INTERFACE_H
#define DATA_PRINTER_INTERFACE_H

#include <string>

class DataTransmitInterface {
public:
    virtual void sendData(const std::string& data) = 0;
    virtual void sendData(std::string&& data) = 0;

    virtual ~DataTransmitInterface() {}
};

#endif // DATA_PRINTER_INTERFACE_H
