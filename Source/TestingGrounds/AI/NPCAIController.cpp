// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "NPCAIController.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"


ANPCAIController::ANPCAIController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Setup the perception component
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	/// SIGHT CONFIGURATION
	SightConfig->SightRadius = 800.0f;
	SightConfig->LoseSightRadius = 1000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 140.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComponent->ConfigureSense(*SightConfig);

	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ANPCAIController::OnTargetPerceptionUpdated);

	//BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	//BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void ANPCAIController::BeginPlay()
{
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetControlledPawn());
}

void ANPCAIController::Possess(APawn * InPawn)
{
	//BlackboardComp->InitializeBlackboard(*this->BehaviorTree->BlackboardAsset);

	//use blackboard
	this->UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComp);

	// Run the behavior tree
	this->RunBehaviorTree(BehaviorTree);
}

void ANPCAIController::OnTargetPerceptionUpdated(AActor* Source, FAIStimulus Stimulus)
{
	//Get actor tag
	if (!Source->ActorHasTag(FName("Enemy")))
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			BlackboardComp->SetValueAsObject(EnemyKeyName, Source);
		}

		else {
			BlackboardComp->ClearValue(EnemyKeyName);
		}
	}
}




