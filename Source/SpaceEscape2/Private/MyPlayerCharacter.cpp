// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessPlayer = EAutoReceiveInput::Player2;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));
	MeshComp->SetupAttachment(RootComponent);

	BaseTurnRate = 45.0f;
	BaseLookUpAtRate = 45.0f;
	OxygenLevel = 100.0f;
	PlayerMovable = false;
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;
	IsPressing = true;
}

void AMyPlayerCharacter::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		IsPressing = true;
	}
}

void AMyPlayerCharacter::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), TestSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

/*void AMyPlayerCharacter::TurnRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	CameraUpTest = Value * BaseTurnRate * GetWorld()->GetDeltaSeconds();
}

void AMyPlayerCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
	

}*/

void AMyPlayerCharacter::LookUpAt(float Value)
{
	//CameraLookVertical = Value + CameraLookVertical / 0.5;
	//const FRotator Rotation = FRotator(0.0f, CameraLookVertical, 0.0f);
	//CameraComp->SetRelativeRotation(Rotation);
	//const FRotator Rotation = AddControllerPitchInput();
	//const FRotator YawRotation = (0, Rotation.Yaw, 0);


}
// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	//TO BE LOOKED INTO I GUESS
	//SkeletalMesh->PlayAnimation(Player_Idle_Anim, true);

	CurrentLevelName = GetWorld()->GetName();
	if (CurrentLevelName != "Title" && CurrentLevelName != "Typewriter")
	{
		
		
	}

}


//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FRotator CameraRotation = FRotator(0.0f, CameraLookVertical, 0.0f);
	

	//SpringArmComp->SetRelativeRotation(CameraRotation);
	
	OxygenLevel = OxygenLevel - 1.0f;
}

// Called to bind functionality to input
void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMyPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpAt", this, &AMyPlayerCharacter::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &AMyPlayerCharacter::TurnRate);
	//PlayerInputComponent->BindAxis("LookUpAtRate", this, &AMyPlayerCharacter::LookUpAtRate);
}

