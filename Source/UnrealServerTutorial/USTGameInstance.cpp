// Fill out your copyright notice in the Description page of Project Settings.

#include "USTGameInstance.h"
#include "Sockets.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/ArrayWriter.h"
#include "SocketSubsystem.h"

//서버 연결
void UUSTGameInstance::ConnectToServer()
{
	//TCP 스트림 "Client Socket" 이름으로 소켓 생성. 
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket"));

	//문자열로 된 IP 주소를 파싱하여 FIPv4Address 객체로 변환
	FIPv4Address Ip;
	FIPv4Address::Parse(IpAddress, Ip);

	//인터넷 주소 생성 및 설정
	TSharedRef<FInternetAddr> InternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	InternetAddr->SetIp(Ip.Value);	//IP 주소 설정
	InternetAddr->SetPort(Port);	//포트 번호 설정

	//화면에 서버 연결 시도 메세지 출력
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connect To Server...")));

	//서버에 연결 시도
	bool Connected = Socket->Connect(*InternetAddr);

	if (Connected)
	{
		//연결 성공 시 화면에 성공 메세지 출력
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connection Success")));

		//Todo
	}
	else
	{
		//연결 실패 시 화면에 실패 메세지 출력
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connection Failed")));

	}
}


//연결 해제
void UUSTGameInstance::disconnectFromServer()
{			  
	//만약에 소켓에 값이 있다면
	if (Socket)
	{

		//소켓 서브 시스템을 통해 생성된 소켓을 파괴하고 연결 해제
		ISocketSubsystem::Get()->DestroySocket(Socket);
		Socket = nullptr; // 소켓 포인터를 null로 설정하여 더 이상 사용 방지
	}
}
