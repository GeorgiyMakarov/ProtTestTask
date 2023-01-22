#include "data_tcp_transmitter.h"

#include <iostream>

#include "../../include/boost_1_81_0/boost/bind.hpp"
#include "../../include/boost_1_81_0/boost/asio/buffer.hpp"

using boost::asio::ip::tcp;

DataTcpTransmitter::DataTcpTransmitter(int port)
    :io_service_()
    ,endpoint_(tcp::v4(), port)
    ,socket_(io_service_)
    ,deadline_timer_(io_service_)
    ,handler_()
{
}

DataTcpTransmitter::DataTcpTransmitter(int port,
                                       std::shared_ptr<DataHandlerInterface> handler)
    :io_service_()
    ,endpoint_(tcp::v4(), port)
    ,socket_(io_service_)
    ,deadline_timer_(io_service_)
    ,handler_(handler)
{
}

void DataTcpTransmitter::sendData(const std::string &data) {
    //не успел достичь адекватной работы буффера на отправку, поэтому он очищается при каждой отправке
    if (!queue_.empty()) queue_.pop();
    if (!handler_.expired() && handler_.lock().get() != nullptr) {
        queue_.push(std::move(handler_.lock()->handleData(data)));
    }
    else {
        queue_.push(data);
    }

    tryConnecting();
}

void DataTcpTransmitter::sendData(std::string &&data) {
    //не успел достичь адекватной работы буффера на отправку, поэтому он очищается при каждой отправке
    if (!queue_.empty()) queue_.pop();
    if (!handler_.expired() && handler_.lock().get() != nullptr) {
        queue_.push(std::move(handler_.lock()->handleData(std::move(data))));
    }
    else {
        queue_.push(data);
    }

    tryConnecting();
}

void DataTcpTransmitter::tryConnecting() {
    io_service_.reset();
    startDeadlineTimer();
    socket_.async_connect(endpoint_, boost::bind(&DataTcpTransmitter::handleNewConnection, this, boost::asio::placeholders::error));
    io_service_.run();
}

void DataTcpTransmitter::trySending() {
    if (!queue_.empty()) {
        socket_.async_write_some(boost::asio::buffer(queue_.back()), boost::bind(&DataTcpTransmitter::handleDataSended, this, ec_));
    }
    else {
        closeConnection();
    }
}

void DataTcpTransmitter::handleNewConnection(const boost::system::error_code& err) {
    if (!err) {
        trySending();
    }
    else {
        closeConnection();
    }
}

void DataTcpTransmitter::handleDataSended(const boost::system::error_code& err) {
    stopDeadlineTimer();
    if (!err) {
        queue_.pop();
        trySending();
    }
    else {
        closeConnection();
    }
}

void DataTcpTransmitter::checkDeadline() {
}

void DataTcpTransmitter::startDeadlineTimer() {
    stopDeadlineTimer();
    setDeadlineTimer(1000);
    deadline_timer_.async_wait(boost::bind(&DataTcpTransmitter::checkDeadline, this));
}

void DataTcpTransmitter::stopDeadlineTimer() {
    deadline_timer_.expires_at(boost::posix_time::pos_infin);
    deadline_timer_.cancel();
}

void DataTcpTransmitter::setDeadlineTimer(int time) {
    deadline_timer_.expires_from_now(boost::posix_time::milliseconds(time));
}

void DataTcpTransmitter::closeConnection() {
    stopDeadlineTimer();
    socket_.close();
}
