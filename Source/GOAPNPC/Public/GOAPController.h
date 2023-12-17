/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "GOAPAtom.h"

#include "GOAPController.generated.h"


class UGOAPPlannerComponent;


 /**
 * AIController containg the planner, states of the current and desired world, and the list of available actions the AI can perform.
 * Current world and desired world are private for each AI, but it's possible to create a global current world to notify changes to other AIs.
  */
UCLASS()
class GOAPNPC_API AGOAPController : public AAIController
{
	GENERATED_BODY()

public:
	AGOAPController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* pawn) override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
	TArray<FAtomArray> DesiredStates;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UGOAPPlannerComponent* PlannerComponent;

	// Creates and execute the plan.
	UFUNCTION(BlueprintCallable)
	bool ExecuteGOAP();

	// Debug info
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DebugPrint;

private:
	void ShowDebugInfo();
};
