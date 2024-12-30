#include "ClientSubsystem.h"

#include "CO_Client/Core/Event/Client/ClientEventDispatcher.h"

void UClientSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	EventDispatcher = NewObject<UClientEventDispatcher>(this);
}
