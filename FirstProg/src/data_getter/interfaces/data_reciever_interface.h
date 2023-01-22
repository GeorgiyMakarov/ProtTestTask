#ifndef DATARECIEVERINTERFACE_H
#define DATARECIEVERINTERFACE_H

#include <string>
#include <iostream>

class DataRecieverInterface {
public:
    virtual ~DataRecieverInterface() {};
    virtual std::string getData() = 0;
};

#endif // DATARECIEVERINTERFACE_H
