// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPCAIController.generated.h"

/**
 * IN PROGRESS, REALLY MESSY AND NOT WORKING YET 

	Implementation Notes before I forget later:
	My instinct tells me that the reason this isn't working is because I have the 
	behavior tree variable inside the AIController rather than the sentry pawn itself. 

	Also possibly the BehaviorComp, need to investigate how BattleTanks implementation is set up.

	To do this I will need to create a NPC character base class that derives from
	ACharacter and then reparent the blueprint FirstPersonCharacter to this new derived class, 
	call it ANPCCharacter or ASentryCharacter. ASentryCharacter will be a base class, 
	except for the BehaviorTree components that I need inorder to run the assigned behavior tree. 

	The rest of the implementation comes directly from blueprint I believe (this is why we reparent the current 
	FirstPersonCharacter blueprint to the new class).

	This way I will be able to assign the SentryBehavior behavior tree to the sentry pawn in blue print
	and have it referenced direclty in C++ by the AIController. 

	Besides this, I then need to rework the OnTargetPerceptionUpdated so that it casts to the pawn and gets the behavior 
	tree to run and blackboard asset associated with this behavior tree directly from the Sentry character(NPC). 
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

