// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RegistrationSubsystem.generated.h"

class UContentRegister;
/**
 * 
 */
UCLASS()
class CO_CLIENT_API URegistrationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UPROPERTY(EditAnywhere, Category = "ContentRegister")
	TArray<TObjectPtr<UContentRegister>> ContentRegisters;
};
