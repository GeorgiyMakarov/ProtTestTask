#include "data_console_reciever.h"

DataConsoleReciever::DataConsoleReciever(const std::istream& stream)
    :stream_(stream)
{
}

std::string DataConsoleReciever::getData() {
    std::string str;
    std::getline(std::cin, str);
    return str;
}
