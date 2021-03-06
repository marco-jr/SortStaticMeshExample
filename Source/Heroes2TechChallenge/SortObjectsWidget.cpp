// Code developed by Marco Antônio, contact: https://www.linkedin.com/in/marco-a-junior/


#include "SortObjectsWidget.h"
#include "Components/Button.h"

void USortObjectsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SortButton->OnClicked.AddDynamic(this, &USortObjectsWidget::SortMeshes);
	DefaultButton->OnClicked.AddDynamic(this, &USortObjectsWidget::DefaultMeshes);
}

void USortObjectsWidget::SortMeshes()
{
	OnSort.Broadcast();
}

void USortObjectsWidget::DefaultMeshes()
{
	OnDefault.Broadcast();
}
