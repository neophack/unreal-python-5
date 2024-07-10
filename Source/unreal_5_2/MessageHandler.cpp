// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageHandler.h"

FMessageHandler::FMessageHandler()
{
}

FMessageHandler::~FMessageHandler()
{
}

void FMessageHandler::AddObjectManager(UObjectManager* Manager)
{
    ObjectManager = Manager;
}

Msg FMessageHandler::ProcessMessage(const FString& Message)
{
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);

    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
        Msg DispatchMessage = ParseAndDispatch(JsonObject);
        return DispatchMessage;
    }
    return Msg(TInPlaceType<FString>(), FString(TEXT("Processed: ") + Message));
    //Msg(FString("Not a JSON message..."));
}

Msg FMessageHandler::ParseAndDispatch(TSharedPtr<FJsonObject>& JsonObject)
{
    FString Action = JsonObject->GetStringField(TEXT("action"));
    FString message = "Nothing happened";

    if (Action == TEXT("add_object") && MsgValidator.ValidateAddObject(JsonObject, message))
    {
        message = ObjectManager->SpawnObject(JsonObject);
    }
    else if (Action == TEXT("delete_object") && MsgValidator.ValidateDeleteObject(JsonObject, message))
    {
        message = ObjectManager->DeleteObject(JsonObject);
    }
    return Msg(TInPlaceType<FString>(), message);
};

