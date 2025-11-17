
#include "ChickenFight/HumanoidCharacterBase_folder/HumanoidCharacterBase.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "ChickenFight/GA_AttributeSets/GA_AttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ChickenFight/GA/ASC_folder/Humanoid_AbilitySystemComponent.h"


AHumanoidCharacterBase::AHumanoidCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ASC_AbilitySystemComponent = CreateDefaultSubobject<UHumanoid_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ASC_AbilitySystemComponent->SetIsReplicated(true);
	ASC_AbilitySystemComponent->SetReplicationMode(ASC_replicationMode);

	GA_AS_AttributeSet = CreateDefaultSubobject<UGA_AttributeSet>(TEXT("GA_AS_AttributeSet"));

}

void AHumanoidCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHumanoidCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ASC_AbilitySystemComponent)
	{
		ASC_AbilitySystemComponent->InitAbilityActorInfo(this, this);

		GrantAbilities(InitialAbilities);
    }
}

void AHumanoidCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (ASC_AbilitySystemComponent)
	{
		ASC_AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AHumanoidCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHumanoidCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AHumanoidCharacterBase::GetAbilitySystemComponent() const
{
	return ASC_AbilitySystemComponent;
}

TArray<FGameplayAbilitySpecHandle> AHumanoidCharacterBase::GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	if (!ASC_AbilitySystemComponent || !HasAuthority())
	{
		return TArray<FGameplayAbilitySpecHandle>();
	}

	TArray<FGameplayAbilitySpecHandle> AbilityHandles;
	for (TSubclassOf<UGameplayAbility> Ability : AbilitiesToGrant)
	{
		FGameplayAbilitySpecHandle SpecHandle = ASC_AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, -1, this));
		AbilityHandles.Add(SpecHandle);
	}

	SendAbilitiesChangedEvent();
	return AbilityHandles;
}

void AHumanoidCharacterBase::RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove)
{
	if (!ASC_AbilitySystemComponent || !HasAuthority())
	{
		return;
	}

	for (FGameplayAbilitySpecHandle AbilityHandle : AbilityHandlesToRemove)
	{
		ASC_AbilitySystemComponent->ClearAbility(AbilityHandle);
	}

	SendAbilitiesChangedEvent();
}

void AHumanoidCharacterBase::SendAbilitiesChangedEvent()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("Event.Abilities.Changed"));
	EventData.Instigator = this;
	EventData.Target = this;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}

