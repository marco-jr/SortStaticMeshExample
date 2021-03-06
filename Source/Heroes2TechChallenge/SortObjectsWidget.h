// Code developed by Marco Antônio, contact: https://www.linkedin.com/in/marco-a-junior/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SortObjectsWidget.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSortDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDefaultDelegate);
/**
 * 
 */
UCLASS()
class HEROES2TECHCHALLENGE_API USortObjectsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
// CONSTRUCTOR

	virtual void NativeConstruct() override;

// COMPONENTS

	// The button will sort the meshes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
		UButton* SortButton;

	// The button will set meshes to default transform
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
		UButton* DefaultButton;

// LOGIC

	// Called when the SortMeshes was called
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintAssignable, Category = "Logic")
		FSortDelegate OnSort;

	// Called when the DefaultMeshes was called
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintAssignable, Category = "Logic")
		FDefaultDelegate OnDefault;

// METHODS

	// Called when the sort button is clicked
	UFUNCTION()
		void SortMeshes();

	// Called when the default button is clicked
	UFUNCTION()
		void DefaultMeshes();
};
