/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#include "GOAPAction.h"


void UGOAPAction::create_P_E()
{
	for (FAtom& itP : preconditions)
	{
		wsPreconditions.addAtom(itP.tag, itP.value);
	}

	for (FAtom& itE : effects)
	{
		wsEffects.addAtom(itE.tag, itE.value);
	}
}

bool UGOAPAction::operator==(const UGOAPAction& a) const
{
	return	(cost == a.getCost()) &&
			(wsPreconditions == a.getPreconditions()) &&
			(wsEffects == a.getEffects());
}

bool UGOAPAction::operator!=(const UGOAPAction& a) const
{
	return !(*this == a);
}

// GETS

FString UGOAPAction::getName() const
{
	return name;
}

float UGOAPAction::getCost() const
{
	return cost;
}

const GOAPWorldState& UGOAPAction::getPreconditions() const
{
	return wsPreconditions;
}

const GOAPWorldState& UGOAPAction::getEffects() const
{
	return wsEffects;
}

// SETS

void UGOAPAction::setName(FString n)
{
	name = n;
}

void UGOAPAction::setCost(float c)
{
	cost = c;
}

void UGOAPAction::setPreconditions(GOAPWorldState pre)
{
	wsPreconditions = pre;
}

void UGOAPAction::setEffects(GOAPWorldState ef)
{
	wsEffects = ef;
}

bool UGOAPAction::checkProceduralPrecondition_Implementation(APawn* p)
{
	return true;
}
