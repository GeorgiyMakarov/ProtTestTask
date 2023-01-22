#ifndef DATAGETTER_H
#define DATAGETTER_H

#include <memory>
#include <mutex>

#include "../buffer_with_signals_interface.h"
#include "../data_handler_interface.h"
#include "interfaces/data_reciever_interface.h"

class DataGetter
{
public:
    DataGetter();
    DataGetter(std::shared_ptr<BufferWithSignalsInterface> buffer,
               std::shared_ptr<DataHandlerInterface> handler,
               std::shared_ptr<DataRecieverInterface> reciever);
    void setBuffer(std::shared_ptr<BufferWithSignalsInterface> buffer);
    void setHandler(std::shared_ptr<DataHandlerInterface> handler);
    void setReciever(std::shared_ptr<DataRecieverInterface> reciever);

    bool checkBuffer(void) const;
    bool checkHandler(void) const;
    bool checkReciever(void) const;
    bool checkWorking(void) const;

    void start(void);
    void stop(void);
private:
    std::weak_ptr<BufferWithSignalsInterface> buffer_;
    std::weak_ptr<DataHandlerInterface> handler_;
    std::weak_ptr<DataRecieverInterface> reciever_;

    mutable std::mutex mutex_;
    bool is_started_;
    bool request_for_stop_;

    void work(void);
};

#endif // DATAGETTER_H
