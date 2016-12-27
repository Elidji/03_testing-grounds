// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ClearBlackboardValue.h"

/* AI Module includes */
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


EBTNodeResult::Type UClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// first get the blackboard component
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	// protect component
	if (!BlackboardComp) { return EBTNodeResult::Failed; }

	// clear the selected key 
	BlackboardComp->ClearValue(ClearKey.SelectedKeyName);
	
	// finish execute
	return EBTNodeResult::Succeeded;
}
