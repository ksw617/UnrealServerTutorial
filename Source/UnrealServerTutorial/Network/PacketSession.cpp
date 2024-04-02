// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/PacketSession.h"
#include "RecvWorker.h"


PacketSession::PacketSession(FSocket* Socket) : Socket(Socket)
{
}

PacketSession::~PacketSession()
{
}

void PacketSession::Run()
{
	RecvWorkerThread = MakeShared<RecvWorker>(Socket, AsShared());
}

void PacketSession::Disconnect()
{
}

void PacketSession::HandleRecvPackets()
{
	while (true)
	{
		TArray<uint8> Packet;
		if (!RecvPacketQueue.Dequeue(OUT Packet))
			break;

		//Todo

	}
}
