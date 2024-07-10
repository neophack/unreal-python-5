// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "MessageValidator.h"
#include "MessageType.h"


class UNREAL_5_2_API FMessageHandler
{
public:
	FMessageHandler();
	~FMessageHandler();

public:
	void AddObjectManager(UObjectManager* Manager);
	void AddCameraManager(UCameraManager* Manager);
	Msg ProcessMessage(const FString& Message);

private:
	UObjectManager* ObjectManager;
	UCameraManager* CameraManager;
	FMessageValidator MsgValidator;

	Msg ParseAndDispatch(TSharedPtr<FJsonObject>& JsonObject);
};
