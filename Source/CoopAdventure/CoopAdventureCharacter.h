// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Animation/AnimMontage.h"
#include "CoopAdventureCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UUserWidget;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


UCLASS(config=Game)
class ACoopAdventureCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// INPUT //////////////////////////////////////////////////////////////////////////////////////////////
	
	// MAPPING CONTEXTS

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Emote Menu MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* PauseMenuMappingContext;

	/** Emote Menu MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* EmoteMenuMappingContext;

	// INPUT ACTIONS

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Pause Menu Input Action
	Opens and closes the pause menu*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseMenuAction;

	/** Emote Menu Input Action
	Opens and closes the emote menu*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EmoteMenuAction;


public:
	ACoopAdventureCharacter();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetIsWaving(bool NewIsWaving);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetIsTutDancing(bool NewIsTutDancing);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetIsCelebrating(bool NewIsCelebrating);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetIsDoingPushup(bool NewIsDoingPushup);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetIsDoingJumpingJack(bool NewIsDoingJumpingJack);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetIsDoingBackflip(bool NewIsDoingBackflip);




protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called to open and close the pause menu */
	void PauseMenu(const FInputActionValue& Value);

	/* Called to open and close the emote menu*/
	void EmoteMenu(const FInputActionValue& Value);
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UClass* WidgetClass;

	UPROPERTY(BlueprintReadWrite)
	bool bPauseMenuIsOpen;

	UPROPERTY(BlueprintReadWrite)
	bool bEmoteMenuIsOpen;

	// Waving emote
	UPROPERTY(ReplicatedUsing = OnRep_IsWaving, BlueprintReadWrite)
	bool bIsWaving;

	UFUNCTION()
	void OnRep_IsWaving();

	// Tut dance emote
	UPROPERTY(ReplicatedUsing = OnRep_IsTutDancing, BlueprintReadWrite)
	bool bIsTutDancing;

	UFUNCTION()
	void OnRep_IsTutDancing();

	// Celebrate (dancing) emote
	UPROPERTY(ReplicatedUsing = OnRep_Celebrating, BlueprintReadWrite)
	bool bIsCelebrating;

	UFUNCTION()
	void OnRep_Celebrating();

	// Pushup emote
	UPROPERTY(ReplicatedUsing = OnRep_DoingPushup, BlueprintReadWrite)
	bool bIsDoingPushup;

	UFUNCTION()
	void OnRep_DoingPushup();

	// Jumping jacks emote
	UPROPERTY(ReplicatedUsing = OnRep_DoingJumpingJack, BlueprintReadWrite)
	bool bIsDoingJumpingJack;

	UFUNCTION()
	void OnRep_DoingJumpingJack();

	// Backflip emote
	UPROPERTY(ReplicatedUsing = OnRep_DoingBackflip, BlueprintReadWrite)
	bool bIsDoingBackflip;

	UFUNCTION()
	void OnRep_DoingBackflip();


	

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Helper functions
	UFUNCTION(BlueprintCallable)
	void SetMappingContext(UInputMappingContext* MappingContext);



};

