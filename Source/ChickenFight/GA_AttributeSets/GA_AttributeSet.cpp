
#include "ChickenFight/GA_AttributeSets/GA_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UGA_AttributeSet::UGA_AttributeSet()
{
	Health = 100.0f;
	MaxHealth = 100.0f;
	Stamina = 100.0f;
	MaxStamina = 100.0f;
}

void UGA_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGA_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGA_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGA_AttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGA_AttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void UGA_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}
}

void UGA_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(GetStamina());
	}
}
