// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GOAPPlanner.h"

#include "GOAPPlannerComponent.generated.h"

// TODO: Make as UBrainComponent

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOAPNPC_API UGOAPPlannerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGOAPPlannerComponent();

	// Creates actions plan
	UFUNCTION(BlueprintCallable, Category = GOAPController)
	bool GeneratePlan(APawn* Pawn);

	// Returns the actions that make up the plan.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
	TArray<UGOAPAction*> GetPlan();

	UFUNCTION(BlueprintCallable, Category = GOAPController)
	bool PerformSingleAction(APawn* Pawn);

	// Sets the goal of the AI, this function can also be used to change the goal.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
	void SetGoal(const TArray<FAtom>& NewGoal);

	// Adds or modifies atoms from the desired world state. Atoms already existing in the desired world state are modified by new input values.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
	void UpdateGoal(const TArray<FAtom>& Atoms);

	// Sets the current world state of the AI, this function can also be used to change the current world state.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
	void SetCurrentWorld(const TArray<FAtom>& NewCurrentWorld);

	// Adds or modifies atoms from the current world state. Atoms already existing in the current world state are modified by new input values.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
	void UpdateCurrentWorld(const TArray<FAtom>& Atoms);

	// Returns the current world state atoms.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
	TArray<FAtom> GetCurrentWorldStateAtoms() const;

	// Returns the desired world state atoms.
	UFUNCTION(BlueprintCallable, Category = GOAPController)
	TArray<FAtom> GetDesiredWorldStateAtoms() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// State of the current world.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
	TArray<FAtom> CurrentWorld;

	// State of the world in wich the goal has been achieved.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
	TArray<FAtom> DesiredWorld;

	// List of actions AI can do.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
	TArray<TSubclassOf<UGOAPAction>> Actions;

	// Maximum algorithm depth.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GOAP)
	int MaxDepth = 100;

private:
	GOAPPlanner* planner = nullptr;

	TArray<UGOAPAction*> auxActions;
	TArray<UGOAPAction*> plan;

	GOAPWorldState wsCurrentWorld;
	GOAPWorldState wsDesiredWorld;
};
