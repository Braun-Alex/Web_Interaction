#include "client.h"
const std::string DEFAULT_IP="127.0.0.1";
const uint16_t DEFAULT_PORT=1236;
int main()
{
    try
    {
    Client client;
    std::cout<<"Enter the message you want to send to the server"<<std::endl;
    std::string the_message;
    getline(std::cin,the_message);
    if (!client.connect(DEFAULT_IP,DEFAULT_PORT))
    {
        std::cerr<<"Connecting to the server failed!";
        return 0;
    }
    if (!client.send(the_message))
    {
        std::cerr<<"Sending the message to the server failed!";
        return 0;
    }
    std::cout<<"Answer of the server: "<<client.receive();
    client.disconnect();
    }
    catch(const std::exception &error)
    {
        std::cerr<<error.what();
    }
    return 0;
}