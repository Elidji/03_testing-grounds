// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "AI/PatrolRoute.h"


TArray<AActor*> UPatrolRoute::GetPatrolPoints() const
{
	return SentryPatrolPoints;
}