// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ContentRegister.generated.h"

class UDefinition;
/**
 * 
 */
UCLASS(Blueprintable, NotBlueprintType)
class CO_CLIENT_API UContentRegister : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UClass> ContentRegisterClass;
	/// The Register Context contain all definition instance that register form Class Definition
	/// , DataTable, or individual Class, The RegisterContext need merge together to get complete
	/// TMap
	UPROPERTY(VisibleAnywhere, Category="Register")
	TMap<FString, TObjectPtr<UDefinition>> RegisterContext;

public:
	virtual bool RegisterFromDataTable(UDataTable* DataTable);
	virtual bool RegisterFromDef(TSubclassOf<UDefinition> definition);
};
