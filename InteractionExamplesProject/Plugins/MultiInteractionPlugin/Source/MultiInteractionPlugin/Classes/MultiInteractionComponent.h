#pragma once

#include "MultiInteractionPluginPrivatePCH.h"
#include "Components/ActorComponent.h"
#include "Runtime/CoreUObject/Public/UObject/TextProperty.h"
#include "InteractiveAction.h"
#include "MultiInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIINTERACTIONPLUGIN_API UMultiInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMultiInteractionComponent();

public:	

	/** Adds an action that can be done with the object */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FInterativeActionHandle AddAction(FActionDelegate ActionBinding, FActionNameDelegate  NameBinding, FActionVisibilityDelegate VisibilityBinding);

	/** Adds an action with a fixed name */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FInterativeActionHandle AddAction_FixedName(FActionDelegate ActionBinding, const FText& Name, FActionVisibilityDelegate VisibilityBinding);

	/** Adds an action with a fixed visibility */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FInterativeActionHandle AddAction_FixedVisibility(FActionDelegate ActionBinding, FActionNameDelegate  NameBinding, EInteractionVisibility Visibility);

	/** Adds an action with a fixed name and fixed visibility */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FInterativeActionHandle AddAction_Fixed(FActionDelegate ActionBinding, const FText& Name, EInteractionVisibility Visibility);

	/** Sets the visibility for a given action */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetActionVisibility(FInterativeActionHandle Handle, EInteractionVisibility Visibility);

	/** Sets the display name for a given action */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetActionName(FInterativeActionHandle Handle, const FText& Name);

	/** Sets the name used for interacting with the object */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractionName(FText Name);

	/** Gets the name used for interaction */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Interaction")
	FText GetInteractionName();

	/** Returns all the interactions possible with the object */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UInteractiveAction*> GetInteractions();

	/** Returns all interaction with a certain visibility */
	UFUNCTION(BlueprintCallable)
	TArray<UInteractiveAction*> GetInteractionsWithVisibility(EInteractionVisibility Visibility, AActor* User);

	/** Returns all interactions that are visible */
	UFUNCTION(BlueprintCallable)
	TArray<UInteractiveAction*> GetVisibleInteractions(AActor* User);

protected:

	/** Name of the interacting object separate from actaul object name */
	UPROPERTY(EditAnywhere)
	FText InteractionName;

	/** Creates a new handle, for now is simply based on the new array index */
	FORCEINLINE FInterativeActionHandle CreateHandle() { return FInterativeActionHandle(Actions.Num()); }

private:

	/** Contains all actions for this component */
	UPROPERTY()
	TArray<UInteractiveAction*> Actions;
};
