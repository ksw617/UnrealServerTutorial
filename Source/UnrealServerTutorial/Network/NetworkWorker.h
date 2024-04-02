// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

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

class UNREALSERVERTUTORIAL_API NetworkWorker : public FRunnable
{
protected:
	FRunnableThread* Thread = nullptr;
	bool Running = true;
	FSocket* Socket;
	//PacketSession들구 있는 포인터
	TWeakPtr<class PacketSession> SessionRef;
};
