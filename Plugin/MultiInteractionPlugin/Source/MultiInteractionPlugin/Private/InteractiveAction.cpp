#include "MultiInteractionPluginPrivatePCH.h"
#include "InteractiveAction.h"

EInteractionVisibility UInteractiveAction::GetVisibility(AActor* User)
{
	// if there is no delegate bound then we are likely using a fixed visibility
	if (!VisibilityBinding.IsBound())
	{
		return CurrentVisibility;
	}

	EInteractionVisibility Visibility;
	VisibilityBinding.Execute(Handle, User, Visibility);
	return Visibility;
}

FText UInteractiveAction::GetName(AActor* User)
{
	// if there is no delegate bound then we are likely using a fixed name
	if (!NameBinding.IsBound())
	{
		return CurrentName;
	}

	FText BoundedName;
	NameBinding.Execute(Handle, User, BoundedName);
	return BoundedName;
}

void UInteractiveAction::Execute(AActor* User)
{
	if (ActionBinding.IsBound())
	{
		ActionBinding.Execute(Handle, User);
	}
}



