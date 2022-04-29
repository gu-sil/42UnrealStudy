// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Interactable.h"
#include "Unreal42Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#pragma region Character Override Functions

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	SkeletalMesh->SetOnlyOwnerSee(true);
	SkeletalMesh->SetupAttachment(FirstPersonCameraComponent);
	SkeletalMesh->bCastDynamicShadow = false;
	SkeletalMesh->CastShadow = false;
	SkeletalMesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	SkeletalMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Set Action Values
	InteractRange = 1000.f;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AMainCharacter::OnPrimaryAction);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AMainCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "Mouse" versions handle devices that provide an absolute delta, such as a mouse.
	// "Gamepad" versions are for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	// PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AMainCharacter::TurnAtRate);
	// PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AMainCharacter::LookUpAtRate);
}

void AMainCharacter::OnPrimaryAction()
{
	FHitResult HitResult;
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		FirstPersonCameraComponent->GetComponentLocation(),
		FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * InteractRange,
		ECollisionChannel::ECC_GameTraceChannel1,
		QueryParams
	);
	if (HitResult.GetActor())
	{
		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("%s is hit."), *HitActor->GetName());
		if (Cast<AInteractable>(HitActor))
		{
			Cast<AInteractable>(HitActor)->OnInteract();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("no hit."));
	}
}

void AMainCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

#pragma endregion