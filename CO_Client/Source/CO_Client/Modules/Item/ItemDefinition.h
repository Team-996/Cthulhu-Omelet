// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO_Client/Core/Register/Definition.h"
#include "UObject/Object.h"
#include "ItemDefinition.generated.h"

class UItemDataComponent;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class CO_CLIENT_API UItemDefinition : public UDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TMap<FString, TObjectPtr<UTexture2D>> itemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString itemName = "Default Item";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int64 maxStackSize = 999;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TArray<FString> itemDescriptions = {"This is the default item", "You should not have this item in your container"};
	/** Parse MetaData and convert it to DataComponent type */
	virtual void ParseMetaData(const TMap<FString, FString>& MetaData) override;
	/// Get the ItemMetaData TMap
	UFUNCTION(BlueprintCallable, Category = "Meta")
	TMap<FString, FString> GetItemMetaData() const;

	/** Stores the Parsed DataComponent type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<TSubclassOf<UItemDataComponent>> DefaultDataComponents;

private:
	TMap<FString, FString> itemMetaData;
};
