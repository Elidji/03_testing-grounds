// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "LastSeenLocation.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API ULastSeenLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector LastKnownLocationKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector ActorKey;
	
};
