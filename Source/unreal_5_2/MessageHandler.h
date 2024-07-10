// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREAL_5_2_API FMessageHandler
{
public:
	FMessageHandler();
	~FMessageHandler();

public:
	FString ProcessMessage(const FString& Message);
	FString ParseAndDispatch(TSharedPtr<FJsonObject>& JsonObject);
};
