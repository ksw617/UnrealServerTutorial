// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SendBuffer.h"


SendBuffer::SendBuffer(int32 BufferSize)
{
	//ũ�� ����
	Buffer.SetNum(BufferSize);
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::CopyData(void* Data, int32 Len)
{
	//������ ����
	memcpy(Buffer.GetData(), Data, Len);
	WriteSize = Len;
}

void SendBuffer::Close(uint32 UsedSize)
{
	//�� ũ��� ���� ũ��
	WriteSize = UsedSize;
}
