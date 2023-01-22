#ifndef DATAHANDLERINTERFACE_H
#define DATAHANDLERINTERFACE_H

#include <string>

class DataHandlerInterface {
public:
    virtual ~DataHandlerInterface() {};
    virtual std::string handleData(std::string data) const = 0;
};

#endif // DATAHANDLERINTERFACE_H
