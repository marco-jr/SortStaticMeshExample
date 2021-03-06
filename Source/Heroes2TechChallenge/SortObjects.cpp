// Code developed by Marco Antônio, contact: https://www.linkedin.com/in/marco-a-junior/


#include "SortObjects.h"
#include "SortObjectsWidget.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
ASortObjects::ASortObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SortRadius = 200.f;
}

// Called when the game starts or when spawned
void ASortObjects::BeginPlay()
{
	Super::BeginPlay();
	
	// Add the SortObjects widget to the screen
	if (SortObjectsWidgetClass)
	{
		SortObjectsWidget = CreateWidget<USortObjectsWidget>(GetWorld(), SortObjectsWidgetClass);
		SortObjectsWidget->AddToViewport(1);
		SortObjectsWidget->OnSort.AddDynamic(this, &ASortObjects::SetMeshesSorted);
		SortObjectsWidget->OnDefault.AddDynamic(this, &ASortObjects::SetMeshesDefaults);
	}

	// Define the ManipulateMeshes default Transform
	for (AStaticMeshActor* _CurrentStaticMesh : ManipulateMeshes)
	{
		FTransform _CurrentStaticMeshTransform = _CurrentStaticMesh->GetActorTransform();
		DefaultManipulateMeshesTransforms.Add(_CurrentStaticMesh, _CurrentStaticMeshTransform);
	}
}

void ASortObjects::SetMeshesSorted()
{
	bIsToDefault = false;

	RandomManipulateMeshesTransforms.Empty();

	// Define the random locations and rotations
	for (AStaticMeshActor* _CurrentStaticMesh : ManipulateMeshes)
	{
		FVector _CurrentRandomLocation = DefaultManipulateMeshesTransforms.Find(_CurrentStaticMesh)->GetLocation();
		FRotator _CurrentRandomRotation = DefaultManipulateMeshesTransforms.Find(_CurrentStaticMesh)->GetRotation().Rotator();

		float _NegativeRadius = SortRadius * -1;
		_CurrentRandomLocation.X += FMath::RandRange(_NegativeRadius, SortRadius);
		_CurrentRandomLocation.Y += FMath::RandRange(_NegativeRadius, SortRadius);

		_CurrentRandomRotation.Yaw += FMath::RandRange(0.0f, 360.0f);

		FTransform _CurrentRandomTransform = FTransform(_CurrentRandomRotation, _CurrentRandomLocation, FVector(1, 1, 1));
		RandomManipulateMeshesTransforms.Add(_CurrentStaticMesh, _CurrentRandomTransform);
	}

	GetWorld()->GetTimerManager().SetTimer(ManipulateMeshesTimer, this, &ASortObjects::VisualManipulate, 0.01f, true);
}

void ASortObjects::SetMeshesDefaults()
{
	bIsToDefault = true;

	GetWorld()->GetTimerManager().SetTimer(ManipulateMeshesTimer, this, &ASortObjects::VisualManipulate, 0.01f, true);
}

void ASortObjects::VisualManipulate()
{
	FTransform _CurrentTransform;
	FTransform _TargetTransform;
	FVector _LocationLerp;
	FRotator _RotationLerp;

	for (AStaticMeshActor* _CurrentStaticMesh : ManipulateMeshes)
	{
		_CurrentTransform = _CurrentStaticMesh->GetActorTransform();
		_TargetTransform = bIsToDefault ? *DefaultManipulateMeshesTransforms.Find(_CurrentStaticMesh) : *RandomManipulateMeshesTransforms.Find(_CurrentStaticMesh);
		_LocationLerp = FMath::Lerp(_CurrentTransform.GetLocation(), _TargetTransform.GetLocation(), 0.1f);
		_RotationLerp.Yaw = FMath::Lerp(_CurrentTransform.GetRotation().Rotator().Yaw, _TargetTransform.GetRotation().Rotator().Yaw, 0.1f);

		_CurrentStaticMesh->SetActorLocation(_LocationLerp);
		_CurrentStaticMesh->SetActorRotation(_RotationLerp);
	}
}
