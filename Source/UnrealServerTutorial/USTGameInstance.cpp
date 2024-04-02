// Fill out your copyright notice in the Description page of Project Settings.

#include "USTGameInstance.h"
#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"
#include "SocketSubsystem.h"
#include "Network/PacketSession.h"	// �߰�

void UUSTGameInstance::ConnectToServer()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));

	FIPv4Address Ip;
	FIPv4Address::Parse(IpAddress, Ip);

	TSharedRef<FInternetAddr> InternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	InternetAddr->SetIp(Ip.Value);
	InternetAddr->SetPort(Port);	

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect To Server...")));

	bool Connected = Socket->Connect(*InternetAddr);

	if (Connected)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connection Success")));

		//PacketSession ���� Socket �Ѱ���
		ServerSession = MakeShared<PacketSession>(Socket);
		//Run ����
		ServerSession->Run();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connection Failed")));

	}
}

void UUSTGameInstance::DisconnectFromServer()
{	
	if (Socket)
	{
		ISocketSubsystem::Get()->DestroySocket(Socket);
		Socket = nullptr; 
	}
}

void UUSTGameInstance::HandleRecvPackets()
{	
	//�����̳� ���� ������ ���� ��� �Լ� ����
	if (Socket == nullptr || ServerSession == nullptr)
		return;

	//���� ������ ���� ���ŵ� ��Ŷ�� ó��
	ServerSession->HandleRecvPackets();
}

