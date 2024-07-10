// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"

UObjectManager::UObjectManager()
{

};

void UObjectManager::InitializeWorld(UWorld* World)
{
	ThisWorld = World;
};

void UObjectManager::SpawnObject()
{
	UE_LOG(LogTemp, Log, TEXT("Spawning Object"));
}