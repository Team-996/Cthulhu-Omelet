// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStack.h"

#include "ItemDefinition.h"
#include "Builder/ItemStackBuilder.h"

UItemStack::UItemStack()
{
}

void UItemStack::Init(TObjectPtr<UItemDefinition> inDefinition, int32 inCount)
{
	DataComponents.Reserve(5);
	Definition = inDefinition;
	Amount     = inCount;

	/// Traverse TSubclassOf<UItemDataComponent> in Definition and dynamically create instances
	/// After creating instance, the component need read Item meta data to set its own value
	for (TSubclassOf<UItemDataComponent> ComponentClass : Definition->DefaultDataComponents)
	{
		if (ComponentClass)
		{
			UItemDataComponent* Component = NewObject<UItemDataComponent>(this, ComponentClass);
			Component->ParseMetaData(Definition->GetItemMetaData()); // Inject metadata into component
			DataComponents.Add(Component);
			Component->Init(this); // Set the owner item stack
		}
	}
}

int32 UItemStack::GetCount() const
{
	return Amount;
}

void UItemStack::SetCount(int32 inCount)
{
	Amount = inCount;
	if (Amount > Definition->maxStackSize)
	{
		Amount = Definition->maxStackSize;
	}
}

void UItemStack::AddDataComponent(UItemDataComponent* component)
{
	for (TObjectPtr<UItemDataComponent> ItemDataComponent : DataComponents)
	{
		if (!ItemDataComponent.IsA(component->GetClass()))
		{
			DataComponents.Add(component);
			UE_LOG(LogTemp, Display, TEXT("UItemStack::AddDataComponent -> Successful add component %s"), *component->GetClass()->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UItemStack::AddDataComponent -> Failed to add component %s (Class duplication)"), *component->GetClass()->GetName())
		}
	}
}

FComponentData UItemStack::GetDataComponent(TSubclassOf<UItemDataComponent> type) const
{
	FComponentData componentData;
	for (TObjectPtr<UItemDataComponent> ItemDataComponent : DataComponents)
	{
		if (ItemDataComponent.IsA(type.Get()))
		{
			componentData.ItemDataComponent      = ItemDataComponent;
			componentData.ItemDataComponentClass = type;
		}
	}
	return componentData;
}

TArray<UItemDataComponent*> UItemStack::GetDataComponents() const
{
	return DataComponents;
}
