#include "ServerPacketHandler.h"

ServerPacketHandler::PacketHeaderFunc ServerPacketHandler::packetHandlers[UINT16_MAX];

void ServerPacketHandler::Init()
{
    for (int i = 0; i < UINT16_MAX; i++)
    {
        packetHandlers[i] = Handle_INVALID;
    }

    packetHandlers[S_LOGIN] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
        { return HandlePacket<Protocol::S_LOGIN>(Handle_S_LOGIN, session, buffer, len); };

    packetHandlers[S_ENTER_ROOM] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
        { return HandlePacket<Protocol::S_ENTER_ROOM>(Handle_S_ENTER_ROOM, session, buffer, len); };

    packetHandlers[S_CHAT] = [](TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
        { return HandlePacket<Protocol::S_CHAT>(Handle_S_CHAT, session, buffer, len); };

}

bool ServerPacketHandler::HandlePacket(TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
{
    PacketHeader* header = (PacketHeader*)buffer;
    return packetHandlers[header->Id](session, buffer, len);
}


bool Handle_INVALID(TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
{
    printf("Invalid Handle\n");

    return false;
}

bool Handle_S_LOGIN(TSharedPtr<PacketSession>& session, Protocol::S_LOGIN& packet)
{
    printf("SEVER LOGIN\n");
    return true;
}

bool Handle_S_ENTER_ROOM(TSharedPtr<PacketSession>& session, Protocol::S_ENTER_ROOM& packet)
{
    printf("SEVER ENTER ROOM\n");

    return false;
}

bool Handle_S_CHAT(TSharedPtr<PacketSession>& session, Protocol::S_CHAT& packet)
{
    printf("SEVER CHAT\n");

    return false;
}



