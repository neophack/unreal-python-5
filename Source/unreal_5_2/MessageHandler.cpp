// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageHandler.h"

FMessageHandler::FMessageHandler()
{
}

FMessageHandler::~FMessageHandler()
{
}

FString FMessageHandler::ProcessMessage(const FString& Message)
{
	FString message = FString("Hello");
	return message;
}