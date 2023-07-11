#include "server.h"
Session::Session(boost::asio::ip::tcp::socket &&socket):socket(std::move(socket)) {}
void Session::Process(const std::string &KEY_WORD)
{
    socket.wait(socket.wait_read);
    the_request.resize(socket.available());
    boost::asio::read(socket,boost::asio::buffer(the_request));
    if (the_request==KEY_WORD) the_request="world";
    boost::asio::write(socket,boost::asio::buffer(the_request));
}
Server::Server(boost::asio::io_context &io_context,uint16_t port):io_context(io_context),
acceptor(io_context,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port)) {}
void Server::Async_Process()
{
    socket.emplace(io_context);
    acceptor.async_accept(*socket, [&] (boost::system::error_code error)
    {
        std::make_shared<Session>(std::move(*socket))->Process(KEY_WORD);
        Async_Process();
    });
}