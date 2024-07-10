// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageType.h"

//MessageType::MessageType()
//{
//}
//
//MessageType::~MessageType()
//{
//}

Msg MessageType::StringToMsg(const FString& Message)
{
    return Msg(TInPlaceType<FString>(), Message);
}

Msg MessageType::TArrayToMsg(const TArray<uint8>& Data)
{
    return Msg(TInPlaceType<TArray<uint8>>(), Data);
}
