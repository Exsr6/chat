#include "Message.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>

sf::Packet& operator << (sf::Packet& packet, const MsgType mType)
{
    return packet << static_cast<sf::Uint8>(mType);
}

sf::Packet& operator >> (sf::Packet& packet, MsgType mtype)
{
    sf::Uint8 r;
    packet >> r;
    mtype = static_cast<MsgType>(r);
    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const MsgReg msg)
{
    return packet << msg.msgType << msg.id << msg.username;
}

sf::Packet& operator >> (sf::Packet& packet, MsgReg msg)
{
    return packet >> msg.msgType >> msg.id >> msg.username;
}

sf::Packet& operator << (sf::Packet& packet, const MsgSelect msg)
{
    return packet << msg.msgType << msg.id << msg.builderID;
}

sf::Packet& operator >> (sf::Packet& packet, MsgSelect msg)
{
    return packet >> msg.msgType >> msg.id >> msg.builderID;
}

sf::Packet& operator << (sf::Packet& packet, const MsgPos msg)
{
    return packet << msg.msgType << msg.id << msg.x << msg.y;
}

sf::Packet& operator >> (sf::Packet& packet, MsgPos msg)
{
    return packet >> msg.msgType >> msg.id >> msg.x >> msg.y;
}

sf::Packet& operator << (sf::Packet& packet, const MsgRand msg)
{
    return packet << msg.msgType << msg.id << msg.r;
}

sf::Packet& operator >> (sf::Packet& packet, MsgRand msg)
{
    return packet >> msg.msgType >> msg.id >> msg.r;
}

void ReadMsg(Message m, Msg& msg)
{
    MsgReg* m_reg;
    MsgPos* m_pos;
    MsgRand* m_rand;
    MsgSelect* m_select;


}