#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

struct BuzzClient
{
    boost::asio::io_service io_service;
    tcp::resolver resolver;
    tcp::resolver::query query;
    tcp::socket m_socket;
    bool bConnected = false;

    BuzzClient()
        : resolver(io_service),
          query(tcp::v4(), "raspi3-PK", "1337"),  // Note: change host + port as needed.
          m_socket(io_service)
    {
        tcp::resolver::iterator iterator = resolver.resolve(query);
        tcp::resolver::iterator end;
        if(iterator != end)
        {
            boost::asio::connect(m_socket, iterator);
            bConnected = true;
        } else
            std::cout << " invalid connection parameters!" << std::endl;
    }

    bool isValid() const { return bConnected; }

    void turnON()
    {
        if(!isValid()) return;
        std::string s = "LED ON\r\n";
        boost::asio::write(m_socket, boost::asio::buffer(s.data(), s.size()));
    }

    void turnOFF()
    {
        if(!isValid()) return;
        std::string s = "LED OFF\r\n";
        boost::asio::write(m_socket, boost::asio::buffer(s.data(), s.size()));
    }
};

int main(int ac, char* av[])
{
    BuzzClient  bc;

    for(int k=0; k<3; k++)
    {
        bc.turnON();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        bc.turnOFF();    
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
