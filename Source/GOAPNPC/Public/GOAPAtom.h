/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"

#include "GOAPAtom.generated.h"

 /**
 * Auxiliary struct to get WorldState's atoms from Blueprints' description.
 */
USTRUCT(BlueprintType)
struct GOAPNPC_API FAtom
{
	GENERATED_BODY()

	FAtom() = default;

	FAtom(FGameplayTag _tag, bool _value)
		: tag(_tag)
		, value(_value)
	{}

#if WITH_EDITORONLY_DATA
	// DEPRECATED: Name of the atom (predicate).
	UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use gameplay tag instead."))
	FString name_DEPRECATED;

	void PostSerialize(const FArchive& Ar);
#endif

	// Name of the atom (predicate).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Category = "Atom"))
	FGameplayTag tag;

	// Value of the atom (truth value).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Category = "Atom"))
	bool value = false;
};


#if WITH_EDITORONLY_DATA
template<>
struct TStructOpsTypeTraits<FAtom> : public TStructOpsTypeTraitsBase2<FAtom>
{
	enum
	{
		WithPostSerialize = true
	};
};
#endif


USTRUCT(Blueprintable)
struct GOAPNPC_API FAtomArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FAtom> DesiredState;
};
