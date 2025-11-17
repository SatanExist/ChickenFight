
#include "ChickenFight/MainCharacter_folder/MainCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "ChickenFight/GA_AttributeSets/GA_AttributeSet.h"

FAttachmentTransformRules AttachmentRules(
    EAttachmentRule::SnapToTarget,    // Позиция: Сбросить и привязать ТОЧНО к сокету
    EAttachmentRule::SnapToTarget,    // Вращение: Сбросить и привязать ТОЧНО к сокету
    EAttachmentRule::KeepRelative,    // Масштаб: Использовать ТОЛЬКО свой собственный масштаб (обычно 1,1,1)
    false
);

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	C_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	C_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    WeaponInRightHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon_R"));

	C_SpringArm->SetupAttachment(RootComponent);
    C_Camera->SetupAttachment(C_SpringArm); 
}

void AMainCharacter::Character_Move(const FInputActionValue& Value)
{
    // 1. Получаем вектор движения от Input Action
    FVector2D MovementVector = Value.Get<FVector2D>();

    // 2. Получаем направление вперед от камеры
    FVector ForwardDirection = C_Camera->GetForwardVector();
    ForwardDirection.Z = 0.0f;
    ForwardDirection.Normalize();

    // 3. Получаем направление вправо от камеры
    FVector RightDirection = C_Camera->GetRightVector();
    RightDirection.Z = 0.0f;
    RightDirection.Normalize();

    // 4. Создаем CombinedMovementDirection с векторами с камеры
    FVector CombinedMovementDirection = ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X;
    CombinedMovementDirection.Normalize();

    // 9. Добавляем перемещение персонажа
    AddMovementInput(CombinedMovementDirection, 1.0f); // ScaleValue = 1.0f
}

void AMainCharacter::Character_Attack(const FInputActionValue& Value)
{
    if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
    {
        FGameplayTag attackTag = FGameplayTag::RequestGameplayTag(FName("GameplayAbility.MeleeWeapon.SimpleMeleeAttack"));
        FGameplayTagContainer attackTagContainer;
        attackTagContainer.AddTag(attackTag);
        ASC->TryActivateAbilitiesByTag(attackTagContainer, true);
    }
}

void AMainCharacter::Character_Dash(const FInputActionValue& Value)
{
    if (UAbilitySystemComponent* ASC = GetAbilitySystemComponent())
    {
        FGameplayTag dashTag = FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Movement.Dash"));
        FGameplayTagContainer dashTagContainer;
        dashTagContainer.AddTag(dashTag);
        ASC->TryActivateAbilitiesByTag(dashTagContainer, true);
    }
}

void AMainCharacter::RotateMeshToCursor()
{
    FHitResult HR_cursor;
    PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HR_cursor);
    if (HR_cursor.bBlockingHit)
    {
        FVector targetLocation = HR_cursor.Location;
        FVector lookDirection = targetLocation - this->GetActorLocation();
        lookDirection.Z = 0.0f;
        lookDirection.Normalize();
        FRotator meshDesiredRotation = FRotationMatrix::MakeFromX(lookDirection).Rotator();
        FRotator correctedRotation = meshDesiredRotation + FRotator(0.0f, -90.0f, 0.0f);
        FRotator currentRotation = GetMesh()->GetRelativeRotation(); 
        FRotator meshNewRotation = FMath::RInterpTo(currentRotation, correctedRotation, GetWorld()->GetDeltaSeconds(), meshRotationSpeed);
        this->GetMesh()->SetRelativeRotation(meshNewRotation);

    }
}

float AMainCharacter::GetCharacterDirection() const
{
    return 0.0f;
}

float AMainCharacter::GetCharacterSpeed() const
{
    return 0.0f;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
    this->SetActorTickEnabled(false);

    // Enable IMC ( Movement )

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(MappingContext_MainPlayer, 1);
        }
    }

    // Enable cursor

    PC = GetController<APlayerController>();
    if (PC)
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeGameOnly());
    }

    this->SetActorTickEnabled(true);
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    RotateMeshToCursor();
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Character_Move);
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMainCharacter::Character_Attack);
        EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AMainCharacter::Character_Dash);
    }

}

