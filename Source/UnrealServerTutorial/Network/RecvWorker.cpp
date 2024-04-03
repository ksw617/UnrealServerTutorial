// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/RecvWorker.h"
#include "Sockets.h"
#include "Serialization/ArrayWriter.h"
#include "PacketSession.h"


RecvWorker::RecvWorker(FSocket* MySocket, TSharedPtr<class PacketSession> Session)
{
	Thread = FRunnableThread::Create(this, TEXT("Recv Worker Thread"));
	Socket = MySocket;
	SessionRef = Session;
}

RecvWorker::~RecvWorker()
{
}

bool RecvWorker::Init()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Recv Worker thread Init")));
	return true;
}

uint32 RecvWorker::Run()
{
	while (Running)
	{
		TArray<uint8> Packet; 
		if (RecvPacket(OUT Packet)) 
		{
			if (TSharedPtr<PacketSession> Session = SessionRef.Pin())
			{
				Session->RecvPacketQueue.Dequeue(Packet);
			}
		}
	}

	return 0;
}

void RecvWorker::Exit()
{
	//Todo
}

void RecvWorker::Destroy()
{
	//while 루프 종료
	Running = false;
}

bool RecvWorker::RecvPacket(TArray<uint8>& OutPacket)
{
	const int32 HeaderSize = sizeof(FPacketHeader);
	TArray<uint8> HeaderBuffer;
	HeaderBuffer.AddZeroed(HeaderSize);

	if (!RecvDesiredBytes(HeaderBuffer.GetData(), HeaderSize))
		return false;

	FPacketHeader Header; 
	{
		FMemoryReader Reader(HeaderBuffer);
		Reader << Header;

		UE_LOG(LogTemp, Log, TEXT("Recv PacketID : %d, PacketSize : %d"), Header.PacketID, Header.PacketSize);
	}

	OutPacket = HeaderBuffer; 

	TArray<uint8> PayloadBuffer; 
	const int32 PayloadSize = Header.PacketSize - HeaderSize;
	if (PayloadSize == 0)
		return true;
	
	OutPacket.AddZeroed(PayloadSize); 
	
	return RecvDesiredBytes(&OutPacket[HeaderSize], PayloadSize);
}

bool RecvWorker::RecvDesiredBytes(uint8* Results, int32 Size)
{
	uint32 PendingDataSize;

	if (Socket->HasPendingData(PendingDataSize) == false || PendingDataSize <= 0)
		return false;

	int32 Offset = 0; 

	while (Size > 0) 
	{
		int32 NumRead = 0;
		Socket->Recv(Results + Offset, Size, OUT NumRead);
		check(NumRead <= Size);

		if (NumRead <= 0)
			return false;

		Offset += NumRead; 
		Size -= NumRead;

	}

	return true;
}
