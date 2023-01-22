#include "ascii_handler.h"

bool AsciiHandler::isDigit(char letter) {
    return (letter <= '9' && letter >= '0');
}

int AsciiHandler::getDigit(char letter)  {
    if (!isDigit(letter)) return kNotDigit;
    else return static_cast<int>(letter - '0');
}
