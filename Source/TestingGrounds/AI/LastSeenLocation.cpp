// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "LastSeenLocation.h"

/* AI Module includes */
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

void ULastSeenLocation::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	// get the blackboard component
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	/* The enemy key in blackboard is set to object>Actor in UE4 editor in order to set the focus below. So we have to get the blackboard object as an actor via a cast to AActor */
	AActor* LastSensedActor = Cast<AActor>(BlackboardComp->GetValueAsObject(ActorKey.SelectedKeyName));

	// protect components
	if (!BlackboardComp || !LastSensedActor) { return; }

	// get the sensed actors last location
	auto LastActorLocation = LastSensedActor->GetActorLocation();

	// if there is a sensed actor, update last actor location
	// otherwise clear the value
	if(LastSensedActor->IsValidLowLevel())
	{
		BlackboardComp->SetValueAsVector(LastKnownLocationKey.SelectedKeyName, LastActorLocation);
	}
}
