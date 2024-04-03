// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SendBuffer.h"


SendBuffer::SendBuffer(int32 BufferSize)
{
	//크기 설정
	Buffer.SetNum(BufferSize);
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::CopyData(void* Data, int32 Len)
{
	//데이터 복사
	memcpy(Buffer.GetData(), Data, Len);
	WriteSize = Len;
}

void SendBuffer::Close(uint32 UsedSize)
{
	//쓴 크기는 사용된 크기
	WriteSize = UsedSize;
}
