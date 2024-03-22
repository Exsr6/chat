#include "accepter.h"
#include "queue.h"
#include "list.h"
#include "receiver.h"
#include "util.h"
#include "server.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>


int server::run()
{
    Queue<std::string> queue;
    List<std::shared_ptr<sf::TcpSocket>> sockets;
    // Launch the udprecvloop thread
    std::thread udprecvThread(&server::udpRecvLoop, this);
    udprecvThread.detach();
    // Launch an accepter thread.
    std::thread accepterThread(Accepter(queue, sockets));
    while(1)
    {
        std::string s = queue.pop(); // s is our message
        std::cout << "Main read: \"" << s << "\"\n";
        // Send to all in sockets. Be careful to synchronise.
        // 1. Define a lambda that sends one message to one socket

        auto send_to_one = [&s](std::shared_ptr<sf::TcpSocket> socket){
            std::size_t sent = 0;
            if (socket->send(s.c_str(), s.size() + 1, sent) != sf::Socket::Done)
            {
                std::cerr << "Error Sending message to socket\n";
            }
        };

        // 2. call for_each with a function that sends one message to one socket
        sockets.for_each(send_to_one);


    }
    accepterThread.join();
    return 0;
}

void server::udpRecvLoop()
{
    // Create a socket and bind it to the port 55002
    sf::UdpSocket socket;
    socket.bind(PORT + 1);
    
    // Receive a message from a client
    char buffer[1024];
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    socket.receive(buffer, sizeof(buffer), received, sender, port);
    std::cout << "Client said: " << buffer << std::endl;
    
    // Send an answer
    std::string message = "Welcome " + sender.toString();
    socket.send(message.c_str(), message.size() + 1, sender, port);
}