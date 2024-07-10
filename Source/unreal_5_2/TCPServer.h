// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectManager.h"
#include "MessageHandler.h"
#include "TCPServer.generated.h"

UCLASS()
class UNREAL_5_2_API ATCPServer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATCPServer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
