cmake_minimum_required(VERSION 3.5)

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREAD ON)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (PROJECT_NAME SecondProg)

set (SHARED_DIRECTORY src)

#set (SHARED_HEADERS ${SHARED_DIRECTORY}/ascii_handler.h
#                    ${SHARED_DIRECTORY}/buffer_with_signals.h
#                    ${SHARED_DIRECTORY}/buffer_with_signals_interface.h
#                    ${SHARED_DIRECTORY}/data_handler_interface.h
#                    )

#set (SHARED_SOURCES ${SHARED_DIRECTORY}/main.cpp
#                    ${SHARED_DIRECTORY}/buffer_with_signals.cpp
#                    ${SHARED_DIRECTORY}/ascii_handler.cpp
#                    )

set (SHARED_SOURCES ${SHARED_DIRECTORY}/main.cpp
                     )

#set (SENDER_DIRECTORY ${SHARED_DIRECTORY}/data_sender)

#set (SENDER_HEADERS ${SENDER_DIRECTORY}/interfaces/data_transmit_interface.h
#                    ${SENDER_DIRECTORY}/data_tcp_transmitter.h
#                    ${SENDER_DIRECTORY}/data_sender.h
#                    ${SENDER_DIRECTORY}/data_console_printer.h
#                    ${SENDER_DIRECTORY}/data_handler_for_tcp.h
#                    )
			  
#set (SENDER_SOURCES ${SENDER_DIRECTORY}/data_tcp_transmitter.cpp
#                    ${SENDER_DIRECTORY}/data_sender.cpp
#                    ${SENDER_DIRECTORY}/data_console_printer.cpp
#                    ${SENDER_DIRECTORY}/data_handler_for_tcp.cpp
#                    )

#set (GETTER_DIRECTORY ${SHARED_DIRECTORY}/data_getter)

#set (GETTER_HEADERS ${GETTER_DIRECTORY}/interfaces/data_reciever_interface.h
#                    ${GETTER_DIRECTORY}/data_getter.h
#                    ${GETTER_DIRECTORY}/data_console_reciever.h
#                    ${GETTER_DIRECTORY}/data_handler.h
#                    )

#set (GETTER_SOURCES ${GETTER_DIRECTORY}/data_getter.cpp
#                    ${GETTER_DIRECTORY}/data_console_reciever.cpp
#                    ${GETTER_DIRECTORY}/data_handler.cpp
#                   )

set (HEADERS ${SHARED_HEADERS}
#             ${SENDER_HEADERS}
#             ${GETTER_HEADERS}
#             )
    )

set (SOURCES ${SHARED_SOURCES}
    )
#             ${SENDER_SOURCES}
#             ${GETTER_SOURCES}
#             )

project(${PROJECT_NAME})

include_directories("include/boost_1_81_0")

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

#LINK_DIRECTORIES("include/boost_1_81_0/boost/libs")

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${HEADERS}
                               ${SOURCES}
                               )

target_link_libraries(${PROJECT_NAME} Threads::Threads)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

