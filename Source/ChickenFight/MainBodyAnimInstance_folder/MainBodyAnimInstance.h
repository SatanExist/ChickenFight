
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainBodyAnimInstance.generated.h"


UCLASS()
class CHICKENFIGHT_API UMainBodyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float direction;

protected:

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	void CalculateMovementValues();
	
};
