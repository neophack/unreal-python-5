// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"

UObjectManager::UObjectManager()
{

};

void UObjectManager::InitializeWorld(UWorld* World)
{
	ThisWorld = World;
};

FString UObjectManager::SpawnObject(TSharedPtr<FJsonObject>& JsonData)
{
    //TODO: Keep track of unique object_id in ObjectDatabase

    // Implementation of SpawnObject method
    UE_LOG(LogTemp, Log, TEXT("Spawn Object called"));
    //FString ObjectClassString = JsonObject->GetStringField(TEXT("object_class"));
    //UClass* ObjectClass = FindObject<UClass>(ANY_PACKAGE, *ObjectClassString);

    FVector Location;
    Location.X = JsonData->GetObjectField(TEXT("location"))->GetNumberField(TEXT("x"));
    Location.Y = JsonData->GetObjectField(TEXT("location"))->GetNumberField(TEXT("y"));
    Location.Z = JsonData->GetObjectField(TEXT("location"))->GetNumberField(TEXT("z"));

    FRotator Rotation;
    Rotation.Pitch = JsonData->GetObjectField(TEXT("rotation"))->GetNumberField(TEXT("pitch"));
    Rotation.Yaw = JsonData->GetObjectField(TEXT("rotation"))->GetNumberField(TEXT("yaw"));
    Rotation.Roll = JsonData->GetObjectField(TEXT("rotation"))->GetNumberField(TEXT("roll"));
    // Convert FVector and FRotator to FString
    FString LocationString = Location.ToString();
    FString RotationString = Rotation.ToString();

    // Log the values using UE_LOG
    UE_LOG(LogTemp, Log, TEXT("Location: %s"), *LocationString);
    UE_LOG(LogTemp, Log, TEXT("Rotation: %s"), *RotationString);
    FActorSpawnParameters SpawnParams;

    AActor* SpawnedActor = ThisWorld->SpawnActor<AActor>(AActor::StaticClass(), Location, Rotation, SpawnParams);
    FVector ActualLocation = SpawnedActor->GetActorLocation();

    UE_LOG(LogTemp, Log, TEXT("Actual Location: %s"), *ActualLocation.ToString());


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
        //Set additional properties for the mesh component
        MyMesh->SetSimulatePhysics(true);
        MyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        MyMesh->SetCollisionProfileName(TEXT("BlockAll"));

        //Attach the mesh component to the actor's root component
        MyMesh->SetupAttachment(SpawnedActor->GetRootComponent());
        MyMesh->RegisterComponent();
    }
    return FString("success");
}