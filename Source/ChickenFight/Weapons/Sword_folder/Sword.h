
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sword.generated.h"

UCLASS()
class CHICKENFIGHT_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	ASword();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UStaticMeshComponent* C_StaticMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USceneComponent* C_Scene;


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
