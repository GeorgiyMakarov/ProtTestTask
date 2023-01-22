#ifndef DATASENDER_H
#define DATASENDER_H

#include <memory>
#include <list>

#include "../../include/boost_1_81_0/boost/asio.hpp"

#include "../buffer_with_signals_interface.h"
#include "data_console_printer.h"

class DataSender
{
public:
    DataSender() = delete;
    //конструктор с подключением буффера
    DataSender(std::shared_ptr<BufferWithSignalsInterface> buffer);
    //конструктор с использованием одного буффера и одного передатчика
    DataSender(std::shared_ptr<BufferWithSignalsInterface> buffer,
               std::shared_ptr<DataTransmitInterface> transmitter);
    //конструктор с использованием одного буффера и множества передатчиков
    DataSender(std::shared_ptr<BufferWithSignalsInterface> buffer,
               std::list<std::shared_ptr<DataTransmitInterface>> transmitters);
    //подключение буффера к уже созданному объекту
//    void connectBuffer(std::shared_ptr<BufferWithSignalsInterface> buffer);
    //отсоединить текущий буффер
//    void disconnectBuffer(void);
    //подключить дополнительный передатчик к уже созданному объекту
    void connectTransmitter(std::shared_ptr<DataTransmitInterface> transmitter);
    //отключить один из передатчиков уже созданного объекта
    void disconnectTransmitter(std::shared_ptr<DataTransmitInterface> transmitter);

private:
    std::weak_ptr<BufferWithSignalsInterface> buffer_;
    boost::signals2::connection buff_connection_;

    std::list<std::weak_ptr<DataTransmitInterface>> transmitters_;

    boost::asio::io_service io_service_;

    std::string data_;

    std::mutex mutex_;

    void addNewTask(); //новая задача (вызывается при появлении данных в общем буффере или при появлении соединения с второй программой
    void handleTask(); //обработать задачу
    void waitForNewTask(); //ожидание новой задачи в поток
    void connectBufferSignal(); //соединения сигнала буффера к вызову обработчика поткоа
    void disconnectBufferSignal(); //отсоединение сигнала буффера
    void createThread(); //создание потока
    void connectTransmitterIfNotDuplicate(std::shared_ptr<DataTransmitInterface>& new_transmitter); //подсоединить передатчик если еще не подсоединен

};

#endif // DATASENDER_H
