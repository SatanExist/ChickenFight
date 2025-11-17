
#include "ChickenFight/Enemies/SkeletonWarrior_folder/Enemy_SkeletonWarrior.h"

AEnemy_SkeletonWarrior::AEnemy_SkeletonWarrior()
{

	PrimaryActorTick.bCanEverTick = false;

}

void AEnemy_SkeletonWarrior::BeginPlay()
{
	Super::BeginPlay();

	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
	{
		
	}
	
}

void AEnemy_SkeletonWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

