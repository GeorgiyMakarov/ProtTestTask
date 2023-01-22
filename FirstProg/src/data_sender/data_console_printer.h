#ifndef DATACONSOLEPRINTER_H
#define DATACONSOLEPRINTER_H

#include <iostream>

#include "interfaces/data_transmit_interface.h"


class DataConsolePrinter : public DataTransmitInterface
{
public:
    DataConsolePrinter(std::ostream& stream);
    void sendData(std::string&& data) override;
    void sendData(const std::string& data) override;
private:
    std::ostream& stream_;
};

#endif // DATACONSOLEPRINTER_H
