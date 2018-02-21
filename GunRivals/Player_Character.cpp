// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/SkeletalMeshSocket.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AR1.h"



// Sets default values
APlayer_Character::APlayer_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isCrouch = false;
	isProne = false;
	isSprintEnable = false;
	isSprint = false;
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/Character/Swat1/Swat1.Swat1'"));
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimBlueprint>AnimClass(TEXT("AnimBlueprint'/Game/BluePrint/AnimBp.AnimBp'"));
	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Object->GetAnimBlueprintGeneratedClass());
	
	GetMesh()->SetRelativeLocation(FVector(0, 0, -86.695686));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0,0,71));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeLocation(FVector(-24,0,0));

	Camera->bUsePawnControlRotation = true;
	SpringArm->bUsePawnControlRotation = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	this->bUseControllerRotationYaw = false;
	
	Camera->bAutoActivate = true;

}

// Called when the game starts or when spawned
void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
	AAR1* Weapon = NewObject<AAR1>();
    WeaponAttach(Weapon);
	
	
	
	
}

// Called every frame
void APlayer_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void APlayer_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &APlayer_Character::forward);
	PlayerInputComponent->BindAxis("Right", this, &APlayer_Character::right);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_Character::lookup);
	PlayerInputComponent->BindAxis("LookRight", this, &APlayer_Character::lookright);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayer_Character::crouch);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayer_Character::startSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayer_Character::stopSprint);
	PlayerInputComponent->BindAction("Prone", IE_Pressed, this, &APlayer_Character::prone);
	PlayerInputComponent->BindAction("IronSight", IE_Pressed, this, &APlayer_Character::ironSightActivate);
	PlayerInputComponent->BindAction("IronSight", IE_Released, this, &APlayer_Character::ironSightDeactivate);

	PlayerInputComponent->BindAxis("TurnRate", this, &APlayer_Character::turnrate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayer_Character::lookuprate);
}




void APlayer_Character::startSprint()
{
	if (!isProne)
	{
		isSprint = true;
		GetCharacterMovement()->MaxWalkSpeed = 1000;
	}
	
}

void APlayer_Character::stopSprint()
{
	if (!isProne)
	{
		isSprint = false;
		if(!isCrouch)
		GetCharacterMovement()->MaxWalkSpeed = 600;
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 400;
		}
	}
}

void APlayer_Character::crouch()
{   
	if (isProne)
		isProne = false;


	isCrouch = !isCrouch;
	if (isCrouch)
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}

void APlayer_Character::forward(float AxisValue)
{
	
	FRotator rotation = UKismetMathLibrary::MakeRotator(0, 0,GetControlRotation().Yaw);
	FVector direction = UKismetMathLibrary::GetForwardVector(rotation);
	AddMovementInput(direction, AxisValue);


}

void APlayer_Character::right(float AxisValue)
{
	
	FRotator rotation = UKismetMathLibrary::MakeRotator(0, 0, GetControlRotation().Yaw);
	FVector direction = UKismetMathLibrary::GetRightVector(rotation);
	AddMovementInput(direction, AxisValue);


}

void APlayer_Character::ironSightActivate()
{
	if (weapon)
	{
		
		//Camera->Deactivate();
        controller=UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->SetViewTarget(weapon);
	}
}

void APlayer_Character::ironSightDeactivate()
{
	if (weapon)
	{
		controller->SetViewTarget(this);


	}
}

void APlayer_Character::prone()
{
	if (isCrouch)
		isCrouch = false;
	isProne = !isProne;
	if (isProne)
		GetCharacterMovement()->MaxWalkSpeed = 100;
	else
		GetCharacterMovement()->MaxWalkSpeed = 600;
}

void APlayer_Character::lookup(float AxisValue)
{
	AddControllerPitchInput(AxisValue);


}

void APlayer_Character::lookright(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayer_Character::turnrate(float AxisValue)
{
	AddControllerYawInput(AxisValue*BaseTurnRate*UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));

}

void APlayer_Character::lookuprate(float AxisValue)
{
	AddControllerPitchInput(AxisValue*BaseLookUpRate*UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));
}

void APlayer_Character::WeaponAttach(AWeaponBase* Weapon)
{
	weapon = Weapon;
	
	FActorSpawnParameters spawninfo;
	FVector Location = GetMesh()->GetSocketLocation("ar1");
	FRotator Rotator = GetMesh()->GetSocketRotation("ar1");
	weapon = GetWorld()->SpawnActor<AWeaponBase>(Weapon->details.className,this->GetActorLocation(),this->GetActorRotation(), spawninfo);
	
	(weapon->GunMesh)->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, weapon->details.socketname);
	//weapon->AttachRootComponentToActor(this, weapon->details.socketname, EAttachLocation::SnapToTarget);
	weapon->SetActorEnableCollision(false);
	
	
}
