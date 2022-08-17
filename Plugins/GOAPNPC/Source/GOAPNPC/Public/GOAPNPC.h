/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters.

	Publishers/Authors:
		-	Diego Romero-Hombrebueno Santos.
		-	Mario Sanchez Blanco.
		-	Jose Manuel Sierra Ramos.

	Published on 2020.

	Updated by Daniel Gil Aguilar on 2022
 */
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGOAPNPCModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
