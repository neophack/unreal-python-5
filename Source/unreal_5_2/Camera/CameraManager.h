// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CameraManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_5_2_API UCameraManager : public UObject
{
	GENERATED_BODY()

public:
	FString AddCamera(TSharedPtr<FJsonObject>& JsonData);

private:
	TMap<FString, AActor*> CameraDatabase;
};
