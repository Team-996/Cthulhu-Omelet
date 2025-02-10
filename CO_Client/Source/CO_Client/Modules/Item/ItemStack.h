// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ItemDataComponent.h"
#include "UObject/Object.h"
#include "ItemStack.generated.h"
class UItemDataComponent;
class UItemDefinition;
/**
 * 
 */
UCLASS()
class CO_CLIENT_API UItemStack : public UObject
{
	GENERATED_BODY()

public:
	UItemStack();

	void Init(TObjectPtr<UItemDefinition> inDefinition, int32 inCount = 1);

	UFUNCTION(BlueprintCallable, Category = "ItemStack")
	int32 GetCount() const;

	UFUNCTION(BlueprintCallable, Category = "ItemStack")
	void SetCount(int32 inCount);

	UFUNCTION(BlueprintCallable, Category = "ItemStack")
	void AddDataComponent(UItemDataComponent* component);

	UFUNCTION(BlueprintCallable, Category = "ItemStack")
	FComponentData GetDataComponent(TSubclassOf<UItemDataComponent> type) const;
	UFUNCTION(BlueprintCallable, Category = "ItemStack")
	TArray<UItemDataComponent*> GetDataComponents() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	int32 Amount = 1;

	UPROPERTY()
	TArray<TObjectPtr<UItemDataComponent>> DataComponents;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Definition")
	TObjectPtr<UItemDefinition> Definition;
};
