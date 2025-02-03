// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStackBuilder.h"

#include "CO_Client/Core/Register/RegistrationSubsystem.h"
#include "CO_Client/Modules/Item/ItemDefinition.h"
#include "CO_Client/Modules/Item/ItemStack.h"

UItemStackBuilder::UItemStackBuilder()
{
}

UItemStackBuilder* UItemStackBuilder::WithDefinition(UItemDefinition* Definition)
{
	_definition = Definition;
	return this;
}

UItemStackBuilder* UItemStackBuilder::WithNamespaceAndPath(FString NameSpace, FString Path)
{
	UItemDefinition* definition = Cast<UItemDefinition>(URegistrationSubsystem::GetRegistrationSubsystem()->GetValue(NameSpace, Path));
	_definition                 = definition;
	return this;
}

UItemStackBuilder* UItemStackBuilder::WithCount(int32 Count)
{
	_count = Count;
	return this;
}

UItemStackBuilder* UItemStackBuilder::WithDataComponent(UItemDataComponent* Component)
{
	_dataComponents.Add(Component);
	return this;
}

UItemStack* UItemStackBuilder::Build()
{
	if (!_definition)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemStackBuilder::Build() -> No Definition set!"));
	}
	// Need Outer perhaps
	UItemStack* itemStack = NewObject<UItemStack>();
	itemStack->Init(_definition, _count);

	for (TObjectPtr<UItemDataComponent> ItemDataComponent : _dataComponents)
	{
		itemStack->AddDataComponent(ItemDataComponent);
	}

	return itemStack;
}
