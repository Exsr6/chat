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
    std::stringstream ss;

    m.first >> msg.msgType;
    switch(msg.msgType) {

        // Register Message
        case MsgType::Register:
        m_reg = new MsgReg();
        if (m.first >> m_reg->id >> m_reg->username){
            std::memcpy(&msg, m_reg, sizeof(MsgReg));
        }
        else{
            ss << "message::readMsg Register message, failed!\n";
        }
        delete m_reg;
        break;

        // Select Message
        case MsgType::Select:
        m_select = new MsgSelect();
        if (m.first >> m_select->id >> m_select->builderID){
            std::memcpy(&msg, m_select, sizeof(MsgSelect));
        }
        else{
            ss << "message::readMsg Select message, failed!\n";
        }
        delete m_select;
        break;


        case MsgType::Build:
        case MsgType::Move:

        // Place Message
        case MsgType::Place:
        m_pos = new MsgPos();
        m_pos->msgType = msg.msgType;
        if (m.first >> m_pos->id >> m_pos->x >> m_pos->y)
        {
            std::memcpy(&msg, m_pos, sizeof(MsgPos));
        }
        else
        {
            ss << "message::readMsg Move message, failed!\n";
        }
        delete m_pos;
        break;

        // Rand Message
        case MsgType::Rand:
        m_rand = new MsgRand();
        if (m.first >> m_rand->id >> m_rand->r)
        {
            std::memcpy(&msg, m_rand, sizeof(MsgRand));
        }
        else{
            ss << "message::readMsg Rand message, failed!\n";
        }
        delete m_rand;
        break;
    }
}