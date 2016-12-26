// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "SetFocus.h"

/* AI Module includes */
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

void USetFocus::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	// get the AI controller 
	auto AIController = OwnerComp.GetAIOwner();

	// get the blackboard component
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	// protect components
	if (!AIController && !BlackboardComp) { return; }

	/* The enemy key in blackboard is set to object>Actor in UE4 editor in order to set the focus below. So we have to get the blackboard object as an actor via a cast to AActor */
	AActor* FocusOnActor = Cast<AActor>(BlackboardComp->GetValueAsObject(FocusKey.SelectedKeyName));

	// set the focal point based on the new focus point from blackboard
	AIController->SetFocus(FocusOnActor);
	//UE_LOG(LogTemp, Warning, TEXT("Trying to execute!"))
}
