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
        if (!ValidateJsonData(JsonObject, message))
        {
            return message;
        }
        message = ObjectManager->SpawnObject(JsonObject);
    }
    // ToDo: More info
    return message;
};

void FMessageHandler::AddObjectManager(UObjectManager* Manager)
{
    ObjectManager = Manager;
}

bool FMessageHandler::ValidateJsonData(TSharedPtr<FJsonObject>& JsonData, FString& ErrorMessage)
{
    if (!JsonData.IsValid())
    {
        ErrorMessage = TEXT("Invalid JSON data!");
        return false;
    }

    TSharedPtr<FJsonObject> LocationObject = JsonData->GetObjectField(TEXT("location"));
    if (!LocationObject.IsValid() ||
        !LocationObject->HasTypedField<EJson::Number>(TEXT("x")) ||
        !LocationObject->HasTypedField<EJson::Number>(TEXT("y")) ||
        !LocationObject->HasTypedField<EJson::Number>(TEXT("z")))
    {
        ErrorMessage = TEXT("Invalid location data!");
        return false;
    }

    TSharedPtr<FJsonObject> RotationObject = JsonData->GetObjectField(TEXT("rotation"));
    if (!RotationObject.IsValid() ||
        !RotationObject->HasTypedField<EJson::Number>(TEXT("pitch")) ||
        !RotationObject->HasTypedField<EJson::Number>(TEXT("yaw")) ||
        !RotationObject->HasTypedField<EJson::Number>(TEXT("roll")))
    {
        ErrorMessage = TEXT("Invalid rotation data!");
        return false;
    }

    if (!JsonData->HasTypedField<EJson::String>(TEXT("material_path")))
    {
        ErrorMessage = TEXT("Invalid or missing material_path!");
        return false;
    }

    if (!JsonData->HasTypedField<EJson::String>(TEXT("mesh_path")))
    {
        ErrorMessage = TEXT("Invalid or missing mesh_path!");
        return false;
    }

    if (!JsonData->HasTypedField<EJson::Boolean>(TEXT("physics")))
    {
        ErrorMessage = TEXT("Invalid or missing physcis!");
        return false;
    }

    return true;
}