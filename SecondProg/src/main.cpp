#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <list>

#include "../include/boost_1_81_0/boost/asio.hpp"
#include "../include/boost_1_81_0/boost/bind.hpp"

using namespace std;

using namespace boost::asio::ip;
using  boost::asio::ip::tcp;

void parseData(std::list<std::string> output_list, const std::string& s) {
    output_list.clear();
    if (s.empty()) return;
    auto it_first = s.begin();
    while (it_first != s.end()) {
        auto it_last = std::find(it_first, s.end(), '\n');
        output_list.push_back(std::string(it_first, it_last));
        it_first = it_last != s.end() ? it_last + 1 : s.end();
    }
}

void printResult(const std::string& str) {
        int res = std::stoi(str);
        if (res % 32 == 0 && res >= 100) {
            std::cout << res << std::endl;
            return;
        }
    std::cout << "incorrect number" << std::endl;
}

int main() {
    boost::asio::io_service io;
    tcp::endpoint endpoint(address::from_string("127.0.0.1"), 6543);
    tcp::acceptor acceptor(io, endpoint);
    boost::system::error_code ec;
    tcp::socket socket(io);
    std::string data;
    std::list<std::string> list_of_nums;

    while(true) {
        acceptor.accept(socket);
        while(true) {
            data.clear(); data.resize(16); list_of_nums.clear();
            size_t size = socket.read_some(boost::asio::buffer(data, 16), ec);
            if (!ec) {
                data.resize(size);
                printResult(data);
            }
            else {
                socket.close();
                break;
            }
        }
    }
    return 0;
}


