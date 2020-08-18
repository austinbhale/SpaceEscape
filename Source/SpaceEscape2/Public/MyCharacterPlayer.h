// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/Actor.h"
#include "MyCharacterPlayer.generated.h"



class USpringArmComponent;
class UCameraComponent;
class APlayerCameraManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeadUI);

UCLASS()
class SPACEESCAPE2_API AMyCharacterPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacterPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		USkeletalMeshComponent* MeshComp;

	APlayerCameraManager* PlayerCam;

public: 

	float SetViewPitchMin(float Input);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		float OxygenLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		float CameraLookVertical;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		float CameraUpTest;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		FString CurrentLevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		USoundBase* TestSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		UObject* PlayerUI;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool PlayerMovable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool IsPressing;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		float PlayerStayPitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		UClass* DeathPawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		APawn* DeathPawnObject;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool AbleToPickUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		bool PickedUpKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		bool DecreaseOxygen;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool PlaySound;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool EnableTicking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool PlayerDead;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool Moving;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool MovingX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool MovingY;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool TestBool;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		float TestVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		int AnimationCall;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		int DeathCall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		UAnimSequence* WalkAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		UAnimSequence* IdleAnimation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		FVector CurrentVelocity;

	UPROPERTY(BlueprintAssignable, Category = "Test")
		FDeadUI DeadUICall;

	FTimerHandle DelayTimer;
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<APawn> ActorToSpawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUpAt(float Value);
	void DelayReset();
	void PlayerDeath();

	void WalkingAnimation();
	void StandingAnimation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: void UIStuff();
};
