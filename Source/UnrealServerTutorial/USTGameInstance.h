// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "USTGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSERVERTUTORIAL_API UUSTGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void ConnectToServer();
	UFUNCTION(BlueprintCallable)
	void disconnectFromServer();
public:
	class FSocket* Socket = nullptr;
	FString IpAddress = TEXT("127.0.0.1");
	int16 Port = 27015;

	
};
