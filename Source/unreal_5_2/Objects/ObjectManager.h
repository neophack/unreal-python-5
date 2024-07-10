// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectManager.generated.h"


UCLASS()
class UNREAL_5_2_API UObjectManager : public UObject
{
	GENERATED_BODY()

public:
	void InitializeWorld(UWorld* World);
	FString SpawnObject(TSharedPtr<FJsonObject>& JsonData);
	FString DeleteObject(TSharedPtr<FJsonObject>& JsonData);
	FString AddCamera(TSharedPtr<FJsonObject>& JsonData);

private:
	UWorld* ThisWorld;
	TMap<FString, AActor*> ObjectDatabase;

	static int32 ObjectCounter;
};
