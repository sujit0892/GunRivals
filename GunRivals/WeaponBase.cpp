// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "Player_Character.h"
#include "Scope.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	CollisionBox = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = CollisionBox;
	
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	sight = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));



}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{

	Super::BeginPlay();

	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::fire(bool ironSight)
{
     
}

void AWeaponBase::reload()
{

}

void AWeaponBase::pickUp()
{

}



