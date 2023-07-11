#pragma once
#include <iostream>
#include <string>
#include <boost/asio.hpp>
class Client
{
public:
    Client();
    bool connect(const std::string &entered_address,uint16_t entered_port);
    bool send(const std::string &entered_request);
    std::string receive();
    void disconnect();
    ~Client();
private:
    boost::asio::io_context context;
    boost::asio::ip::tcp::socket socket;
    boost::system::error_code error_code;
};