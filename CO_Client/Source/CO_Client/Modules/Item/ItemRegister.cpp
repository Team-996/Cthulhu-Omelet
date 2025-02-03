// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemRegister.h"
#include "ItemDefinition.h"
#include "ItemRowData.h"

bool UItemRegister::RegisterFromDataTable(UDataTable* DataTable)
{
	if (!DataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("RegisterFromDataTable: DataTable is null!"));
		return false;
	}

	bool bSuccess = true;

	for (auto& Row : DataTable->GetRowMap())
	{
		FItemRegisterDataRow*       Item       = (FItemRegisterDataRow*)(Row.Value);
		TObjectPtr<UItemDefinition> definition = BuildItemDefinition(*Item);

		if (definition != nullptr)
		{
			if (RegisterContext.Contains(Item->ItemID))
			{
				UE_LOG(LogTemp, Warning, TEXT("RegisterFromDataTable: Item ID %s is already registered!"), *Item->ItemID);
			}
			else
			{
				RegisterContext.Add(Item->ItemID, definition);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("RegisterFromDataTable: Failed to register item definition instance for ItemID: %s"), *Item->ItemID);
			bSuccess = false;
		}
	}

	return bSuccess;
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
	TObjectPtr<UItemDefinition>  definition    = NewObject<UItemDefinition>(this);

	UE_LOG(LogTemp, Display, TEXT("UItemRegister::BuildItemDefinition -> Successful create Definition class: %s"), *rowData.ItemID)

	if (definition == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemRegister::BuildItemDefinition -> Failed to build item definition instance"));
		return templateClass.GetDefaultObject();
	}
	/// Data Injection
	/// TODO: consider move those part into builder (Builder)
	definition->id               = rowData.ItemID;
	definition->itemName         = rowData.Name;
	definition->maxStackSize     = rowData.MaxStackSize;
	definition->itemDescriptions = rowData.Descriptions;
	definition->itemIcon         = rowData.ItemIcon;

	UE_LOG(LogTemp, Display, TEXT("UItemRegister::BuildItemDefinition -> Parsing item MetaData: %s"), *rowData.ItemID)

	/// Read Table row metadata and parse into item definition
	definition->ParseMetaData(rowData.MetaData);
	/// End of parse

	UE_LOG(LogTemp, Display, TEXT("UItemRegister::BuildItemDefinition -> Successful create Definition Instance: %s"), *rowData.ItemID)

	return definition;
}
