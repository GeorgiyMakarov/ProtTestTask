#include "data_handler.h"
#include "../ascii_handler.h"

#include <algorithm>
#include <cassert>

using namespace AsciiHandler;

DataHandler::DataHandler(std::string replacer, int capacity)
    :replacer_(replacer)
{
    initBuff(capacity);
}

std::string DataHandler::handleData(std::string data) const {
    if (!checkData(data)) return std::string();

    std::sort(data.begin(), data.end(), [](char lhs, char rhs) {
        return lhs > rhs;
    });

    return getStringWithoutEvenNumbers(data);
}

void DataHandler::initBuff(int capacity) const {
    buff_.resize(capacity);
    for (auto item : buff_) {
        item.reserve(2);
    }
    buff_size_ = 0;
}

void DataHandler::clearBuff() const {
    for (int i = 0; i < buff_size_; ++i) {
        buff_[i].clear();
    }
    buff_size_ = 0;
}

bool DataHandler::checkData(const std::string &data) const {
    if (data.size() > 64) return false;
    for (const auto& letter : data) {
        if (!isDigit(letter)) return false;
    }
    return true;
}

std::string DataHandler::getStringWithoutEvenNumbers(const std::string& data) const {
    /*
        Обоснование запутанного алгоритма:

        Если проходить по строке с 0 индекса и заменять символ четного числа
        двумя символами KB, сложность такого алгоритма составит O(N^2):
        (всего N элементов, для каждого элемента может потребоваться операция вставки сложностью N)

        Используемый здесь алгоритм состоит из трех частей:
        1)Очистить буффер (сложность N)
        2)Заполнить буффер символами из строки, заменяя четные символы на KB (сложность 2N)
        3)Заполнить результирующую строку из буффера (сложность N)
        Итог: Сложность алгоритма O(4N)

        Место под буффер (вектор и строки из которых он состоит) заранее зарезервировано
        максимальным количеством элементов, которые могут потребоваться.
    */

    clearBuff();
    int counter = fillBufferFromSortedString(data);
    return buildStringFromBuff(counter);
}

int DataHandler::fillBufferFromSortedString(const std::string &data) const {
    buff_size_ = data.size();
    int counter = 0;
    //переписываем в элементы буффера нечетные числа, вместо четных записываем KB
    //считаем количество символов, из которых будет состоять результирующая строка в counter
    for (int i = 0; i < data.size(); ++i) {
        if ((getDigit(data[i])) % 2 == 0) {
            buff_[i] = replacer_;
            counter += 2;
        }
        else {
            buff_[i].push_back(data[i]);
            ++counter;
        }
    }

    return counter;
}

std::string DataHandler::buildStringFromBuff(int new_string_size) const {
    //создаем строку для вывода, резервируем в ней место под нужное количество элементов
    std::string result;
    result.reserve(new_string_size);
    int counter = 0;
    //заполняем результирующую строку из буффера
    for (const auto& element : buff_) {
        if (counter >= buff_size_) break;
        for (const auto& letter : element) {
            result.push_back(letter);
        }
        ++counter;
    }
    return result;
}
