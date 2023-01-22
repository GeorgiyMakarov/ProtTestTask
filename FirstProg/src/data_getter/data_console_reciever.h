#ifndef DATARECIEVERCONSOLE_H
#define DATARECIEVERCONSOLE_H

#include "interfaces/data_reciever_interface.h"

class DataConsoleReciever : public DataRecieverInterface
{
public:
    DataConsoleReciever(const std::istream& stream);
    std::string getData() override;
private:
    const std::istream& stream_;
};

#endif // DATARECIEVERCONSOLE_H
