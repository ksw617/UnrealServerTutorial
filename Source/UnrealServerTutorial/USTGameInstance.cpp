// Fill out your copyright notice in the Description page of Project Settings.

#include "USTGameInstance.h"
#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"
#include "SocketSubsystem.h"
#include "Network/PacketSession.h"	
#include "Protocol/Protocol.pb.h"
#include "ServerPacketHandler.h"

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

		ServerSession = MakeShared<PacketSession>(Socket);
		ServerSession->Run();


		//로그인 패킷 보내기
		{
			Protocol::C_LOGIN Packet;
			TSharedPtr<SendBuffer> SendBuffer = ServerPacketHandler::MakeSendPacket(Packet);
			SendPacket(SendBuffer);
			
		}
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
	if (Socket == nullptr || ServerSession == nullptr)
		return;

	ServerSession->HandleRecvPackets();
}

void UUSTGameInstance::SendPacket(TSharedPtr<class SendBuffer> SendBuffer)
{
	if (Socket == nullptr || ServerSession == nullptr)
		return;

	ServerSession->SendPacket(SendBuffer);
}

void UUSTGameInstance::HandleSpawn(const Protocol::PlayerInfo& PlayerInfo)
{
	if (Socket == nullptr || ServerSession == nullptr)
		return;

	auto* World = GetWorld();
	if (World == nullptr)
		return;

	const uint64 PlayerID = PlayerInfo.id();
	if (Players.Find(PlayerID) != nullptr)
		return;

	FVector SpawnLocation(PlayerInfo.x(), PlayerInfo.y(), PlayerInfo.z());
	AActor* Actor = World->SpawnActor(PlayerClass, &SpawnLocation);

	Players.Add(PlayerInfo.id(), Actor);
}

void UUSTGameInstance::HandleSpawn(const Protocol::S_ENTER_GAME& EnterGamePacket)
{
	HandleSpawn(EnterGamePacket.info());
}

void UUSTGameInstance::HandleSpawn(const Protocol::S_SPAWN& SpawnPacket)
{
	for (auto& Player : SpawnPacket.players())
	{
		HandleSpawn(Player);
	}
}

