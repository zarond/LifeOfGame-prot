// Fill out your copyright notice in the Description page of Project Settings.


#include "NavButtonsComponent.h"

// Sets default values for this component's properties
UNavButtonsComponent::UNavButtonsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
    
    Parent = GetOwner();
    //NavComp = Cast<UNavigationComponent>(Parent->GetComponentByClass(UNavigationComponent::StaticClass()));
    NavComp = Parent->FindComponentByClass<UNavigationComponent>();
}

void UNavButtonsComponent::UpdateButtons(){
    Buttons.Empty();
    int R = NavComp->R;
    if (NavComp->field == nullptr) return;
    for (int i=0;i<2*R+1;++i)
        for (int j=0;j<2*R+1;++j){
            if (NavComp->field[i][j].steps!= 255) {
                FVector Location = GetActorLocation();
                Location.X += (i-R)*100.0f;
                Location.Y += (j-R)*100.0f;
                FActorSpawnParameters SpawnInfo;
                AActor* tmp = GetWorld()->SpawnActor(Location,FRotator::ZeroRotator);
                Buttons.Add(tmp);
            }
        }
}


// Called when the game starts
void UNavButtonsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNavButtonsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

