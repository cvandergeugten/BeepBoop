// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoopAdventureCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACoopAdventureCharacter

ACoopAdventureCharacter::ACoopAdventureCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	bPauseMenuIsOpen = false;
	bEmoteMenuIsOpen = false;

	// Initialize emote states
	bIsWaving = false;
	bIsTutDancing = false;
	bIsCelebrating = false;
	bIsDoingPushup = false;
	bIsDoingJumpingJack = false;
	bIsDoingBackflip = false;
}

void ACoopAdventureCharacter::SetMappingContext(UInputMappingContext* MappingContext)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void ACoopAdventureCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACoopAdventureCharacter, bIsWaving);
	DOREPLIFETIME(ACoopAdventureCharacter, bIsTutDancing);
	DOREPLIFETIME(ACoopAdventureCharacter, bIsCelebrating);
	DOREPLIFETIME(ACoopAdventureCharacter, bIsDoingPushup);
	DOREPLIFETIME(ACoopAdventureCharacter, bIsDoingJumpingJack);
	DOREPLIFETIME(ACoopAdventureCharacter, bIsDoingBackflip);
}




void ACoopAdventureCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}


}



//////////////////////////////////////////////////////////////////////////
// Input

void ACoopAdventureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACoopAdventureCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACoopAdventureCharacter::Look);

		// Pause Menu
		EnhancedInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Started, this, &ACoopAdventureCharacter::PauseMenu);

		// Emote Menu
		EnhancedInputComponent->BindAction(EmoteMenuAction, ETriggerEvent::Started, this, &ACoopAdventureCharacter::EmoteMenu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ACoopAdventureCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACoopAdventureCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACoopAdventureCharacter::PauseMenu(const FInputActionValue& Value)
{
	// THIS IS A MULTIPLAYER GAME SO YOU CANNOT STOP THE SIMULATION
	
	/*
	*  This function should only open and close the pause menu. The 
	*  logic associated with menu buttons and sliders should be
	*  handled inside the Widget Blueprint
	*/

	// This variable is being referenced in BP
	bPauseMenuIsOpen = !bPauseMenuIsOpen;

	if (bPauseMenuIsOpen)
	{
		SetMappingContext(PauseMenuMappingContext);
	}
	else
	{
		SetMappingContext(DefaultMappingContext);
	}

}

void ACoopAdventureCharacter::EmoteMenu(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("EmoteMenu"));

	bEmoteMenuIsOpen = !bEmoteMenuIsOpen;

	if (bEmoteMenuIsOpen)
	{
		SetMappingContext(EmoteMenuMappingContext);
	}
	else
	{
		SetMappingContext(DefaultMappingContext);
	}
}

// Waving emote functions
void ACoopAdventureCharacter::OnRep_IsWaving()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("OnRep Function Called"));
}

void ACoopAdventureCharacter::ServerSetIsWaving_Implementation(bool NewIsWaving)
{
	bIsWaving = NewIsWaving;
}

// Tut dancing emote functions
void ACoopAdventureCharacter::OnRep_IsTutDancing()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("OnRep Function Called"));
}



void ACoopAdventureCharacter::ServerSetIsTutDancing_Implementation(bool NewIsTutDancing)
{
	bIsTutDancing = NewIsTutDancing;
}

void ACoopAdventureCharacter::OnRep_Celebrating()
{

}



void ACoopAdventureCharacter::ServerSetIsCelebrating_Implementation(bool NewIsCelebrating)
{
	bIsCelebrating = NewIsCelebrating;
}

void ACoopAdventureCharacter::OnRep_DoingPushup()
{

}


void ACoopAdventureCharacter::ServerSetIsDoingPushup_Implementation(bool NewIsDoingPushup)
{
	bIsDoingPushup = NewIsDoingPushup;
}

void ACoopAdventureCharacter::OnRep_DoingJumpingJack()
{

}


void ACoopAdventureCharacter::ServerSetIsDoingJumpingJack_Implementation(bool NewIsDoingJumpingJack)
{
	bIsDoingJumpingJack = NewIsDoingJumpingJack;
}

void ACoopAdventureCharacter::OnRep_DoingBackflip()
{

}


void ACoopAdventureCharacter::ServerSetIsDoingBackflip_Implementation(bool NewIsDoingBackflip)
{
	bIsDoingBackflip = NewIsDoingBackflip;
}


