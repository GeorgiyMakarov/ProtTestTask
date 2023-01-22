#ifndef DATATCPSENDER_H
#define DATATCPSENDER_H
#include <queue>
#include <memory>

#include "interfaces/data_transmit_interface.h"
#include "../data_handler_interface.h"
#include "../../include/boost_1_81_0/boost/asio/deadline_timer.hpp"

#include "../../include/boost_1_81_0/boost/asio.hpp"

class DataTcpTransmitter : public DataTransmitInterface
{
public:
    DataTcpTransmitter(int port);
    DataTcpTransmitter(int port, std::shared_ptr<DataHandlerInterface> handler);
    void sendData(const std::string& data) override;
    void sendData(std::string&& data) override;
    void setHandler(std::shared_ptr<DataHandlerInterface> handler);
private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::endpoint endpoint_;
    boost::asio::ip::tcp::socket socket_;

    std::queue<std::string> queue_;
    boost::system::error_code ec_;

    std::string temp_;


    std::weak_ptr<DataHandlerInterface> handler_;

    boost::asio::deadline_timer deadline_timer_;

    void tryConnecting();
    void trySending(void);
    void handleNewConnection(const boost::system::error_code& err);
    void handleDataSended(const boost::system::error_code& err);
    void checkDeadline(void);
    void startDeadlineTimer(void);
    void stopDeadlineTimer(void);
    void setDeadlineTimer(int time);
    void closeConnection(void);
};

#endif // DATATCPSENDER_H
