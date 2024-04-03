#pragma once

#include "CoreMinimal.h"

#include "Network/SendBuffer.h"
#include "Network/PacketSession.h"
#include "Protocol/Protocol.pb.h"

enum : uint16
{
	C_LOGIN = 1001,
	S_LOGIN = 1002,
	C_ENTER_ROOM = 1003,
	S_ENTER_ROOM = 1004,
	C_CHAT = 1005,
	S_CHAT = 1006,
};

bool Handle_INVALID(TSharedPtr<PacketSession>& session, BYTE* buffer, int len);
bool Handle_S_LOGIN(TSharedPtr<PacketSession>& session, Protocol::S_LOGIN& packet);
bool Handle_S_ENTER_ROOM(TSharedPtr<PacketSession>& session, Protocol::S_ENTER_ROOM& packet);
bool Handle_S_CHAT(TSharedPtr<PacketSession>& session, Protocol::S_CHAT& packet);

class ServerPacketHandler  : public PacketHandler
{
protected:
	using PacketHeaderFunc = std::function<bool(TSharedPtr<PacketSession>&, BYTE*, int)>;
	static PacketHeaderFunc packetHandlers[UINT16_MAX];

public:
	//Init
	static void Init();
	//Recv
	static bool HandlePacket(TSharedPtr<PacketSession>& session, BYTE* buffer, int len);
public:
	static TSharedPtr<SendBuffer> MakeSendPacket(Protocol::C_LOGIN& packet) { return MakeSendBuffer(packet, C_LOGIN); }
	static TSharedPtr<SendBuffer> MakeSendPacket(Protocol::C_ENTER_ROOM& packet) { return MakeSendBuffer(packet, C_ENTER_ROOM); }
	static TSharedPtr<SendBuffer> MakeSendPacket(Protocol::C_CHAT& packet) { return MakeSendBuffer(packet, C_CHAT); }
protected:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, TSharedPtr<PacketSession>& session, BYTE* buffer, int len)
	{
		PacketType packet;
		packet.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

		return func(session, packet);
	}

protected:
	template<typename T>
	static TSharedPtr<SendBuffer> MakeSendBuffer(T& packet, uint16 id)
	{
		uint16 dataSize = static_cast<uint16>(packet.ByteSizeLong());
		uint16 packetSize = dataSize + sizeof(PacketHeader);

		TSharedPtr<SendBuffer> sendBuffer = MakeShared<SendBuffer>(packetSize);
		PacketHeader* buffer = reinterpret_cast<PacketHeader*>(sendBuffer->GetBuffer());
		buffer->Size = packetSize;
		buffer->Id = id;

		packet.SerializeToArray(&buffer[1], dataSize);
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}

};

