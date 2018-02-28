#pragma once

#include "MultiInteractionPluginPrivatePCH.h"
#include "InteractiveAction.generated.h"


UENUM(BlueprintType)
enum class EInteractionVisibility : uint8
{
	ENABLED		UMETA(DisplayName = "Enabled"),
	DISABLED	UMETA(DisplayName = "Disabled"),
	HIDDEN		UMETA(DisplayName = "Hidden")
};

USTRUCT(BlueprintType)
struct FInterativeActionHandle
{
	/* Makes sure the interaction component can get the id of the handle for retrieving the action */
	friend class UMultiInteractionComponent;

	GENERATED_BODY()

private:

	/** Identifier for this handle, for now is simply based on the index in the array containing the action */
	UPROPERTY()
	int32 ID;


public:

	FInterativeActionHandle()
	{
		this->ID = -1;
	}

	FInterativeActionHandle(int64 id)
	{
		this->ID = id;
	}

	bool IsValid()
	{
		return ID != -1;
	}

	bool operator== (const FInterativeActionHandle& Other)
	{
		return ID == Other.ID;
	}

	friend uint32 GetTypeHash(const FInterativeActionHandle& Other)
	{
		return GetTypeHash(Other.ID);
	}

	friend bool operator==(const FInterativeActionHandle& first, const FInterativeActionHandle& second)
	{
		return (first.ID == second.ID);
	}

protected:
	FORCEINLINE int32 GetId() const { return ID; }
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FActionDelegate, FInterativeActionHandle, Handle, AActor*, User);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FActionNameDelegate, FInterativeActionHandle, Handle, AActor*, User, FText&, output);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FActionVisibilityDelegate, FInterativeActionHandle, Handle, AActor*, User, EInteractionVisibility&, output);

/**
 * 
 */
UCLASS(BlueprintType)
class MULTIINTERACTIONPLUGIN_API UInteractiveAction : public UObject
{
	GENERATED_BODY()

	friend class UMultiInteractionComponent;

public:

	UInteractiveAction()
	{
	}

	void Init(FInterativeActionHandle& SetHandle, FActionDelegate Action, FText Name, FActionVisibilityDelegate Visibility)
	{
		ActionBinding = Action;
		CurrentName = Name;
		VisibilityBinding = Visibility;
		Handle = SetHandle;
	}

	void Init(FInterativeActionHandle& SetHandle, FActionDelegate Action, FActionNameDelegate Name, FActionVisibilityDelegate Visibility)
	{
		ActionBinding = Action;
		NameBinding = Name;
		VisibilityBinding = Visibility;
		Handle = SetHandle;
	}

	void Init(FInterativeActionHandle& SetHandle, FActionDelegate Action, FText Name, EInteractionVisibility Visibility)
	{
		ActionBinding = Action;
		CurrentName = Name;
		CurrentVisibility = Visibility;
		Handle = SetHandle;
	}

	void Init(FInterativeActionHandle& SetHandle, FActionDelegate Action, FActionNameDelegate Name, EInteractionVisibility Visibility)
	{
		ActionBinding = Action;
		NameBinding = Name;
		CurrentVisibility = Visibility;
		Handle = SetHandle;
	}

	UFUNCTION(BlueprintCallable)
	void Execute(AActor* User);

	UFUNCTION(BlueprintCallable)
	FText GetName(AActor* User);

	UFUNCTION(BlueprintCallable)
	EInteractionVisibility GetVisibility(AActor* User);


private:

	/** Current name of the action */
	FText CurrentName;

	/** Current visibility of the aciton */
	EInteractionVisibility CurrentVisibility;

	/** Delegate used to get the current name */
	FActionNameDelegate NameBinding;

	/** Delegate used for visibility */
	FActionVisibilityDelegate VisibilityBinding;

	/** Delegate used when the action is executed */
	FActionDelegate ActionBinding;

	/** Handle used by this action */
	FInterativeActionHandle Handle;
	
};