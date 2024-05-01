#include <SFML/Network.hpp>
#include <memory>
#include <functional>
#define PORT 4301


typedef std::pair<sf::Packet, std::shared_ptr<sf::TcpSocket>> Message;

//Socket and TCPsocket