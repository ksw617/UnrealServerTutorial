// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkWorker.h"

/**
 * 
 */
class UNREALSERVERTUTORIAL_API SendWorker : public NetworkWorker
{
public:
	SendWorker(FSocket* MySocket, TSharedPtr<class PacketSession> Session);
	~SendWorker();
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
public:
	void Destroy();
private:
	bool SendPacket(TSharedPtr<class SendBuffer> SendBuffer);
	bool SendDesiredBytes(const uint8* Buffer, int32 Size);
};
