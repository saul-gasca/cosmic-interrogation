// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CosmicInterrogation/Dev/DevUtils.h"
#include "NharCharacter.generated.h"

UCLASS()
class COSMICINTERROGATION_API ANharCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANharCharacter();


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Dev")
	ENharState CurrentState;

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

};
