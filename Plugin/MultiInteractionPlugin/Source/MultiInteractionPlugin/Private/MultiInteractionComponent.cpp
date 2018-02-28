#include "MultiInteractionPluginPrivatePCH.h"
#include "MultiInteractionComponent.h"

UMultiInteractionComponent::UMultiInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMultiInteractionComponent::SetActionVisibility(FInterativeActionHandle Handle, EInteractionVisibility Visibility)
{
	if (Handle.GetId() < 0 || Handle.GetId() >= Actions.Num())
	{
		return;
	}

	UInteractiveAction* Action = Actions[Handle.GetId()];
	Action->CurrentVisibility = Visibility;
}

void UMultiInteractionComponent::SetActionName(FInterativeActionHandle Handle, const FText& Name)
{
	if (Handle.GetId() < 0 || Handle.GetId() >= Actions.Num())
	{
		return;
	}

	UInteractiveAction* Action = Actions[Handle.GetId()];
	Action->CurrentName = Name;
}

FInterativeActionHandle UMultiInteractionComponent::AddAction(FActionDelegate ActionBinding, FActionNameDelegate  NameBinding, FActionVisibilityDelegate VisibilityBinding)
{
	FInterativeActionHandle Handle = CreateHandle();

	// create the interaction object and add it
	UInteractiveAction* Object = NewObject<UInteractiveAction>();
	Object->Init(Handle, ActionBinding, NameBinding, VisibilityBinding);
	Actions.Add(Object);

	return Handle;
}

FInterativeActionHandle UMultiInteractionComponent::AddAction_FixedName(FActionDelegate ActionBinding, const FText& Name, FActionVisibilityDelegate VisibilityBinding)
{
	FInterativeActionHandle Handle = CreateHandle();

	// create the interaction object and add it
	UInteractiveAction* Object = NewObject<UInteractiveAction>();
	Object->Init(Handle, ActionBinding, Name, VisibilityBinding);
	Actions.Add(Object);

	return Handle;
}

FInterativeActionHandle UMultiInteractionComponent::AddAction_FixedVisibility(FActionDelegate ActionBinding, FActionNameDelegate  NameBinding, EInteractionVisibility Visibility)
{
	FInterativeActionHandle Handle = CreateHandle();

	// create the interaction object and add it
	UInteractiveAction* Object = NewObject<UInteractiveAction>();
	Object->Init(Handle, ActionBinding, NameBinding, Visibility);
	Actions.Add(Object);

	return Handle;
}

FInterativeActionHandle UMultiInteractionComponent::AddAction_Fixed(FActionDelegate ActionBinding, const FText& Name, EInteractionVisibility Visibility)
{
	FInterativeActionHandle Handle = CreateHandle();

	// create the interaction object and add it
	UInteractiveAction* Object = NewObject<UInteractiveAction>();
	Object->Init(Handle, ActionBinding, Name, Visibility);
	Actions.Add(Object);

	return Handle;
}

TArray<UInteractiveAction*> UMultiInteractionComponent::GetInteractions()
{
	return Actions;
}

TArray<UInteractiveAction*> UMultiInteractionComponent::GetInteractionsWithVisibility(EInteractionVisibility Visibility, AActor* User)
{
	// go through all items and only add those that match the given visibility
	TArray<UInteractiveAction*> SelectedActions;
	for (UInteractiveAction* Action : Actions)
	{
		if (Action->GetVisibility(User) == Visibility)
		{
			SelectedActions.Add(Action);
		}
	}
	return SelectedActions;
}

TArray<UInteractiveAction*> UMultiInteractionComponent::GetVisibleInteractions(AActor* User)
{
	// go through all items and only add those that are not hidden
	TArray<UInteractiveAction*> SelectedActions;
	for (UInteractiveAction* Action : Actions)
	{
		if (Action->GetVisibility(User) != EInteractionVisibility::HIDDEN)
		{
			SelectedActions.Add(Action);
		}
	}
	return SelectedActions;
}



FText UMultiInteractionComponent::GetInteractionName()
{
	return InteractionName;
}

void UMultiInteractionComponent::SetInteractionName(FText Name)
{
	InteractionName = Name;
}


