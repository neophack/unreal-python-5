// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "SpawnedObject.h"

int32 UObjectManager::ObjectCounter = 1;

UObjectManager::UObjectManager()
{
};

void UObjectManager::InitializeWorld(UWorld* World)
{
	ThisWorld = World;
};

FString UObjectManager::SpawnObject(TSharedPtr<FJsonObject>& JsonData)
{
    FString ObjectID = FString::Printf(TEXT("%d"), ObjectCounter++);

    FVector Location;
    Location.X = JsonData->GetObjectField(TEXT("location"))->GetNumberField(TEXT("x"));
    Location.Y = JsonData->GetObjectField(TEXT("location"))->GetNumberField(TEXT("y"));
    Location.Z = JsonData->GetObjectField(TEXT("location"))->GetNumberField(TEXT("z"));

    FRotator Rotation;
    Rotation.Pitch = JsonData->GetObjectField(TEXT("rotation"))->GetNumberField(TEXT("pitch"));
    Rotation.Yaw = JsonData->GetObjectField(TEXT("rotation"))->GetNumberField(TEXT("yaw"));
    Rotation.Roll = JsonData->GetObjectField(TEXT("rotation"))->GetNumberField(TEXT("roll"));

    FActorSpawnParameters SpawnParams;

    ASpawnedObject* SpawnedActor = ThisWorld->SpawnActor<ASpawnedObject>(ASpawnedObject::StaticClass(), Location, Rotation, SpawnParams);
    FVector SpawnedLocation = SpawnedActor->GetActorLocation();
    UE_LOG(LogTemp, Log, TEXT("Spawned actor %s at location: %s"), *SpawnedActor->GetName(), *SpawnedLocation.ToString());

    FString MaterialPath = JsonData->GetStringField(TEXT("material_path"));
    FString MeshPath = JsonData->GetStringField(TEXT("mesh_path"));

    if (SpawnedActor) {
        UE_LOG(LogTemp, Log, TEXT("Spawned Actor initialized"));
        UStaticMeshComponent* MyMesh = NewObject<UStaticMeshComponent>(SpawnedActor);

        if (!MeshPath.IsEmpty()) {
            UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *MeshPath));
            MyMesh->SetStaticMesh(Mesh);
        }
        if (!MaterialPath.IsEmpty()) {
            UMaterial* Material = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, *MaterialPath));
            MyMesh->SetMaterial(0, Material);
        }

        if (JsonData->GetBoolField(TEXT("physics"))) {
            MyMesh->SetSimulatePhysics(true);
            MyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            MyMesh->SetCollisionProfileName(TEXT("BlockAll"));
        }

        MyMesh->SetupAttachment(SpawnedActor->GetRootComponent());
        MyMesh->RegisterComponent();

        ObjectDatabase.Add(ObjectID, SpawnedActor);
    }
    return ObjectID;
}

FString UObjectManager::DeleteObject(TSharedPtr<FJsonObject>& JsonData)
{
    FString ObjectID = JsonData->GetStringField(TEXT("object_id"));
    if (ObjectDatabase.Contains(ObjectID))
    {
        AActor* ActorToDelete = *ObjectDatabase.Find(ObjectID);
        if (ActorToDelete)
        {
            ActorToDelete->Destroy();
            ObjectDatabase.Remove(ObjectID);
            return FString("success");
        }
    }
    return FString("object not found");
}