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
UCLASS()
class CO_CLIENT_API UItemStackBuilder : public UObject
{
	GENERATED_BODY()

public:
	UItemStackBuilder();

	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemStackBuilder * WithDefinition(UItemDefinition* Definition);
	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemStackBuilder * WithNamespaceAndPath(FString NameSpace = FString("Default"), FString Path = FString("Default"));
	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemStackBuilder * WithCount(int32 Count);
	UFUNCTION(BlueprintCallable, Category = "Item")
	UItemStackBuilder * WithDataComponent(UItemDataComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "Build")
	UItemStack * Build();

protected:
	TObjectPtr<UItemDefinition>            _definition = nullptr;
	int32                                  _count      = 1;
	TArray<TObjectPtr<UItemDataComponent>> _dataComponents;
};
