#include <iostream>
#include <memory>

#include "../include/boost_1_81_0/boost/asio.hpp"
#include "../include/boost_1_81_0/boost/bind.hpp"

#include "data_getter/data_getter.h"
#include "data_getter/data_console_reciever.h"
#include "data_getter/data_handler.h"
#include "buffer_with_signals.h"
#include "data_sender/data_sender.h"
#include "data_sender/data_console_printer.h"
#include "data_sender/data_tcp_transmitter.h"
#include "data_sender/data_handler_for_tcp.h"

using namespace std;

int main()
{
    //инициализация общего буффера
    std::shared_ptr<BufferWithSignalsInterface> data_buffer = std::make_shared<BufferWithSignals>();
    //инициализация потока, получающего данные от пользователя
    std::shared_ptr<DataRecieverInterface> data_reciever = std::make_shared<DataConsoleReciever>(std::cin);
    std::shared_ptr<DataHandlerInterface> data_handler = std::make_shared<DataHandler>(std::string("KB"));
    std::unique_ptr<DataGetter> data_getter = std::make_unique<DataGetter>(data_buffer, data_handler, data_reciever);
    //запустить поток получения данных от пользователя
    data_getter->start();
    //инициализация потока, отправляющего данные
    std::shared_ptr<DataTransmitInterface> data_printer = std::make_shared<DataConsolePrinter>(std::cout);
    std::shared_ptr<DataHandlerInterface> data_handler_tcp = std::make_shared<DataHandlerForTcp>();
    std::shared_ptr<DataTransmitInterface> data_tcp_sender = std::make_shared<DataTcpTransmitter>(6543, data_handler_tcp);
    std::unique_ptr<DataSender> data_sender = std::make_unique<DataSender>(data_buffer);
    data_sender.get()->connectTransmitter(data_printer);
    data_sender.get()->connectTransmitter(data_tcp_sender);

    while (true) {
    }

    return 0;
}


