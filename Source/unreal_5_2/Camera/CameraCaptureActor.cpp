#include "CameraCaptureActor.h"
#include "Camera/CameraComponent.h"
#include "Engine/SceneCapture2D.h"
#include "Engine/TextureRenderTarget2D.h"

ACameraCaptureActor::ACameraCaptureActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACameraCaptureActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraCaptureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//TArray<uint8> ACameraCaptureActor::CaptureImage()
//{
//	return
//}

