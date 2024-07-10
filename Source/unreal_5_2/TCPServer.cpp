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
    MessageHandler = MakeUnique<FMessageHandler>();
}

// Called when the game starts or when spawned
void ATCPServer::BeginPlay()
{
    Super::BeginPlay();
    ObjectManager = NewObject<UObjectManager>();
    UWorld* World = GetWorld();
    if (World) {
        ObjectManager->InitializeWorld(GetWorld());
        MessageHandler->AddObjectManager(ObjectManager);
    };

    StartTCPListener();
}

// Called every frame
void ATCPServer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    bool connected = CheckForConnections();
    FString ReceivedMessage = ReceiveData();
    if (!ReceivedMessage.IsEmpty()) {
        Msg DispatchMessage = MessageHandler->ProcessMessage(ReceivedMessage);
        SendMessage(DispatchMessage);
    }
}

void ATCPServer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    CloseTCPListener();
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

bool ATCPServer::CheckForConnections()
{
    if (ServerSocket)
    {
        bool Pending;
        if (ServerSocket->HasPendingConnection(Pending) && Pending)
        {
            ClientSocket = ServerSocket->Accept(TEXT("Accepted Client Connection"));
            if (ClientSocket)
            {
                UE_LOG(LogServer, Log, TEXT("Client connected"));
                return true;
            }
        }
    }
    return false;
}

FString ATCPServer::ReceiveData()
{
    if (ClientSocket)
    {
        uint32 Size;
        while (ClientSocket->HasPendingData(Size))
        {
            TArray<uint8> ReceivedData;
            ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

            int32 Read = 0;
            ClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

            // Ensure the data is null-terminated
            ReceivedData.Add(0);

            FString ReceivedString = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
            UE_LOG(LogServer, Log, TEXT("Received Data: %s"), *ReceivedString);
            return ReceivedString;
        }

        if (ClientSocket->GetConnectionState() != SCS_Connected)
        {
            ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
            ClientSocket = nullptr;
            UE_LOG(LogServer, Log, TEXT("Client disconnected"));
        }
    }
    return FString();
}

void ATCPServer::SendMessage(const FString& Message)
{
    if (ClientSocket && ClientSocket->GetConnectionState() == SCS_Connected)
    {
        // Convert the FString to a byte array
        FTCHARToUTF8 Convert(*Message);
        int32 BytesSent = 0;
        bool bSuccessful = ClientSocket->Send((uint8*)Convert.Get(), Convert.Length(), BytesSent);

        if (bSuccessful)
        {
            UE_LOG(LogServer, Log, TEXT("Sent message to client: %s"), *Message);
        }
        else
        {
            UE_LOG(LogServer, Error, TEXT("Failed to send message to client"));
        }
    }
    else
    {
        UE_LOG(LogServer, Error, TEXT("No client connected or client disconnected"));
    }
}

void ATCPServer::SendImage(const TArray<uint8>& ImageData)
{
    if (ClientSocket && ClientSocket->GetConnectionState() == SCS_Connected)
    {
        int32 BytesSent = 0;
        int32 TotalBytesSent = 0;
        int32 DataSize = ImageData.Num();
        const uint8* DataPtr = ImageData.GetData();

        while (TotalBytesSent < DataSize)
        {
            ClientSocket->Send(DataPtr + TotalBytesSent, DataSize - TotalBytesSent, BytesSent);
            TotalBytesSent += BytesSent;
        }

        if (TotalBytesSent == DataSize)
        {
            UE_LOG(LogServer, Log, TEXT("Sent binary data to client"));
        }
        else
        {
            UE_LOG(LogServer, Error, TEXT("Failed to send all data to client"));
        }
    }
    else
    {
        UE_LOG(LogServer, Error, TEXT("No client connected or client disconnected"));
    }
}

void ATCPServer::SendMessage(const Msg& Message)
{
    if (ClientSocket && ClientSocket->GetConnectionState() == SCS_Connected)
    {
        if (Message.IsType<FString>())
        {
            SendMessage(Message.Get<FString>());
        }
        else if (Message.IsType<TArray<uint8>>())
        {
            SendImage(Message.Get<TArray<uint8>>());
        }
    }
}

bool ATCPServer::CloseTCPListener()
{
    if (ServerSocket)
    {
        ServerSocket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ServerSocket);
        ServerSocket = nullptr;
    }
    if (ClientSocket)
    {
        ClientSocket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
        ClientSocket = nullptr;
    }

    UE_LOG(LogServer, Log, TEXT("Sockets cleaned up"));
    return true;
}