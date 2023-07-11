#include "client.h"
Client::Client():socket(context) {}
bool Client::connect(const std::string &entered_address,uint16_t entered_port)
{
    if (socket.is_open()) socket.close(error_code);
    socket.connect(boost::asio::ip::tcp::
                       endpoint(boost::asio::ip::make_address(entered_address,error_code),entered_port),
                       error_code);
    return !static_cast<bool>(error_code);
}
bool Client::send(const std::string &entered_request)
{
    if (!error_code&&socket.is_open()) boost::asio::write(socket,boost::asio::buffer(entered_request),
                                                                     error_code);
    return !static_cast<bool>(error_code);
}
std::string Client::receive()
{
    socket.wait(socket.wait_read,error_code);
    size_t the_bytes=socket.available(error_code);
    if (!error_code)
    {
        std::string the_answer;
        the_answer.resize(the_bytes);
        boost::asio::read(socket,boost::asio::buffer(the_answer),error_code);
        return the_answer;
    }
    return "Problem with the socket has been found";
}
void Client::disconnect()
{
    if (socket.is_open()) socket.close(error_code);
}
Client::~Client()
{
    disconnect();
}