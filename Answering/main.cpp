#include "server.h"
const std::uint16_t DEFAULT_PORT=1236;
int main()
{
    boost::asio::io_context io_context;
    try
    {
    std::thread server_thread([&]()
    {
    std::cout<<"Server with IP 127.0.0.1 and port "<<DEFAULT_PORT<<
    " waits for new clients... Enter \"Stop\" to stop accepting connections by the server"<<std::endl;
    Server server(io_context, DEFAULT_PORT);
    server.Async_Process();
    io_context.run();
    });
    server_thread.detach();
    std::string COMMAND;
    std::getline(std::cin,COMMAND);
    while (COMMAND!="Stop")
    {
        std::cerr<<"Entered incorrect command. Enter \"Stop\" to stop accepting connections by the server"
        <<std::endl;
        std::getline(std::cin,COMMAND);
    }
    io_context.stop();
    std::cout<<"Server has been successfully disabled";
    }
    catch(std::exception &error)
    {
        std::cerr<<error.what();
        if (!io_context.stopped()) io_context.stop();
    }
    return 0;
}