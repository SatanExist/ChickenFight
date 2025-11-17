
#include "ChickenFight/Weapons/Sword_folder/Sword.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

ASword::ASword()
{
	PrimaryActorTick.bCanEverTick = false;

	C_Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	C_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	RootComponent = C_Scene;
	C_StaticMesh->SetupAttachment(RootComponent);

}

void ASword::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

