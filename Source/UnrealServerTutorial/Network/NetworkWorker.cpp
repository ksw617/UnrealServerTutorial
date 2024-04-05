// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkWorker.h"
#include "Sockets.h"
#include "Serialization/ArrayWriter.h"
#include "PacketSession.h"
#include "SendBuffer.h"


RecvWorker::RecvWorker(FSocket* MySocket, TSharedPtr<class PacketSession> Session) : Socket(MySocket), SessionRef(Session)
{
	Thread = FRunnableThread::Create(this, TEXT("Recv Worker Thread"));

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
				Session->RecvPacketQueue.Enqueue(Packet);
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


SendWorker::SendWorker(FSocket* MySocket, TSharedPtr<class PacketSession> Session)
{
	Thread = FRunnableThread::Create(this, TEXT("Send Worker Thread"));
	Socket = MySocket;
	SessionRef = Session;
}

SendWorker::~SendWorker()
{
}

bool SendWorker::Init()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Send Worker thread Init")));
	return true;
}

uint32 SendWorker::Run()
{
	while (Running)
	{
		TSharedPtr<SendBuffer> SendBuffer;
	
			if (TSharedPtr<PacketSession> Session = SessionRef.Pin())
			{
				if (Session->SendPacketQueue.Dequeue(OUT SendBuffer))
				{
					SendPacket(SendBuffer);
				}
			}
		
	}

	return 0;
}


void SendWorker::Exit()
{
}

void SendWorker::Destroy()
{
	Running = false;
}

bool SendWorker::SendPacket(TSharedPtr<class SendBuffer> SendBuffer)
{
	if (SendDesiredBytes(SendBuffer->GetBuffer(), SendBuffer->GetWriteSize()) == false)
		return false;

	return true;
}

bool SendWorker::SendDesiredBytes(const uint8* Buffer, int32 Size)
{
	while (Size > 0)
	{
		int32 BytesSend = 0;
		if (Socket->Send(Buffer, Size, BytesSend) == false)
			return false;

		Size -= BytesSend;
		Buffer += BytesSend;

	}

	return true;
}
