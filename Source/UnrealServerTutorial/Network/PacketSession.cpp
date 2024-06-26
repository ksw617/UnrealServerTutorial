// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/PacketSession.h"
#include "Network/NetworkWorker.h"
#include "ServerPacketHandler.h"

#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"
#include "SocketSubsystem.h"
#include "Network/PacketSession.h"	

PacketSession::PacketSession(FSocket* Socket) : Socket(Socket)
{
	ServerPacketHandler::Init();

}

PacketSession::~PacketSession()
{
	Disconnect();
}

void PacketSession::Run()
{
	RecvWorkerThread = MakeShared<RecvWorker>(Socket, AsShared());
	SendWorkerThread = MakeShared<SendWorker>(Socket, AsShared());
}


void PacketSession::HandleRecvPackets()
{
	while (true)
	{
		TArray<uint8> Packet;
		if (!RecvPacketQueue.Dequeue(OUT Packet))
			break;

		TSharedPtr<PacketSession> MySession = AsShared();
		ServerPacketHandler::HandlePacket(MySession, Packet.GetData(), Packet.Num());

	}
}

void PacketSession::SendPacket(TSharedPtr<class SendBuffer> SendBuffer)
{
	SendPacketQueue.Enqueue(SendBuffer);
}

void PacketSession::Disconnect()
{
	if (RecvWorkerThread)
	{
		RecvWorkerThread->Destroy();
		RecvWorkerThread = nullptr;
	}

	if (SendWorkerThread)
	{
		SendWorkerThread->Destroy();
		SendWorkerThread = nullptr;
	}
}


