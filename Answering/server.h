#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
class Server
{
public:
    Server(boost::asio::io_context &io_context,uint16_t port);
    void Async_Process();
private:
    const std::string KEY_WORD="hello";
    boost::asio::io_context &io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
};
class Session: public std::enable_shared_from_this<Session>
{
public:
    explicit Session(boost::asio::ip::tcp::socket &&socket);
    void Process(const std::string &KEY_WORD);
private:
    boost::asio::ip::tcp::socket socket;
    std::string the_request;
};