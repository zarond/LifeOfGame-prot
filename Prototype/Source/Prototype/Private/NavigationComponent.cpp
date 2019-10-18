// Fill out your copyright notice in the Description page of Project Settings.


#include "NavigationComponent.h"

#include "Algo/Reverse.h"

// Sets default values for this component's properties
UNavigationComponent::UNavigationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
    //globalActor = (ATurnBased*)GetWorld()->GetAuthGameMode().globalActor;
    Owner = GetOwner();
    Position.x = 0;
    Position.y = 0;
}


// Called when the game starts
void UNavigationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNavigationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//-------------------------
int UNavigationComponent::energyToTraverseCell(int x,int y) {return 1;}
bool UNavigationComponent::checkBlocked(int x,int y) {return false;}
//-------------------------

void UNavigationComponent::resetfield(int oldRadius,int newRadius){
    if (oldRadius < newRadius){
        if (field!=nullptr){
            for (int i=0;i<2*oldRadius+1;++i) delete[] field[i];
        }
        if (newRadius>0){
            field = new fieldcell*[2*newRadius+1];
            for (int i=0;i<2*newRadius+1;++i) field[i] = new fieldcell[2*newRadius+1];
        } else field = nullptr;
    }
    for (int i=0;i<newRadius;++i)
        for (int j=0;j<newRadius;++j)
            field[i][j].steps = 255;
}


void UNavigationComponent::calculatepathsSTART(int radius){
    calculatepaths(radius,0,left,1,0);
    calculatepaths(radius,0,down,0,1);
    calculatepaths(radius,0,right,-1,0);
    calculatepaths(radius,0,up,0,-1);
}


void UNavigationComponent::calculatepaths(int radius, int stepstaken, dir from, int x, int y){
    if (checkBlocked(Position.x + x,Position.y + y)) return; // нужна функция проверяющая карту на возможность пройти. Position - относится к npc, к которому прикреплен компонент
    if (stepstaken>radius) return; // шаги закончились
    if (stepstaken >= field[x + radius][y + radius].steps) return;
    field[x + radius][y + radius].steps = stepstaken;
    field[x + radius][y + radius].direction = from;
    unsigned char energylost = 0;
    switch (from){
        case right:
            energylost = energyToTraverseCell(Position.x + x + 1 ,Position.y + y); // функция достающая из карты число труднопроходимости клетки, с которой сходили
            break;
        case up:
            energylost = energyToTraverseCell(Position.x + x ,Position.y + y + 1);
            break;
        case left:
            energylost = energyToTraverseCell(Position.x + x - 1 ,Position.y + y);
            break;
        case down:
            energylost = energyToTraverseCell(Position.x + x ,Position.y + y - 1);
            break;
    }
    stepstaken += energylost;
    // (x,y)=(0,0) отвечает за (radius,radius) - центр в field
    if (x+1<radius)  calculatepaths(radius,stepstaken,left,x+1,y);
    if (y+1<radius)  calculatepaths(radius,stepstaken,down,x,y+1);
    if (x-1>-radius) calculatepaths(radius,stepstaken,right,x-1,y);
    if (y-1>-radius) calculatepaths(radius,stepstaken,up,x,y-1);
    // здесь направление ставится противоположное, чтобы уже в следующем шаге сразу сказать ОТКУДА был сделан предыдущий
    
}

void UNavigationComponent::SetUp(int x, int y, int newRadius, int Energy){
    Position.x = x;
    Position.y = y;
    resetfield(R,newRadius);
    R = newRadius;
    calculatepathsSTART(R);
    return;
}

UFUNCTION(BlueprintCallable, Category = "NavigationCustom")
TArray<int> UNavigationComponent::getpath(int x, int y){
    TArray<int> dirArray;
    for (int i=0;i<R;++i){
        if (x==0 && y==0) break;
        //dirArray.Add((int)field[x + R][y + R].direction);
        switch (field[x + R][y + R].direction){
            case right:
                x+=1;
                dirArray.Add(2);
                break;
            case up:
                y+=1;
                dirArray.Add(3);
                break;
            case left:
                x-=1;
                dirArray.Add(0);
                break;
            case down:
                y-=1;
                dirArray.Add(1);
                break;
        }
    }
    Algo::Reverse(dirArray);
    return dirArray;
}

