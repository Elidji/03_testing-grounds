// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Public/PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	///GET PATROL POINTS
	// access the AI controller that owns the pawn
	auto AIController = OwnerComp.GetAIOwner();

	// access the pawn that's being controlled by the AI Controller
	auto ControlledPawn = AIController->GetPawn();

	// now that patrolroute is added to the pawn as a component, we can find it by looking at FindComponentByClass
	// remember that the hash include of PatrolRoute allows us to send UPatrolRoute as a type
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	// Ensure that a patrol route component exists on the pawn
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// next access the PatrolPoints array now that we have access to the patrol route
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

	// Protect against empty patrol routes
	if (PatrolPoints.Num() == 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("A Sentry is missing patrol points."));
		return EBTNodeResult::Failed;
	}

	///SET NEXT WAYPOINT
	//first we need to get the blackboard component
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	/*IndexKey is a FBlackboardKeySelector, sending it's FName to GetValueAsInt
	to get back the integer value which corresponds to the index of the component 
	sent. Basicaly to see what the blackboard component is pointed to. We've pointed it
	to nextWaypointKeyIndex. This gets the next index of the waypoint we need to go to.*/
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	/* Here we set the next waypoint based on the patrol point index which we found above.*/
	BlackboardComp->SetValueAsObject(NextWaypointKey.SelectedKeyName, PatrolPoints[Index]);

	///CYCLE INDEX
	/*incrementing the index and then taking the modulo of the length makes it run in a cycle fashion
	without having to set index back to zero*/
	auto NextIndex = (Index + 1) % PatrolPoints.Num();

	// increment the index by setting the indexKey value to the next index that was determined above
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
