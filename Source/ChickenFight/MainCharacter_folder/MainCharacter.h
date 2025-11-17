
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputActionValue.h"
#include "Components/StaticMeshComponent.h"
#include "ChickenFight/HumanoidCharacterBase_folder/HumanoidCharacterBase.h"

#include "MainCharacter.generated.h"

UCLASS()
class CHICKENFIGHT_API AMainCharacter : public AHumanoidCharacterBase
{
	GENERATED_BODY()

public:
	AMainCharacter();

	// Параметры

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomMovement")
	float meshRotationSpeed = 15.0f;

	// Основные компоненты

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USpringArmComponent* C_SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UCameraComponent* C_Camera;

	// Input Components

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* MappingContext_MainPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* DashAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	UStaticMeshComponent* WeaponInRightHand;

	// Функции

	UFUNCTION()
	void Character_Move(const FInputActionValue& Value);

	UFUNCTION()
	void Character_Attack(const FInputActionValue& Value);

	UFUNCTION()
	void Character_Dash(const FInputActionValue& Value);

	UFUNCTION()
	void RotateMeshToCursor();

	UFUNCTION()
	float GetCharacterDirection() const;

	UFUNCTION()
	float GetCharacterSpeed() const;

	// Variables

	APlayerController* PC; // переменная для курсора

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
