#pragma once

#include "CoreMinimal.h"            // Includes most of the commonly used core Unreal Engine functionality.
#include "Engine/Engine.h"          // General engine-level systems.
#include "GameFramework/Actor.h"    // Base class for most gameplay objects.
#include "GameFramework/Character.h" // Base class for characters with movement capabilities.
#include "GameFramework/PlayerController.h" // For controlling players in a game.
#include "GameFramework/GameModeBase.h" // Base class for Game Modes.
#include "GameFramework/GameStateBase.h" // Base class for Game States.
#include "Net/UnrealNetwork.h"          // Networking utilities.
#include "Engine/NetDriver.h"           // For network driver controls.
#include "Engine/World.h"               // Access to the game world.
#include "Components/SceneComponent.h" // Base component for attaching objects.
#include "Components/ActorComponent.h" // Base class for actor components.
#include "Components/PrimitiveComponent.h" // Base class for renderable components.
#include "Components/BoxComponent.h"   // Box-shaped collision.
#include "Components/SphereComponent.h" // Sphere-shaped collision.
#include "Components/CapsuleComponent.h" // Capsule-shaped collision.
#include "TimerManager.h"              // Managing timed events.
#include "Kismet/KismetSystemLibrary.h" // General-purpose blueprint functions.
#include "Kismet/GameplayStatics.h"    // Utility functions for gameplay.

// From BP_Robot2
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"