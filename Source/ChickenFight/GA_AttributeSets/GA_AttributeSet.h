
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"

#include "AbilitySystemComponent.h"

#include "GA_AttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 

UCLASS()
class CHICKENFIGHT_API UGA_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UGA_AttributeSet();

	// Health Attributes

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGA_AttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGA_AttributeSet, MaxHealth);

	// Stamina Attributes

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UGA_AttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UGA_AttributeSet, MaxStamina);
	
public:

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UGA_AttributeSet, Health, OldValue);
	}

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UGA_AttributeSet, MaxHealth, OldValue);
	}

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UGA_AttributeSet, Stamina, OldValue);
	}

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UGA_AttributeSet, MaxStamina, OldValue);
	}

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

};
