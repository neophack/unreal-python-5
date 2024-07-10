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
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);

    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        FString DispatchMessage = ParseAndDispatch(JsonObject);
        return DispatchMessage;
    }
    return FString("Not a JSON message...");
}

FString FMessageHandler::ParseAndDispatch(TSharedPtr<FJsonObject>& JsonObject)
{
    FString Action = JsonObject->GetStringField(TEXT("action"));
    FString message = "Nothing happened";

    if (Action == TEXT("add_object"))
    {
        if (!MsgValidator.ValidateAddObject(JsonObject, message))
        {
            return message;
        }
        message = ObjectManager->SpawnObject(JsonObject);
    }
    else if (Action == TEXT("delete_object"))
    {
        if (!MsgValidator.ValidateDeleteObject(JsonObject, message))
        {
            return message;
        }
        message = ObjectManager->DeleteObject(JsonObject);
    }
    // ToDo: More info
    return message;
};

void FMessageHandler::AddObjectManager(UObjectManager* Manager)
{
    ObjectManager = Manager;
}
