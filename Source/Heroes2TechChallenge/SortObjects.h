// Code developed by Marco Antônio, contact: https://www.linkedin.com/in/marco-a-junior/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SortObjects.generated.h"

class AStaticMeshActor;
class USortObjectsWidget;

UCLASS()
class HEROES2TECHCHALLENGE_API ASortObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASortObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// SETTINGS

	// Static Meshes to manipulate the World Transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		TArray<AStaticMeshActor*> ManipulateMeshes;

	// Value that defines how long the sorted StaticMeshes should go
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float SortRadius;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		//float Visi

	// The SortObjects Widget Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		TSubclassOf<USortObjectsWidget> SortObjectsWidgetClass;

// LOGIC

	// The ManipulateMeshes default Transforms
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Logic")
		TMap<AStaticMeshActor*, FTransform> DefaultManipulateMeshesTransforms;

	// The ManipulateMeshes randomized Transforms
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Logic")
		TMap<AStaticMeshActor*, FTransform> RandomManipulateMeshesTransforms;

	// The SortObjects widget reference
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Logic")
		USortObjectsWidget* SortObjectsWidget;

	// The timer to visual manipulate the StaticMeshes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Logic")
		FTimerHandle ManipulateMeshesTimer;

	// Boolean value that defines if the visual manipulate is to default or not.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Logic")
		bool bIsToDefault;

// METHODS

	// Call to sort all the StaticMeshes in the ManipulateMeshes
	UFUNCTION(BlueprintCallable)
		void SetMeshesSorted();

	// Call to set the default Transform to all StaticMeshes in the ManipulateMeshes
	UFUNCTION(BlueprintCallable)
		void SetMeshesDefaults();

	// Called every delay time of ManipulateMeshesTimer
	UFUNCTION()
		void VisualManipulate();
};
