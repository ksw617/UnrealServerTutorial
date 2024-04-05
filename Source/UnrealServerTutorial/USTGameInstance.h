// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Protocol/Protocol.pb.h"
#include "USTGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSERVERTUTORIAL_API UUSTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	class FSocket* Socket = nullptr;
	FString IpAddress = TEXT("127.0.0.1");
	int16 Port = 27015;
	TSharedPtr<class PacketSession> ServerSession;
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PlayerClass;
	TMap<uint64, AActor*> Players;
public:
	UFUNCTION(BlueprintCallable)
	void ConnectToServer();
	UFUNCTION(BlueprintCallable)
	void DisconnectFromServer();
	UFUNCTION(BlueprintCallable)
	void HandleRecvPackets();

	void SendPacket(TSharedPtr<class SendBuffer> SendBuffer);
public:
	void HandleSpawn(const Protocol::PlayerInfo& PlayerInfo);
	void HandleSpawn(const Protocol::S_ENTER_GAME& EnterGamePacket);
	void HandleSpawn(const Protocol::S_SPAWN& SpawnPacket);

	
};
