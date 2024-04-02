// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkWorker.h"
/**
 * 
 */
class UNREALSERVERTUTORIAL_API RecvWorker : public NetworkWorker
{
public:
	RecvWorker(FSocket* MySocket, TSharedPtr<class PacketSession> Session);
	~RecvWorker();
public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Exit() override;
public:
	void Destroy(); // 스레드 중지 할 목적으로
private:
	bool RecvPacket(TArray<uint8>& OutPacket);
	bool RecvDesiredBytes(uint8* Results, int32 Size);
};
