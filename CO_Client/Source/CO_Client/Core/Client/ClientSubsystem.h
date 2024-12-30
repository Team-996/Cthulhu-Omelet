#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ClientSubsystem.generated.h"

class UClientEventDispatcher;
/**
 * 
 */
UCLASS(Blueprintable)
class CO_CLIENT_API UClientSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UClientEventDispatcher> EventDispatcher;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
