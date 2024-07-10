// Fill out your copyright notice in the Description page of Project Settings.


#include "TCPServer.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"

DEFINE_LOG_CATEGORY(LogServer);

// Sets default values
ATCPServer::ATCPServer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StartTCPListener();
}

bool ATCPServer::StartTCPListener()
{
    // Obtain the socket subsystem
    SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    if (!SocketSubsystem)
    {
        UE_LOG(LogServer, Error, TEXT("Unable to get SocketSubsystem"));
        return false;
    }
    else {
        UE_LOG(LogServer, Log, TEXT("Got SocketSubsystem"));
    }

    // Create the TCP listener socket
    ServerSocket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("TCP Server"), false);
    if (!ServerSocket)
    {
        UE_LOG(LogServer, Error, TEXT("Unable to create TCP Socket"));
        return false;
    }
    else {
        UE_LOG(LogServer, Log, TEXT("Created TCP Socket"));
    }

    // Set up the server address
    TSharedRef<FInternetAddr> ServerAddr = SocketSubsystem->CreateInternetAddr();
    ServerAddr->SetIp(TEXT("0.0.0.0"), bindSocketSuccess);
    ServerAddr->SetPort(port);

    // Bind the socket to the address
    if (!ServerSocket->Bind(*ServerAddr))
    {
        UE_LOG(LogServer, Error, TEXT("Unable to bind socket to address"));
        return false;
    }
    else {
        UE_LOG(LogServer, Log, TEXT("Socket successfully bound to address"));
    }

    // Start listening on the socket
    if (!ServerSocket->Listen(8))
    {
        UE_LOG(LogServer, Error, TEXT("Unable to start listening on socket"));
        return false;
    }
    else {
        UE_LOG(LogServer, Log, TEXT("Server started listening on port %d"), port);
    }
    return true;
}

// Called when the game starts or when spawned
void ATCPServer::BeginPlay()
{
	Super::BeginPlay();
	//StartTCPListener();
}

// Called every frame
void ATCPServer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

