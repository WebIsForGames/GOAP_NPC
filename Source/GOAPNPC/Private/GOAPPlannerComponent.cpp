// Copyright Epic Games, Inc. All Rights Reserved.

#include "GOAPPlannerComponent.h"

// Sets default values for this component's properties
UGOAPPlannerComponent::UGOAPPlannerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UGOAPPlannerComponent::BeginPlay()
{
	// Loads actions.
	for (auto i = 0; i < Actions.Num(); ++i)
	{
		if (Actions[i])
		{
			FString aux = Actions[i].GetDefaultObject()->GetName();
			auxActions.Push(Actions[i].GetDefaultObject());
		}
	}

	// Loads Current World.
	for (FAtom atom : CurrentWorld)
		wsCurrentWorld.addAtom(atom.tag, atom.value);

	// Loads Desired World.
	for (FAtom atom : DesiredWorld)
		wsDesiredWorld.addAtom(atom.tag, atom.value);

	// Loads actions' preconditions and effects.
	for (UGOAPAction* a : auxActions)
		a->create_P_E();

	// Loads Planner.
	planner = new GOAPPlanner(&wsCurrentWorld, &wsDesiredWorld, auxActions);
	planner->setMaxDepth(MaxDepth);

	// Error messages.
	if (auxActions.Num() == 0)
		UE_LOG(LogTemp, Warning, TEXT("Actions not found."));

	if (wsCurrentWorld.isEmpty())
		UE_LOG(LogTemp, Warning, TEXT("Undefined Current World."));

	if (wsDesiredWorld.isEmpty())
		UE_LOG(LogTemp, Warning, TEXT("Undefined Desired World.")); // This is normal in the first execution, isn´t it?

	Super::BeginPlay();
}


bool UGOAPPlannerComponent::GeneratePlan(APawn* Pawn)
{
	if (!Pawn)
		return false;

	if ((auxActions.Num()) > 0 && !wsCurrentWorld.isEmpty() && !wsDesiredWorld.isEmpty())
	{
		// Creates the cheapest plan of actions.
		plan = planner->generatePlan(Pawn);
		return true;
	}

	return false;
}

TArray<UGOAPAction*> UGOAPPlannerComponent::GetPlan()
{
	return plan;
}

void UGOAPPlannerComponent::SetGoal(const TArray<FAtom>& newGoal)
{
	wsDesiredWorld.cleanAtoms();
	UpdateGoal(newGoal);
}

void UGOAPPlannerComponent::UpdateGoal(const TArray<FAtom>& atoms)
{
	for (FAtom atom : atoms)
		wsDesiredWorld.addAtom(atom.tag, atom.value);
}

void UGOAPPlannerComponent::SetCurrentWorld(const TArray<FAtom>& newCurrentWorld)
{
	wsCurrentWorld.cleanAtoms();
	UpdateCurrentWorld(newCurrentWorld);
}

void UGOAPPlannerComponent::UpdateCurrentWorld(const TArray<FAtom>& atoms)
{
	for (FAtom atom : atoms)
		wsCurrentWorld.addAtom(atom.tag, atom.value);
}

TArray<FAtom> UGOAPPlannerComponent::GetCurrentWorldStateAtoms() const
{
	TArray<FAtom> worldStateAtoms;
	for (auto atom : wsCurrentWorld.getAtoms())
	{
		worldStateAtoms.Add({ atom.Key, atom.Value });
	}

	return worldStateAtoms;
}

TArray<FAtom> UGOAPPlannerComponent::GetDesiredWorldStateAtoms() const
{
	TArray<FAtom> worldStateAtoms;
	for (auto atom : wsDesiredWorld.getAtoms())
	{
		worldStateAtoms.Add({ atom.Key, atom.Value });
	}

	return worldStateAtoms;
}

bool UGOAPPlannerComponent::PerformSingleAction(APawn* Pawn)
{
	if (!Pawn)
		return false;

	if (plan.Num() > 0)
	{
		// Gets next action to perform.
		UGOAPAction* aux = plan.Last();

		// Performs an action and when it's done its effects are applied, changing the current world state.
		if (aux->doAction(Pawn))
		{
			wsCurrentWorld.joinWorldState(aux->getEffects());
		}

		return true;
	}

	return false;
}