// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO_Client/Core/Register/MetaDataParser.h"
#include "UObject/Object.h"
#include "ItemDataComponent.generated.h"

class UItemDataComponent;

USTRUCT(BlueprintType)
struct FComponentData
{
	GENERATED_BODY()

	TObjectPtr<UItemDataComponent>  ItemDataComponent;
	TSubclassOf<UItemDataComponent> ItemDataComponentClass;
};

class UItemStack;
/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class CO_CLIENT_API UItemDataComponent : public UObject, public IMetaDataParser
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Item Data")
	virtual void Init(UItemStack* owner);
	/// Parse Meta Data and set its own field
	/// @param MetaData The Metadata component need for constructing its own value
	virtual void ParseMetaData(const TMap<FString, FString>& MetaData) override;

protected:
	UPROPERTY()
	TObjectPtr<UItemStack> OwningStack;
};
