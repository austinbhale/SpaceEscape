// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/PrimitiveComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCharacterPlayer::AMyCharacterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	MeshComp->SetupAttachment(RootComponent);

	OxygenLevel = 100.0f;
	PlayerMovable = false;
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;
	IsPressing = true;
	PickedUpKey = false;
	PlayerMovable = false;
	Moving = false;
	AnimationCall = 2;
}

void AMyCharacterPlayer::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f) && PlayerMovable == true)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		IsPressing = true;
	}
}

void AMyCharacterPlayer::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f) && PlayerMovable == true)
	{
		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacterPlayer::LookUpAt(float Value)
{
	FRotator NewRotation = SpringArmComp->GetComponentRotation();
	CameraLookVertical += NewRotation.Pitch;
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + Value, -25.0f, 25.0f);
	SpringArmComp->SetWorldRotation(NewRotation);
	
	/*if (CameraLookVertical > 35.0f)
	{
		CameraLookVertical = 35.0f;
	}
	else if (CameraLookVertical < -35.0f)
	{
		CameraLookVertical = -35.0f;
	}*/
	
	//const FRotator YawRotation = (0, Rotation.Yaw, 0);


}
void AMyCharacterPlayer::DelayReset()
{
	PlayerMovable = true;
	DecreaseOxygen = true;
	GetWorldTimerManager().ClearTimer(DelayTimer);
}
void AMyCharacterPlayer::PlayerDeath()
{
	//MeshComp->SetSimulatePhysics(true);
	MeshComp->DestroyComponent(false);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
	PlayerMovable = false;
	DeadUICall.Broadcast();

	const FVector Location = CameraComp->GetComponentLocation();
	const FRotator Rotation = CameraComp->GetComponentRotation();

	DeathPawnObject = GetWorld()->SpawnActor<APawn>(ActorToSpawn, Location, Rotation);
	Controller->Possess(DeathPawnObject);
//	const FActorSpawnParameters SpawnParameters;
	//const FActorSpawnParameters SpawnParameters;
	//const FTransform CameraTransform =  CameraComp->GetComponentTransform();
	//const FVector CameraLocation =  CameraComp->GetComponentLocation();
	//const FRotator CameraRotation =  CameraComp->GetComponentRotation();
	//GetWorld()->SpawnActor<DeathPawn>(DeathPawn, CameraLocation, CameraRotation);
	//UWidgetBlueprintLibrary::GetAllWidgetsOfClass()
}
void AMyCharacterPlayer::WalkingAnimation()
{
		MeshComp->PlayAnimation(WalkAnimation, true);
}
void AMyCharacterPlayer::StandingAnimation()
{
		MeshComp->PlayAnimation(IdleAnimation, true);
}
float AMyCharacterPlayer::SetViewPitchMin(float Input)
{
	return 0.0f;
}
// Called when the game starts or when spawned
void AMyCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	//maybe if its broken:
	//SkeletalMesh->PlayAnimation(Player_Idle_Anim, true);
	//FRotator BattaBing = FRotator(0.0f, 0.0f, 0.0f);
	//PlayerCam->LimitViewPitch(BattaBing, -25.0f, 25.0f);

	CurrentLevelName = GetWorld()->GetName();
	if (CurrentLevelName != "Title" && CurrentLevelName != "Typewriter")
	{
		GetWorldTimerManager().SetTimer(DelayTimer, this, &AMyCharacterPlayer::DelayReset, 2.0f, false);
		EnableTicking = true;
	}
}

// Called every frame
void AMyCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
/*
	CAMERA STUFF!!!!
	const FRotator CameraRotation = CameraComp->GetRelativeRotation();
	CameraLookVertical = CameraRotation.Pitch;
	CameraComp->SetRelativeRotation(FRotator(CameraRotation));
*/
	//PlayerRotation == MeshComp->GetRelativeRotation();
	CurrentVelocity = AMyCharacterPlayer::GetVelocity();
	
	if (CurrentLevelName != "Title" && CurrentLevelName != "Typewriter")
	{
		if (EnableTicking == true)
		{
			//Insert the CameraVertical stuff here
			if (DecreaseOxygen == true)
			{
				OxygenLevel = OxygenLevel - 0.2f;
				if (OxygenLevel <= 0.0f)
				{
					if (PlayerDead == false)
					{
						PlayerDead = true;
						PlayerDeath();
						Moving = false;
					}
				}
				else if (OxygenLevel > 100.0f)
				{
					OxygenLevel = 100.0f;
				}
				else
				{
					if (CurrentVelocity.X == 0.0f && CurrentVelocity.Y == 0.0f)
					{
						Moving = false;
					}
					if (CurrentVelocity.X != 0.0f || CurrentVelocity.Y != 0.0f)
					{
						Moving = true;
					}
					if (!Moving && AnimationCall == 2)
					{
						StandingAnimation();
						AnimationCall = 1;
					}
					if (Moving && AnimationCall == 1)
					{
						WalkingAnimation();
						AnimationCall = 2;
					}					
				}
			}
		}
	}
	//SpringArmComp->SetRelativeRotation(CameraRotation);
	//IF PITCH ROTATION OF ACTOR IS !0, MAKE IT 0 !!!!
}

// Called to bind functionality to input
void AMyCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacterPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacterPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacterPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpAt", this, &AMyCharacterPlayer::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpAt", this, &AMyCharacterPlayer::LookUpAt);
}

