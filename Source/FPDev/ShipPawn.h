// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MortalPawn.h"
#include "ShipPawn.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FPDEV_API AShipPawn : public AMortalPawn
{
	GENERATED_BODY()

	//List of rounds queued to fire.
	TArray<bool> FireQueue;

	//Whether the character is holding the trigger down or not.
	bool TriggerHeld;

	//Spwan bullets for the round.
	void FireWeapon(float DeltaTime);
	
public:

	AShipPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditDefaultsOnly, Category = "Controls")
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditDefaultsOnly, Category = "Controls")
		float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, Category = "Controls")
		float BaseImpulseRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
		float EngineImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		float MaxEngineImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		float MinEngineImpulse;

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void PitchAtRate(float Rate);

	void ModifyEngineImpluse(float Rate);

	//Fire Event Triggered by input.
	void OnFire();

	//Change TriggerHeld state
	void ToggleTrigger() {
		TriggerHeld = !TriggerHeld;
	}


	/** Projectile class to spawn */
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Projectile")
		TSubclassOf<class AFPDevProjectile> ProjectileClass;

	//The characters WeaponMechanic, used to specify "how the character uses" the current weapon.
	//See WeaponMechanics for "Weapon Functionality".
	//Get the character's WeaponFunction member and use "Weapon Modifier" functions to modify the active WeaponMechanic's "Weapon Functionality" properties. 
	UPROPERTY(BlueprintReadOnly, Category = "Weapon Mechanic")
	class UWeaponMechanic* WeaponFunction;

	//Use this function change the character's WeaponFunction to a new WeaponMechanic of your choice.
	//This method constructs a WeaponMechanic of your choice and makes it the acitive WeaponFunction.
	//@Params: NewMechanicType - the WeaponMechanic subclass to change to.
	//DO NOT: Pass this function a WeaponMechanic object.  
	UFUNCTION(BlueprintCallable, Category = "Weapon Mechanic")
		void ChangeWeaponMechanicClass(UClass* NewMechanicType);

	//Use this function change the character's WeaponFunction to a WeaponMechanic object.
	//This method sets the acitive WeaponFunction to a WeaponMechanic object.
	//@Params: NewWeaponFunction - the WeaponMechanic object to change to.
	//DO NOT: Pass this function a WeaponMechanic type.  
	UFUNCTION(BlueprintCallable, Category = "Weapon Mechanic")
		void SetWeaponFunction(UWeaponMechanic* NewWeaponFunction);

	//Time since the last trigger pulled.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon Mechanic")
		float TimeSinceFire;

	//Time since the last round fired.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon Mechanic")
		float TimeSinceBulletSpawn;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class USceneComponent* MuzzleLocation;

	//Fire Event Triggered by input.
	UFUNCTION(BlueprintCallable, Category = "Weapon Operation")
		bool ActivateWeapon();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//initialize the pawn's mesh and other viewable components
	virtual void SetupPawnView() override;

	//Return the mesh component(s) used for this pawn.
	virtual UStaticMeshComponent* GetPawnUsedView() override;

};