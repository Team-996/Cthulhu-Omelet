// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaDataParser.h"
#include "UObject/Object.h"
#include "Definition.generated.h"

/**
 * 
 */
UCLASS()
class CO_CLIENT_API UDefinition : public UObject, public IMetaDataParser
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString id;
	UFUNCTION(BlueprintCallable, Category = "Meta")
	virtual void ParseMetaData(const TMap<FString, FString>& MetaData) override
	{
	}
};
