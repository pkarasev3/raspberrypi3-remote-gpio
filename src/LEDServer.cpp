#include <cstdio>
#include <iostream>
#include <boost/asio.hpp>

#if defined(BUILDING_FOR_RASPI)
    #include <wiringPi.h>
#endif

using boost::asio::ip::tcp;

#if defined(BUILDING_FOR_RASPI)
void writeHigh(int arg)
{
    digitalWrite (arg,  HIGH);
}
void writeLow(int arg)
{
    digitalWrite (arg,  LOW);
}
#else
void writeHigh(int){}
void writeLow(int){}
#endif


int main(int argc, char** argv)
{
   
        boost::asio::io_service io_service;

        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1337));

#if defined(BUILDING_FOR_RASPI)
        wiringPiSetup () ;
        pinMode (0, OUTPUT) ;
#endif

        for (;;)
        {
            try
            {
                tcp::socket socket(io_service);
                acceptor.accept(socket);

                boost::asio::streambuf b;
                boost::system::error_code error_code;

                size_t bytesRead = 0;
                do
                {
                    bytesRead = boost::asio::read_until(socket, b, "\r\n");
                    std::istream reader(&b);

                    std::string input;
                    std::getline(reader, input);

                    std::string command = input.substr(0, input.length() - 1);
                    std::cout << "Received command: " << command << std::endl;
                    if (command.compare("LED ON") == 0)
                    {
                        std::cout << "LED going high" << std::endl;
                        writeHigh(0);
                    }

                    if (command.compare("LED OFF") == 0)
                    {
                        std::cout << "LED going low" << std::endl;
                        writeLow(0);
                    }
                        
                } while (bytesRead > 0);
            }
            catch (std::exception& e)
            {
                std::cerr << "Exception thrown but regenerating" << std::endl;
            }
        }
    

    return 0;
}
