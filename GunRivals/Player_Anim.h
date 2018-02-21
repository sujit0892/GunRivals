// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Player_Character.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "Player_Anim.generated.h"

/**
 * 
 */
UCLASS()
class GUNRIVALS_API UPlayer_Anim : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float deltaSecond) override;
	virtual void NativeInitializeAnimation() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Direction;
	
	APawn* Pawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float yaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isCrouch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isSprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isProne;
	
};
