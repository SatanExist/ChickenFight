
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Base.generated.h"

UCLASS()
class CHICKENFIGHT_API UGA_Base : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	bool isShouldShowInAbilitiesBar = false;
	
};
