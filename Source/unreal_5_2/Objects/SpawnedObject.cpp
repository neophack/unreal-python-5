// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnedObject.h"

// Sets default values
ASpawnedObject::ASpawnedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a root component and attach it to the actor
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootComp;

}

// Called when the game starts or when spawned
void ASpawnedObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

