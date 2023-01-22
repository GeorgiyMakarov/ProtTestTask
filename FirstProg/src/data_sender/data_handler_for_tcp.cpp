#include "data_handler_for_tcp.h"
#include "../ascii_handler.h"

using namespace AsciiHandler;

std::string DataHandlerForTcp::handleData(std::string data) const {
    int temp = 0;
    for (auto letter : data) {
        if (isDigit(letter)) temp += getDigit(letter);
    }
    return std::to_string(temp);
}
