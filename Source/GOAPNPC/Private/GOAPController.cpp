/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright � 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario S�nchez Blanco, Jos� Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */

#include "GOAPController.h"
#include "GOAPPlannerComponent.h"

AGOAPController::AGOAPController()
{
	PlannerComponent = CreateDefaultSubobject<UGOAPPlannerComponent>(TEXT("GOAPPlannerComponent"));
}

void AGOAPController::BeginPlay()
{
	Super::BeginPlay();
}

void AGOAPController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
}

void AGOAPController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AGOAPController::ExecuteGOAP()
{
	if (!GetPawn())
		return false;

	for (const FAtomArray& goal : DesiredStates)
	{
		PlannerComponent->SetGoal(goal.DesiredState);
		if (PlannerComponent->GeneratePlan(GetPawn()) && (PlannerComponent->GetPlan().Num() > 0))
		{
			ShowDebugInfo();
			return PlannerComponent->PerformSingleAction(GetPawn());
		}
	}

	return false;
}

void AGOAPController::ShowDebugInfo()
{
	if (!DebugPrint || !GEngine || !GetPawn())
		return;

	FString name = GetPawn()->GetName();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Plan generated by: " + name), false);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("controller: " + this->GetName()), false);

	auto plan = PlannerComponent->GetPlan();
	for (int i = 0; i < plan.Num(); i++)
	{
		if (i != 0)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("--->"), false);
		FString action = plan[i]->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("" + action), false);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("\n"), false);
}
