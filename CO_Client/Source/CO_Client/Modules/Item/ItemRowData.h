// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemRowData.generated.h"

class UItemDefinition;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemRegisterDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TMap<FString, TObjectPtr<UTexture2D>> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 MaxStackSize = 999;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<FString> Descriptions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TMap<FString, FString> MetaData;
	/// Specify the Definition Class template to use for instantiate ItemDefinition
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Builder")
	TSubclassOf<UItemDefinition> DefinitionClassTemplate;
};
