// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SPACEESCAPE2_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		USkeletalMeshComponent* MeshComp;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		float OxygenLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		float CameraLookVertical;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		float CameraUpTest;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		FString CurrentLevelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inherited Variables")
		USoundBase* TestSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool PlayerMovable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inherited Variables")
		bool IsPressing;

protected:
	// Called when the game starts or when spawned
	
	virtual void BeginPlay() override;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	//void TurnRate(float Value);
	//void LookUpAtRate(float Value);
	void LookUpAt(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		float BaseLookUpAtRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
