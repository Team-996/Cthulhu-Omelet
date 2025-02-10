// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO_Client/Core/Register/ContentRegister.h"
#include "UObject/Object.h"
#include "ItemRegister.generated.h"

struct FItemRegisterDataRow;
class UItemDefinition;
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

	/// Register items from correspond datatable, user need to set correct datatable
		/// or else it would fail to register items
		/// @param DataTable The datatable need to read its rows to register items
		/// @return whether or not successful register
	UFUNCTION(BlueprintCallable, Category = "Register")
	virtual bool RegisterFromDataTable(UDataTable* DataTable) override;
	UFUNCTION(BlueprintCallable, Category = "Register")
	virtual bool RegisterFromDef(TSubclassOf<UDefinition> definition) override;
	/// Build Item Definition from the row of ItemDatatable, it will return the default item Definition
	/// if It can not build
	/// @param rowData The row of Item register DataTable, represent a single item register data
	/// @return The ready ItemDefinition filled with Data
	UFUNCTION(BlueprintCallable, Category = "Register")
	UItemDefinition* BuildItemDefinition(FItemRegisterDataRow& rowData);
};
