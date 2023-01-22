#ifndef USERDATAHANDLER_H
#define USERDATAHANDLER_H

#include <iostream>
#include <vector>
#include <string>

#include "../data_handler_interface.h"

namespace  UserDataHandlerEmptyParams {
    const int buff_capacity = 64;
};

class DataHandler : public DataHandlerInterface
{
public:
    DataHandler(std::string replacer, int capacity = UserDataHandlerEmptyParams::buff_capacity);
    std::string handleData(std::string data) const override;
private:
    mutable std::vector<std::string> buff_;
    mutable size_t buff_size_;
    const std::string replacer_;

    void initBuff(int capacity) const;
    void clearBuff() const;
    bool checkData(const std::string& data) const;
    std::string getStringWithoutEvenNumbers(const std::string& data) const;
    //подфункции для getStringWithoutEvenNumbers:
    int fillBufferFromSortedString(const std::string& data) const;
    std::string buildStringFromBuff(int new_string_size = 0) const;
};

#endif // USERDATAHANDLER_H
