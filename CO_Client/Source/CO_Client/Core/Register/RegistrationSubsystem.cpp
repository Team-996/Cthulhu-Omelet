// Fill out your copyright notice in the Description page of Project Settings.


#include "RegistrationSubsystem.h"

#include "Definition.h"
#include "CO_Client/Modules/Item/ItemRegister.h"

void URegistrationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// reserve
	RegisterMap.Reserve(5);
}

UItemRegister* URegistrationSubsystem::createItems(FString _namespace)
{
	UItemRegister* ItemRegister = NewObject<UItemRegister>(this);
	ItemRegister->NameSpace     = _namespace;

	if (RegisterMap.Find(_namespace))
	{
		RegisterMap.Find(_namespace)->elements.Add(ItemRegister);
		UE_LOG(LogTemp, Display, TEXT("Created Item Register %s"), *_namespace);
	}
	else
	{
		FRegisters registers;
		registers.elements.Add(ItemRegister);
		RegisterMap.Add(_namespace, registers);
		UE_LOG(LogTemp, Display, TEXT("Created Item Register %s"), *_namespace);
	}
	return ItemRegister;
}

UDefinition* URegistrationSubsystem::GetValue(FString _namespace, FString _id)
{
	if (RegisterMap.Find(_namespace)) // Find name space
	{
		FRegisters registers = *RegisterMap.Find(_namespace);
		/// TODO: we might need to merege registerd elements into a big array and
		/// sort by alphabet order, it will decrease the complexity
		for (UContentRegister* _register : registers.elements) // Find all register under the same namespace
		{
			TArray<TObjectPtr<UDefinition>> definitions;
			_register->RegisterContext.GenerateValueArray(definitions); // get each register's registered definitions
			for (TObjectPtr definition : definitions)
			{
				if (definition->id == _id)
				{
					return definition;
				}
			}
		}
		return nullptr;
	}
	else
	{
		return nullptr;
	}
}
