#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraCaptureActor.generated.h"

UCLASS()
class UNREAL_5_2_API ACameraCaptureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACameraCaptureActor();
	//TArray<uint8> CaptureImage();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
