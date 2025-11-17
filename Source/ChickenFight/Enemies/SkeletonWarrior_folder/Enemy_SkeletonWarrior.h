
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ChickenFight/HumanoidCharacterBase_folder/HumanoidCharacterBase.h"

#include "Enemy_SkeletonWarrior.generated.h"

UCLASS()
class CHICKENFIGHT_API AEnemy_SkeletonWarrior : public AHumanoidCharacterBase
{
	GENERATED_BODY()
	
public:	
	AEnemy_SkeletonWarrior();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
