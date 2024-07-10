// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/TVariant.h"

typedef TVariant<FString, TArray<uint8>> Msg;

class UNREAL_5_2_API MessageType
{
//public:
//	MessageType();
//	~MessageType();
public:
	static Msg StringToMsg(const FString& Message);
    static Msg TArrayToMsg(const TArray<uint8>& Data);
};
