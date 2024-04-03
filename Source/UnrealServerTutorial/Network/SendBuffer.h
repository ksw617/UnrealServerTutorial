// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct PacketHeader
{
	uint16 Size; // Å©±â
	uint16 Id;	 // id
};


class UNREALSERVERTUTORIAL_API SendBuffer : public TSharedFromThis<SendBuffer>
{
public:
	TArray<BYTE> Buffer;
	int32 WriteSize = 0;
public:
	SendBuffer(int32 BufferSize);
	~SendBuffer();
public:
	BYTE* GetBuffer() { return Buffer.GetData(); }
	int32 GetWriteSize() const { return WriteSize; }
	int32 Capacity() const { return static_cast<int32>(Buffer.Num()); }
public:
	void CopyData(void* Data, int32 Len);
	void Close(uint32 UsedSize);
};
