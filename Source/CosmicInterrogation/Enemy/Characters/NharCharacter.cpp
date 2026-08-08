// Fill out your copyright notice in the Description page of Project Settings.


#include "CosmicInterrogation/Enemy/Characters/NharCharacter.h"
#include "Engine/Engine.h"

// Sets default values
ANharCharacter::ANharCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentState = ENharState::Scientific;
}

// Called when the game starts or when spawned
void ANharCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetNharState(CurrentState);

	FTimerHandle ThreateningTimerHandle;
	GetWorldTimerManager().SetTimer(ThreateningTimerHandle,this,
		&ANharCharacter::ChangeToThreatening,3.0f,false);

	FTimerHandle FearfulTimerHandle;
	GetWorldTimerManager().SetTimer(
		FearfulTimerHandle,
		this,
		&ANharCharacter::ChangeToFearful,
		6.0f,
		false
	);
	
}

// Called every frame
void ANharCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANharCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANharCharacter::SetNharState(ENharState NewState)
{
	CurrentState = NewState;

	FString StateName;
	
	switch (CurrentState)
	{

		case ENharState::Scientific:
			StateName = TEXT("Scientific");
			break;
		
		case ENharState::Threatening:
			StateName = TEXT("Threatening");
			break;

		case ENharState::Fearful:
			StateName = TEXT("Fearful");
			break;
		
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Nhar State: %s"), *StateName));
	
}

void ANharCharacter::ChangeToThreatening()
{
	SetNharState(ENharState::Threatening);
}

void ANharCharacter::ChangeToFearful()
{
	SetNharState(ENharState::Fearful);
}

