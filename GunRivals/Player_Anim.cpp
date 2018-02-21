// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_Anim.h"

#include "Kismet/KismetMathLibrary.h"


void UPlayer_Anim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	 Pawn = TryGetPawnOwner();

}

void UPlayer_Anim::NativeUpdateAnimation(float deltaSecond)
{
	Super::NativeUpdateAnimation(deltaSecond);
	if (Pawn)
	{
		APlayer_Character* player = (APlayer_Character*)Pawn;
		if (player)
		{
			FVector velocity = Pawn->GetVelocity();
			FRotator rotation = Pawn->GetControlRotation();
			Speed = velocity.Size();
			Direction = CalculateDirection(velocity, rotation);
			FRotator playerRotationWithCamera = UKismetMathLibrary::NormalizedDeltaRotator(player->GetControlRotation(), player->GetActorRotation());
			yaw = playerRotationWithCamera.Yaw;
			pitch = playerRotationWithCamera.Pitch;
			isCrouch = player->isCrouch;
			isSprint = player->isSprint;
			isProne = player->isProne;


		}

	}
}


