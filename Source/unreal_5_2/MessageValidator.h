// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class UNREAL_5_2_API FMessageValidator
{
public:
	bool ValidateAddObject(TSharedPtr<FJsonObject>& JsonObject, FString ErrorMessage);
	bool ValidateDeleteObject(TSharedPtr<FJsonObject>& JsonData, FString& ErrorMessage);
};
