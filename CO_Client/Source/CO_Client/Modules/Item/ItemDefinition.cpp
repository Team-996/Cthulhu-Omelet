// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDefinition.h"

void UItemDefinition::ParseMetaData(const TMap<FString, FString>& MetaData)
{
	Super::ParseMetaData(MetaData);
	DefaultDataComponents.Empty();
	// Read meta data and find the key, base on the key to set Default data component class
	for (const auto& Pair : MetaData)
	{
		if (Pair.Key == "Durability")
		{
			//DefaultDataComponents.Add(UDurabilityComponent::StaticClass());
		}
		else if (Pair.Key == "Enchantment")
		{
			//DefaultDataComponents.Add(UEnchantmentComponent::StaticClass());
		}
	}
}

TMap<FString, FString> UItemDefinition::GetItemMetaData() const
{
	return itemMetaData;
}
