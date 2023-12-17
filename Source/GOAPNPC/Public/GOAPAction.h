/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#pragma once

#include "GOAPWorldState.h"
#include "GOAPAtom.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/NoExportTypes.h"

#include "GameplayTags.h"

#include "GOAPAction.generated.h"

 /**
 * GOAPAction class contains every attribute and function needed to define an action.
 * Represent edges in the planner algorithm.
 */
UCLASS(Blueprintable)
class GOAPNPC_API UGOAPAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	FString name;

	// Cost of the action. The planner will take this into account when making the cheapest plan.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float cost;

	// Preconditions or requirements needed to perform the action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WorldState)
	TArray<FAtom> preconditions;

	// Effects or postconditions caused by the action.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WorldState)
	TArray<FAtom> effects;

private:
	GOAPWorldState wsPreconditions;

	GOAPWorldState wsEffects;

public:
	// Optional function to check if it's possible to perform the action.
	UFUNCTION(BlueprintNativeEvent, Category = GOAPAction)
	bool checkProceduralPrecondition(APawn* p);
	bool checkProceduralPrecondition_Implementation(APawn* p);

	// Performs the action.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = GOAPAction)
	bool doAction(APawn* p);

	// Generate action's preconditions and effects.
	void create_P_E();

	// COMPARATORS
	bool operator==(const UGOAPAction& action) const;
	bool operator!=(const UGOAPAction& action) const;

	// GETS
	FString getName() const;

	float getCost() const;

	const GOAPWorldState& getPreconditions() const;

	const GOAPWorldState& getEffects() const;

	// SETS
	void setName(FString n);

	void setCost(float c);

	void setPreconditions(GOAPWorldState preconditionAtoms);

	void setEffects(GOAPWorldState effectAtoms);
};
