#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ClientEventDispatcher.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClientClose);

UCLASS(BlueprintType, Blueprintable)
class CO_CLIENT_API UClientEventDispatcher : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintCallable, BlueprintReadWrite, BlueprintAssignable, Category="Event")
	FOnClientClose OnClientClose;
};
