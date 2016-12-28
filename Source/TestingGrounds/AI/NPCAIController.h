// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPCAIController.generated.h"

/**
 * 
 */

UCLASS()
class TESTINGGROUNDS_API ANPCAIController : public AAIController
{
	GENERATED_BODY()

	ANPCAIController(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay();

	virtual void Possess(class APawn* InPawn) override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Source,  FAIStimulus Stimulus);

	UAIPerceptionComponent* PerceptionComponent;

	UBlackboardComponent* BlackboardComp;

	UBehaviorTreeComponent* BehaviorComp;

	class UAISenseConfig_Sight* SightConfig;
	//void UpdatePerception(TArray<AActor*> SensedActor);

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName EnemyKeyName = "Enemy";
};

