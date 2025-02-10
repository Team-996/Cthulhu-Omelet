// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemStackBuilder.generated.h"

class UItemDataComponent;
class UItemStack;
class UItemDefinition;
/**
 * 
 */
UCLASS(BlueprintType)
class CO_CLIENT_API UItemStackBuilder : public UObject
{
	GENERATED_BODY()

public:
	UItemStackBuilder();

	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemStackBuilder* WithDefinition(UItemDefinition* Definition);
	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemStackBuilder* WithNamespaceAndPath(FString NameSpace = FString("Default"), FString Path = FString("Default"));
	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemStackBuilder* WithCount(int32 Count = 1);
	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemStackBuilder* WithDataComponent(UItemDataComponent* Component);
	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemStackBuilder* WithCommonProperties(FString NameSpace = FString("Default"), FString Path = FString("Default"), int32 Count = 1);
	/// Build the customize ItemStack with outer
	/// @param outer the outer of the ItemStack
	/// @return the ItemStack
	UFUNCTION(BlueprintCallable, Category = "Build")
	UItemStack* Build(UObject* outer);
	/// native static getter of ItemStack builder
	static UItemStackBuilder* Builder();

protected:
	TObjectPtr<UItemDefinition>            _definition = nullptr;
	int32                                  _count      = 1;
	TArray<TObjectPtr<UItemDataComponent>> _dataComponents;
};
