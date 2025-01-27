// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO_Client/Core/Register/ContentRegister.h"
#include "UObject/Object.h"
#include "ItemRegister.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CO_CLIENT_API UItemRegister : public UContentRegister
{
	GENERATED_BODY()

public:
	/// Set the datatable for the register
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UDataTable> ItemRegisterDataTable;

public:
	/// Register items from correspond datatable, user need to set correct datatable
	/// or else it would fail to register items
	/// @param DataTable The datatable need to read its rows to register items
	/// @return whether or not successful register
	UFUNCTION(BlueprintCallable, Category = "Register")
	virtual bool RegisterFromDataTable(UDataTable* DataTable) override;
	UFUNCTION(BlueprintCallable, Category = "Register")
	virtual bool RegisterFromDef(TSubclassOf<UDefinition> definition) override;
};
