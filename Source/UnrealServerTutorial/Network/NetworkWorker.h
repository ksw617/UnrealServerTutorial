// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class FSocket;

struct UNREALSERVERTUTORIAL_API FPacketHeader
{
	uint16 PacketSize;	
	uint16 PacketID;	

	FPacketHeader() : PacketSize(0), PacketID(0) {}
	FPacketHeader(uint16 Size, uint16 ID) : PacketSize(Size), PacketID(ID) {}

	friend FArchive& operator<<(FArchive& Archive, FPacketHeader& Header)
	{
		Archive << Header.PacketSize;
		Archive << Header.PacketID;
		return Archive;
	}

};


class UNREALSERVERTUTORIAL_API RecvWorker : public FRunnable
{
protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	FSocket* Socket = nullptr;
	//PacketSession들구 있는 포인터
	TWeakPtr<class PacketSession> SessionRef;
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


class UNREALSERVERTUTORIAL_API SendWorker : public FRunnable
{
protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	FSocket* Socket = nullptr;
	//PacketSession들구 있는 포인터
	TWeakPtr<class PacketSession> SessionRef;
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

