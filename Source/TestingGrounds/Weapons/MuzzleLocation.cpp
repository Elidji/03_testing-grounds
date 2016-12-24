// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "MuzzleLocation.h"


// Sets default values for this component's properties
UMuzzleLocation::UMuzzleLocation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// Place muzzle location at the front of the gun barrel
	SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
}


// Called when the game starts
void UMuzzleLocation::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMuzzleLocation::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

