// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectManager.h"
#include "MessageValidator.h"

/**
 * 
 */
class UNREAL_5_2_API FMessageHandler
{
public:
	FMessageHandler();
	~FMessageHandler();

public:
	void AddObjectManager(UObjectManager* manager);
	FString ProcessMessage(const FString& Message);

private:
	UObjectManager* ObjectManager;
	FMessageValidator MsgValidator;

	FString ParseAndDispatch(TSharedPtr<FJsonObject>& JsonObject);
};
