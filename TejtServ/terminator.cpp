#include <zinara.hpp>

#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cout << "\nUsage: terminator <ip> <port> <password>\n" << std::endl;
        return EXIT_FAILURE;
    }
    try
    {
        zinara::system_initializer sysinit;
        
        zinara::ip::tcp::socket socket;
        zinara::ip::tcp::address address(argv[1], std::atoi(argv[2]));
        zinara::ip::tcp::connector connector;
        
        connector.connect(socket, address, zinara::timeval());
        
        std::string msg;
        msg += "HALTEXEC:";
        msg += argv[3];
        msg += "\r\n";
        zinara::basic_stream_buffer<std::allocator> buffer;
        buffer.putn(msg.c_str(), msg.size());
        
        while(buffer.size() > 0)
            buffer.discard(0, socket.send(buffer));
    }
    catch(std::exception& error)
    {
        std::cout << "\nA fatal error was encountered: " << error.what() << "\n" << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
