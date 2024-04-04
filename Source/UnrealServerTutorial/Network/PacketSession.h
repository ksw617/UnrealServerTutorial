// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALSERVERTUTORIAL_API PacketSession : public TSharedFromThis<PacketSession>
{
public:
	class FSocket* Socket = nullptr;
	TQueue<TArray<uint8>> RecvPacketQueue;
	TQueue<TSharedPtr<class SendBuffer>> SendPacketQueue;
	TSharedPtr<class RecvWorker> RecvWorkerThread;
	TSharedPtr<class SendWorker> SendWorkerThread;
public:
	PacketSession(class FSocket* Socket);
	~PacketSession();
public:
	void Run();
	void Disconnect();
public:
	UFUNCTION(BlueprintCallable)
	void HandleRecvPackets();
	void SendPacket(TSharedPtr<class SendBuffer> SendBuffer);
};
