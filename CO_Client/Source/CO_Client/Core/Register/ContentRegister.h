// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ContentRegister.generated.h"

class UDefinition;
/**
 * 
 */
UCLASS(Blueprintable)
class CO_CLIENT_API UContentRegister : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category="Register")
	TMap<FString, TObjectPtr<UDefinition>> RegisterContext;


public:
	UFUNCTION(BlueprintCallable, Category = "Register")
	bool RegisterFromID_Def(FString id, TSubclassOf<UDefinition> definition);
	UFUNCTION(BlueprintCallable, Category = "Register")
	bool RegisterFromDef(TSubclassOf<UDefinition> definition);
};
