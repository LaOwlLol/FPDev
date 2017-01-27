// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProjectileInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class FPDEV_API IProjectileInterface
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	//Allows desginer to construct a UProjectileMovementComponent to govern this projectile's movement of a a custom projectile type.
	//Return Value:: UProjectileMovementComponent
	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile Characteristics") UProjectileMovementComponent* InitProjectileMovementComponent();
	
};
