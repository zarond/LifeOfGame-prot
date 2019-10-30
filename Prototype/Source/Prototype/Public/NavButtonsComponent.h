// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "NavigationComponent.h"
#include "NavButton.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NavButtonsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UNavButtonsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNavButtonsComponent();
    TArray<ANavButton*> Buttons;
    UNavigationComponent* NavComp;
    AActor* Parent;
    UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ANavButton> ButtonToSpawn;
    
	UFUNCTION(BlueprintCallable, Category = "NavigationCustom")
    void UpdateButtons();
	//UFUNCTION(BlueprintCallable, Category = "NavigationCustom")
	//void SetNavButton(ANavButton* Button);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
