// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyActor.h"
#include "GoLUser.h"
//#include "UObject/UObjectGlobals.h"


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NavigationComponent.generated.h"

//#include "MyActor.h"
//#include "Prototype.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UNavigationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNavigationComponent();
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool creatureIsPlayer = false;
    
    UPROPERTY(EditAnywhere)
    AMyActor* globalActor; // указатель на глобального актора
    AActor* Owner; // указатель на владельца компонента
    AGoLUser* GOLref; // указатель на GolUser в сцене
    
    enum dir {right,up,left,down};
    UPROPERTY()
    int R = 1;

    
    struct fieldcell{
        dir direction;
        unsigned char steps;
        unsigned char stepsOnLava;
    };
    
    //---------------------------------
    //заглушки ненужные
    struct pos {
        int x;
        int y;
    };
    pos Position;
    
    int energyToTraverseCell(int x,int y);//{return 1;}
    bool checkBlocked(int x,int y); //{return false;}
    //---------------------------------
    
    fieldcell** field = nullptr; // то самое поле размера (2r+1)x(2r+1), в котором хранятся возможные ходы. Необходимо обновлять после каждого подшага
    
    void calculatepathsSTART(int radius); // старт расчета из точки позиции npc
    
    void calculatepaths(int radius, int stepstaken,int stepsOnLava, dir from, int x, int y);
    // функция, рекурсивно вычисляющая все возможные ходы и сколько энергии тратится на них.
    // Записывает результат в массив fieldcell размера (2r+1)x(2r+1), в котором хранится направление того, откуда был предыдущий ход для восстановления всего пути к клетке,
    // и кол-во шагов, за которые можно добраться до этой клетки (ограничение в 253). Центр массива отвечает за позицию игрока (или npc)
    // код 255 - абсолютный max, код 254 - на клетке "лава"
    
    void resetfield(int oldRadius,int newRadius);
    
    UFUNCTION(BlueprintCallable, Category = "NavigationCustom")
    void SetUp(int x, int y, int newRadius, int Energy); // вызывать прсле хода - обновление массива field для последующего использования и сам рассчет возможных ходов вызывается здесь
    UFUNCTION(BlueprintCallable, Category = "NavigationCustom")
    TArray<int> getpath(int x, int y); //получить путь к выбраной клетке

	UFUNCTION(BlueprintCallable, Category = "NavigationCustom")
	void SetGlobalActor(AMyActor * Actor, AGoLUser * goluser);
    
    //---------------------------------
    //заглушки ненужные
    
    /*
    struct pos {
        int x;
        int y;
    };
    pos Position;*/
    
    //int energyToTraverseCell(int x,int y);//{return 1;}
    //bool checkBlocked(int x,int y); //{return false;}
    
    //---------------------------------
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    

		
};
