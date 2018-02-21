// Fill out your copyright notice in the Description page of Project Settings.

#include "AR1.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

AAR1::AAR1()
{
	UStaticMeshComponent* Scope;
	UStaticMeshComponent* lens;
	Scope = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scope"));
	lens = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("lens"));
	
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	GunMesh->SetupAttachment(RootComponent);
	Camera->SetupAttachment(GunMesh);
	Camera->bAutoActivate = true;
	details.name = "ar1";
	details.socketname = "ar1";
	details.className = this->GetClass();
	
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Weapontest/Models/Weapons/Static/ar1_static.ar1_static'"));
	if (MeshAsset.Object)
	{
		GunMesh->SetStaticMesh(MeshAsset.Object);
	
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ScopeAsset(TEXT("StaticMesh'/Game/Weapontest/Scope/halo/edit_552_eotech_552.edit_552_eotech_552'"));
	if (ScopeAsset.Succeeded())
		Scope->SetStaticMesh(ScopeAsset.Object);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>LensAsset(TEXT("StaticMesh'/Game/Weapontest/Scope/halo/edit_552_eotech_lense.edit_552_eotech_lense'"));
	if (LensAsset.Succeeded())
		lens->SetStaticMesh(LensAsset.Object);

	Scope->AttachToComponent(GunMesh, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("scope")));
	lens->AttachToComponent(Scope, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("lens")));
	//Camera->AttachToComponent(GunMesh, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("lens")));
	
	Camera->SetRelativeLocation(FVector(0, 10.5, 18));
	Camera->SetRelativeRotation(FRotator(0, 90, 0));
	Camera->SetFieldOfView(60);


	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetObj(TEXT("UserWidget'/Game/HUD/Dot.Dot_C'"));

	if (WidgetObj.Succeeded())
		sight->SetWidgetClass(WidgetObj.Class);
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

	
	
	

   

}


