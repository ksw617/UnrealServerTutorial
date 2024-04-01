//#include "pch.h"
//#include "ServerPacketHandler.h"
//
//void ServerPacketHandler::Init()
//{
//    PacketHandler::Init();
//    
//    packetHandlers[S_LOGIN] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
//        {
//            return HandlePacket<Protocol::S_LOGIN>(Handle_S_LOGIN, session, buffer, len);
//        };
//
//    packetHandlers[S_ENTER_ROOM] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
//        {
//            return HandlePacket<Protocol::S_ENTER_ROOM>(Handle_S_ENTER_ROOM, session, buffer, len);
//        };
//
//    packetHandlers[S_CHAT] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int len)
//        {
//            return HandlePacket<Protocol::S_CHAT>(Handle_S_CHAT, session, buffer, len);
//        };
//
//}
//
//
//bool Handle_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int len)
//{
//    printf("Invalid Handle\n");
//
//    //todo
//    return false;
//}
//
//bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_LOGIN& packet)
//{
//    if (!packet.success())
//        return false;
//
//    printf("LOGIN SUCCESS\n");
//    Protocol::C_ENTER_ROOM sendPacket;
//    
//    Protocol::Player* player = new Protocol::Player;
//    player->set_id(packet.playerid());
//    player->set_name("TEST");
//    
//    sendPacket.set_allocated_player(player);
//    
//    auto sendBuffer = ServerPacketHandler::MakeSendPacket(sendPacket);
//    session->Send(sendBuffer);
//
//    return true;
//}
//
//bool Handle_S_ENTER_ROOM(shared_ptr<PacketSession>& session, Protocol::S_ENTER_ROOM& packet)
//{
//    printf("SEVER ENTER ROOM\n");
//
//    return false;
//}
//
//bool Handle_S_CHAT(shared_ptr<PacketSession>& session, Protocol::S_CHAT& packet)
//{
//    printf("SEVER CHAT\n");
//
//    return false;
//}

//