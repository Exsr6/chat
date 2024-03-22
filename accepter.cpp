#include "accepter.h"
#include "receiver.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <thread>

Accepter::Accepter(Queue<std::string>& q, List<std::shared_ptr<sf::TcpSocket>>& s):
    m_queue(q),
    m_socket(s)
{}

void Accepter::operator()()
{
    sf::TcpListener listener;

    // The listener has to listen.
    if (listener.listen(PORT) != sf::Socket::Done)
    {
        std::cerr << "Error Listening to client! " << std::endl;
        return;
    }
    std::cout << "Bound to port\n";
    while (true)
    {
        std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();

        // Accept a connection on socket
        if (listener.accept(*socket) != sf::Socket::Done)
        {
            std::cerr << "Error accepting the connection to client! " << std::endl;
            return;
        }


        m_socket.push(socket);
        std::stringstream ss;
        ss << "Accepted a connection from: "
            << socket->getRemoteAddress()
            << ":"
            << socket->getRemotePort()
            << std::endl;
        std::cout << ss.str();
        std::shared_ptr<Receiver> receiver = std::make_shared<Receiver>(socket, m_queue);
        // Launch a thread to receive with the receiver
        std::thread accepter_thread(&Receiver::recv_loop, receiver);
        accepter_thread.detach();
    }
}

