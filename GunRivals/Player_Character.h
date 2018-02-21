// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/Character.h"
#include "Player_Character.generated.h"

UCLASS()
class GUNRIVALS_API APlayer_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool isSprint;
	bool isCrouch;
	bool isProne;
	bool isSprintEnable; 
	
	AWeaponBase* weapon;

	void startSprint();
	void stopSprint();
	void crouch();
	void forward(float AxisValue);

	void right(float AxisValue);
	void ironSightActivate();
	void ironSightDeactivate();
	//void fire();
	//void reload();

	void prone();

	void lookup(float AxisValue);
	void lookright(float AxisValue);
	void turnrate(float AxisValue);
	void lookuprate(float AxisValue);
	
	float BaseTurnRate;
	float BaseLookUpRate;

	UFUNCTION()
	void WeaponAttach(AWeaponBase* Weapon);


	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	APlayerController* controller;
};
