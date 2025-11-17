// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Humanoid_AbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta = (BlueprintSpawnableComponent))
class CHICKENFIGHT_API UHumanoid_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	UHumanoid_AbilitySystemComponent();

	virtual void BeginPlay() override;

	void OnRep_ActivateAbilities() override;
	
};
