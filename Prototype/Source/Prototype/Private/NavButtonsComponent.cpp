// Fill out your copyright notice in the Description page of Project Settings.

#include "NavButtonsComponent.h"

// Sets default values for this component's properties
UNavButtonsComponent::UNavButtonsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
    /*
    Parent = GetOwner();
    if (Parent == nullptr) UE_LOG(LogTemp, Warning, TEXT("no Parent during constructor"));
    //NavComp = Cast<UNavigationComponent>(Parent->GetComponentByClass(UNavigationComponent::StaticClass()));
	if (Parent!=NULL)	NavComp = Parent->FindComponentByClass<UNavigationComponent>();
     */
}

void UNavButtonsComponent::UpdateButtons(){
    UpdateWalkButtons();
}
void UNavButtonsComponent::UpdateAttackButtons(){
    
}

void UNavButtonsComponent::UpdateWalkButtons(){
    //for (int i = 0; i < Buttons.Num(); ++i) Buttons[i]->Destroy();
    //Buttons.Empty();
    if (NavComp == nullptr) {UE_LOG(LogTemp, Warning, TEXT("no navComp"));return;}
    int R = NavComp->R;
    if (NavComp->field == nullptr) return;
    int counter = 0;
    bool hitlimit = false;
    for (int i=0;i<2*R+1;++i)
        for (int j=0;j<2*R+1;++j){
            if (NavComp->field[i][j].steps <= R) {
                FVector Location = this->Parent->GetActorLocation();
                Location.Y += (i-R)*100.0f;
                Location.X += (j-R)*100.0f;
                //Location.Z += 100.0f;
                FActorSpawnParameters SpawnInfo;
                FRotator rot = FRotator::ZeroRotator;
                switch (NavComp->field[i][j].direction) {
                    case 0:
                        //rot = FRotator::ZeroRotator;
                        rot.Yaw = 0;
                        break;
                    case 1:
                        rot.Yaw = -90;
                        break;
                    case 2:
                        rot.Yaw = 180;
                        break;
                    case 3:
                        rot.Yaw = 90;
                        break;
                }
                //ANavButton* tmp = GetWorld()->SpawnActor(ButtonToSpawn.Get(),Location, FRotator::ZeroRotator, SpawnInfo);
                ANavButton* tmp;
                if ((counter < Buttons.Num()) && hitlimit == false) {
                    tmp = Buttons[counter];
                    tmp-> SetActorLocationAndRotation(Location, rot);
                    tmp-> SetActorHiddenInGame(false);
                    tmp-> SetActorEnableCollision(true);
                    tmp-> SetActorTickEnabled(true);
                    ++counter;
                } else {
                    hitlimit = true;
                    tmp = (ANavButton*) GetWorld()->SpawnActor(ButtonToSpawn, &Location, &rot, SpawnInfo);
                    if (tmp != NULL) Buttons.Add(tmp);
                }
                //ANavButton* tmp = (ANavButton*) GetWorld()->SpawnActor(ButtonToSpawn, &Location, &rot, SpawnInfo);
                if (tmp == NULL) return;
                tmp->x = i - R;
                tmp->y = j - R;
                tmp->steps = NavComp->field[i][j].steps;
                #if WITH_EDITOR
                tmp->SetFolderPath("SpawnedActors/NavButtons");  // полезная фича
                #endif
                //Buttons.Add(tmp);
                //++counter;
            }
        }
    if (hitlimit) return;
    for (int i = counter; i < Buttons.Num(); ++i) {
        //Buttons[i]->Destroy();
        Buttons[i]-> SetActorHiddenInGame(true);
        Buttons[i]-> SetActorEnableCollision(false);
        Buttons[i]-> SetActorTickEnabled(false);
    }
}

//void UNavButtonsComponent::SetNavButton(ANavButton * Button)
//{
//	ButtonToSpawn = Button;
//}


// Called when the game starts
void UNavButtonsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Parent = GetOwner();
    if (Parent == nullptr) UE_LOG(LogTemp, Warning, TEXT("no Parent during begin play"));
    //NavComp = Cast<UNavigationComponent>(Parent->GetComponentByClass(UNavigationComponent::StaticClass()));
    if (Parent!=NULL)    NavComp = Parent->FindComponentByClass<UNavigationComponent>();
}


// Called every frame
void UNavButtonsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    
	// ...
}

