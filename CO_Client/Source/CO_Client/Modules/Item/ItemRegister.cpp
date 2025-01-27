// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemRegister.h"
#include "ItemDefinition.h"
#include "ItemRowData.h"

bool UItemRegister::RegisterFromDataTable(UDataTable* DataTable)
{
	for (auto& Row : DataTable->GetRowMap())
	{
		FItemRegisterDataRow*       Item       = (FItemRegisterDataRow*)(Row.Value);
		TObjectPtr<UItemDefinition> definition = BuildItemDefinition(*Item);
		if (definition != nullptr)
		{
			RegisterContext.Add(Item->ItemID, definition);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("RegisterFromDataTable: Failed to register item definition instance"));
			return false;
		}
	}

	return true;
}

bool UItemRegister::RegisterFromDef(TSubclassOf<UDefinition> definition)
{
	TObjectPtr<UItemDefinition> ItemDefinition = NewObject<UItemDefinition>(definition);
	if (ItemDefinition == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("RegisterFromDef(): Failed to register item definition instance"));
		return false;
	}
	else
	{
		if (RegisterContext.Find(ItemDefinition->id))
		{
			UE_LOG(LogTemp, Warning, TEXT("RegisterFromDef(): You try to register the definition with same id"));
		}
		RegisterContext.Add(ItemDefinition->id, ItemDefinition);
		return true;
	}
}

UItemDefinition* UItemRegister::BuildItemDefinition(FItemRegisterDataRow& rowData)
{
	TSubclassOf<UItemDefinition> templateClass = rowData.DefinitionClassTemplate;
	TObjectPtr<UItemDefinition>  definition    = NewObject<UItemDefinition>(templateClass);

	if (definition == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemRegister::BuildItemDefinition -> Failed to build item definition instance"));
		return templateClass.GetDefaultObject();
	}

	/// Read Table row metadata and parse into item definition
	definition->ParseMetaData(rowData.MetaData);
	/// End of parse
	return definition;
}
