// Fill out your copyright notice in the Description page of Project Settings.


#include "ChickenFight/GA/ASC_folder/Humanoid_AbilitySystemComponent.h"

#include "ChickenFight/HumanoidCharacterBase_folder/HumanoidCharacterBase.h"


UHumanoid_AbilitySystemComponent::UHumanoid_AbilitySystemComponent()
{

}

void UHumanoid_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHumanoid_AbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	AHumanoidCharacterBase* HumanoidCharacter = Cast<AHumanoidCharacterBase>(GetOwner());

	if (HumanoidCharacter)
	{
		return;
	}

	HumanoidCharacter->SendAbilitiesChangedEvent();

}
