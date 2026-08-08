// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CosmicInterrogation/Dev/DevUtils.h"
#include "NharCharacter.generated.h"

class USphereComponent;
class ACosmicInterrogationCharacter;

UCLASS()
class COSMICINTERROGATION_API ANharCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANharCharacter();
	


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Dev")
	ENharState CurrentState;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Props)
	TObjectPtr<USphereComponent> DetectionSphere = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Props)
	bool bIsPlayerNearby = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Props)
	float PlayerDistance = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Props)
	float PlayerSpeed = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Props)
	bool bIsPlayerApproaching = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Props)
	float TimeNearPlayer = 0.0f;


	UPROPERTY()
	float PreviousPlayerDistance = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Props)
	float SphereRadius = 500.0f;

	UPROPERTY()
	ACosmicInterrogationCharacter* PlayerCharacter = nullptr;

	UPROPERTY()
	ACosmicInterrogationCharacter* DetectedPlayer = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	void SetNharState(ENharState NewState);

	void ChangeToThreatening();

	void ChangeToFearful();

	UFUNCTION()
	void OnDetectionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnDetectionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdatePlayerSensors(float DeltaTime);
	
	void EvaluateState();
};
