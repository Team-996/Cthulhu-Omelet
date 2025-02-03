// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataComponent.h"

void UItemDataComponent::Init(UItemStack* owner)
{
	OwningStack = owner;
}

void UItemDataComponent::ParseMetaData(const TMap<FString, FString>& MetaData)
{
}
