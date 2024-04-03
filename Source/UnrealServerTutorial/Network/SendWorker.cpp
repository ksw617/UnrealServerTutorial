// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SendWorker.h"
#include "SendBuffer.h"
#include "PacketSession.h" 
#include "Sockets.h"

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
