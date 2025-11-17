
#include "ChickenFight/MainBodyAnimInstance_folder/MainBodyAnimInstance.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"
#include "ChickenFight/MainCharacter_folder/MainCharacter.h"

void UMainBodyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CalculateMovementValues();
}

void UMainBodyAnimInstance::CalculateMovementValues()
{
	APawn* owningPawn = this->TryGetPawnOwner();

	if (!owningPawn)
	{
		return;
	}

	AMainCharacter* mainCharacter = Cast<AMainCharacter>(owningPawn);

	if (!mainCharacter)
	{
		return;
	}

	// Рассчёт скорости

	FVector velocity = mainCharacter->GetVelocity();
	FVector velocity2D = FVector(velocity.X, velocity.Y, 0.0f);
	speed = velocity2D.Size();

	// Рассчёт направления

	if (speed > SMALL_NUMBER)
	{
		FRotator meshRotation = mainCharacter->GetMesh()->GetComponentRotation();
		meshRotation.Yaw += 90.0f;
		direction = UKismetAnimationLibrary::CalculateDirection(velocity2D, meshRotation);
	}
	else
	{
		direction = 0.0f;
	}


}
