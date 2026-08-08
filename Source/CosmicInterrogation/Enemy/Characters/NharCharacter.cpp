// Fill out your copyright notice in the Description page of Project Settings.


#include "CosmicInterrogation/Enemy/Characters/NharCharacter.h"
#include "Engine/Engine.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "CosmicInterrogation/CosmicInterrogationCharacter.h"
#include "Preferences/PersonaOptions.h"

// Sets default values
ANharCharacter::ANharCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	DetectionSphere->SetupAttachment(GetRootComponent());
	DetectionSphere->SetSphereRadius(SphereRadius);

	CurrentState = ENharState::Scientific;
}

// Called when the game starts or when spawned
void ANharCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(DetectionSphere);

	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnDetectionBeginOverlap);

	DetectionSphere->OnComponentEndOverlap.AddDynamic(this,&ThisClass::OnDetectionEndOverlap);

	//SetNharState(CurrentState);

	/*FTimerHandle ThreateningTimerHandle;
	GetWorldTimerManager().SetTimer(ThreateningTimerHandle,this,
		&ANharCharacter::ChangeToThreatening,3.0f,false);

	FTimerHandle FearfulTimerHandle;
	GetWorldTimerManager().SetTimer(
		FearfulTimerHandle,
		this,
		&ANharCharacter::ChangeToFearful,
		6.0f,
		false
	);*/
	
}

// Called every frame
void ANharCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePlayerSensors(DeltaTime);

}

// Called to bind functionality to input
void ANharCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANharCharacter::SetNharState(ENharState NewState)
{

	if (CurrentState == NewState)
	{
		return;
	}

	
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

void ANharCharacter::OnDetectionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerCharacter = Cast<ACosmicInterrogationCharacter>(OtherActor);

	if (PlayerCharacter)
	{

		bIsPlayerNearby = true;

		DetectedPlayer = PlayerCharacter;


		PlayerDistance = FVector::Dist(GetActorLocation(), DetectedPlayer->GetActorLocation());

		PreviousPlayerDistance = PlayerDistance;

		TimeNearPlayer = 0.0f;

		

		DrawDebugSphere(GetWorld(),GetActorLocation(),SphereRadius,20,FColor::Orange,false,1.0f);
	}
}

void ANharCharacter::OnDetectionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != DetectedPlayer)
	{
		return;
	}

	DetectedPlayer = nullptr;
	
	bIsPlayerNearby = false;
	PlayerDistance = 0.0f;
	PlayerSpeed = 0.0f;
	bIsPlayerApproaching = false;
	TimeNearPlayer = 0.0f;

	EvaluateState();

	
}

void ANharCharacter::UpdatePlayerSensors(float DeltaTime)
{
	if (!bIsPlayerNearby || !DetectedPlayer)
	{
		return;
	}

	TimeNearPlayer += DeltaTime;

	PlayerDistance = FVector::Dist(GetActorLocation(), DetectedPlayer->GetActorLocation());

	PlayerSpeed = DetectedPlayer->GetVelocity().Size();

	bIsPlayerApproaching = PlayerDistance < PreviousPlayerDistance;

	PreviousPlayerDistance = PlayerDistance;

	EvaluateState();
}

void ANharCharacter::EvaluateState()
{

	if (!bIsPlayerNearby)
	{
		SetNharState(ENharState::Scientific);
		return;
	}

	if (PlayerDistance < 200.0f && PlayerSpeed > 300.0f && bIsPlayerNearby)
	{
		SetNharState(ENharState::Threatening);
		return;
	}

	if (TimeNearPlayer > 8.0f)
	{
		SetNharState(ENharState::Fearful);
		return;
	}

	SetNharState(ENharState::Scientific);

	
	/*if (bIsPlayerNearby)
	{
		SetNharState(ENharState::Threatening);
	}else
	{
		SetNharState(ENharState::Scientific);
	}*/

	GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Cyan,FString::Printf(
	TEXT("Distance: %.1f | Speed: %.1f | Approaching: %s | Time: %.1f"),
	PlayerDistance,
	PlayerSpeed,
	bIsPlayerApproaching ? TEXT("True") : TEXT("False"),
	TimeNearPlayer
	));

	
}

