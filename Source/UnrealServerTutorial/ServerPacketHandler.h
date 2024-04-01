#pragma once
//#include "PacketHandler.h"
//#include "Protocol.pb.h"
//
//enum :uint16
//{
//	C_LOGIN = 1001,
//	S_LOGIN = 1002,
//	C_ENTER_ROOM = 1003,
//	S_ENTER_ROOM = 1004,
//	C_CHAT = 1005,
//	S_CHAT = 1006,
//};
//
//bool Handle_S_LOGIN(shared_ptr<PacketSession>& session, Protocol::S_LOGIN& packet);
//bool Handle_S_ENTER_ROOM(shared_ptr<PacketSession>& session, Protocol::S_ENTER_ROOM& packet);
//bool Handle_S_CHAT(shared_ptr<PacketSession>& session, Protocol::S_CHAT& packet);
//
//class ServerPacketHandler  : public PacketHandler
//{
//
//public:
//	static void Init();
//public:
//	static shared_ptr<SendBuffer> MakeSendPacket(Protocol::C_LOGIN& packet) { return MakeSendBuffer(packet, C_LOGIN); }
//	static shared_ptr<SendBuffer> MakeSendPacket(Protocol::C_ENTER_ROOM& packet) { return MakeSendBuffer(packet, C_ENTER_ROOM); }
//	static shared_ptr<SendBuffer> MakeSendPacket(Protocol::C_CHAT& packet) { return MakeSendBuffer(packet, C_CHAT); }
//
//};

