// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO_Client/Core/Register/Definition.h"
#include "UObject/Object.h"
#include "ItemDefinition.generated.h"

/**
 * 
 */
UCLASS()
class CO_CLIENT_API UItemDefinition : public UDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TObjectPtr<UTexture2D> itemIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString itemName = "Default Item";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int64 maxStackSize = 999;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TArray<FString> itemDescriptions = {"This is the default item", "You should not have this item in your container"};
	virtual void    ParseMetaData(const TMap<FString, FString>& MetaData) override;

private:
	TMap<FString, FString> itemMetaData;
};
