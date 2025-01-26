﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Definition.generated.h"

/**
 * 
 */
UCLASS()
class CO_CLIENT_API UDefinition : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString id;
};
