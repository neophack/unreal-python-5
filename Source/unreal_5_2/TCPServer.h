// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectManager.h"
#include "MessageHandler.h"
#include "TCPServer.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogServer, Log, All);

UCLASS()
class UNREAL_5_2_API ATCPServer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATCPServer();
	ISocketSubsystem* SocketSubsystem;
	FSocket* ServerSocket;
	FSocket* ClientSocket;
	int32 port = 9999;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool StartTCPListener();
	bool bindSocketSuccess;
	//bool CheckForConnections();

	//FString ReceiveData();
	//void SendMessage(const FString& Message);
	//bool CloseTCPListener();
};
