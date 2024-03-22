#include "queue.h"
#include "receiver.h"
#include "util.h"
#include "server.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>

int main()
{
    // create a udp socket
    std::shared_ptr<sf::UdpSocket> udpSocket = std::make_shared<sf::UdpSocket>();
    // send a message to the broadcast address
    std::string bcast = "bcast";
    sf::Socket::Status status = udpSocket->send(bcast.c_str(), bcast.size() + 1, sf::IpAddress::Broadcast, PORT + 1);
    // if status ...
    if (status != sf::Socket::Done) {
        std::cerr << "Error: Broadcast not working!\n";
    }
    // wait 1 second
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // set the udp socket to non blocking
    udpSocket->setBlocking(false);
    // receive
    sf::IpAddress serverAddress;
    unsigned short serverPort;
    std::size_t received;
    char buffer[256];
    status = udpSocket->receive(buffer, sizeof(buffer), received, serverAddress, serverPort);
    // if receive worked, we know the address for the server
    if (status = sf::Socket::Done) {
        
    }
    else {
        // if not, make a thread that runs the server
        server my_server;
        std::thread(&server::run, &my_server).detach();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        serverAddress = sf::IpAddress::getLocalAddress();
    }

    std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
    status = socket->connect(serverAddress, PORT); // use the address from the server
    if (status != sf::Socket::Done) {
        return 1;
    }
    std::cout << "Connected\n";
    Queue<std::string> queue;

    // Launch a receiver thread to receive messages from the server.
    Receiver rec(socket, queue);
    std::thread recv_thread(&Receiver::recv_loop, &rec);

    std::string s = "";
    while (1)
    {
        std::getline(std::cin, s);
        std::size_t sent;
        std::cout << "Sending: \"" << s << "\" " << s.size() + 1 << std::endl;
        // Send messages to the server
        if (socket->send(s.c_str(), s.size() + 1, sent) != sf::Socket::Done)
        {
            std::cerr << "Error sending messages to the server" << std::endl;
            return 0;
        }
    }
    recv_thread.join();
    return 0;
}
