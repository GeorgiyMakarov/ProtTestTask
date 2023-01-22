#ifndef DATAHANDLERFORTCP_H
#define DATAHANDLERFORTCP_H

#include "../data_handler_interface.h"

class DataHandlerForTcp : public DataHandlerInterface
{
public:
    std::string handleData(std::string data) const override;
};

#endif // DATAHANDLERFORTCP_H
