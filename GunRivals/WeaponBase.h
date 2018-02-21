// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/WidgetComponent.h"
#include "WeaponBase.generated.h"


USTRUCT(BlueprintType)
struct FItemDetails
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int capacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName socketname;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* className;
	

};

UCLASS()
class GUNRIVALS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* GunMesh;

	

	void fire(bool ironSight);
	void reload();
	void pickUp();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "detail")
		FItemDetails details;
	

	

	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* sight;

	
		
   

};

