#include "data_console_printer.h"

DataConsolePrinter::DataConsolePrinter(std::ostream& stream)
    :stream_(stream)
{
}

void DataConsolePrinter::sendData(std::string&& data) {
    stream_ << data << std::endl;
}

void DataConsolePrinter::sendData(const std::string& data) {
    stream_ << data << std::endl;
}

