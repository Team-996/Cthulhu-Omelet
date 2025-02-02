// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RegistrationSubsystem.generated.h"

class UDefinition;
class UItemRegister;
class UContentRegister;

/// The Compact POD that store array of register
/// @author Caizii
USTRUCT(BlueprintType)
struct FRegisters
{
	GENERATED_BODY()

public:
	/// TODO: we probably need merge the register element together rather than
	/// make several register
	TArray<UContentRegister*> elements;
};

/**
 * 
 */
UCLASS(Blueprintable)
class CO_CLIENT_API URegistrationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/// it looks very heavy engineered, but indeed, it is heavy engineered
	UPROPERTY(EditAnywhere, Category = "ContentRegister")
	TMap<FString, FRegisters> RegisterMap;

	/// Function
public:
	/// Create specific namespace item register
	/// @param _namespace Create Item register with specific name space
	/// @return the register with specific namespace
	UFUNCTION(BlueprintCallable, Category = "Items")
	UItemRegister* createItems(FString _namespace = FString("Default"));
	/// Query specific namespace and id Definition return generic UDefinition
	/// @param _namespace namespace you want to narrow down
	/// @param _id the register id you want to search base on its register namespace
	/// @return the Definition found
	UFUNCTION(BlueprintCallable, Category = "Items")
	UDefinition* GetValue(FString _namespace = FString("Default"), FString _id = FString("Default"));

	// createPets()

	// createBlocks()
private:
};
