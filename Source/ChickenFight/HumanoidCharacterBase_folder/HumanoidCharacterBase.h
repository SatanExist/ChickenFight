
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

#include "ChickenFight/GA_AttributeSets/GA_AttributeSet.h"

#include "HumanoidCharacterBase.generated.h"

UCLASS()
class CHICKENFIGHT_API AHumanoidCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHumanoidCharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> InitialAbilities;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AbilitySystem")
	UAbilitySystemComponent* ASC_AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AbilitySystem")
	class UGA_AttributeSet* GA_AS_AttributeSet;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	EGameplayEffectReplicationMode ASC_replicationMode = EGameplayEffectReplicationMode::Mixed;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	TArray<FGameplayAbilitySpecHandle> GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	void RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	void SendAbilitiesChangedEvent();

};
