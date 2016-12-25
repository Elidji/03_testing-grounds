// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "FocusAtActor.h"

/* AI Module includes */
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UFocusAtActor::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// get the AI controller 
	auto AIController = OwnerComp.GetAIOwner();

	// get the blackboard component
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	// get the new focus point by sending the focus key 
	auto NewFocusPoint = BlackboardComp->GetValueAsVector(FocusKey.SelectedKeyName);

	// set the focal point based on the new focus point from blackboard
	AIController->SetFocalPoint(NewFocusPoint);

	UE_LOG(LogTemp, Warning, TEXT("Trying to execute!"))
	return EBTNodeResult::Succeeded;

}
