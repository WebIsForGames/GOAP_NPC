/**
	GOAP NPC: Goal-Oriented Action Planning for Non-Player Characters
	Copyright © 2022 Narratech Laboratories

	Authors: Diego Romero-Hombrebueno Santos, Mario Sánchez Blanco, José Manuel Sierra Ramos, Daniel Gil Aguilar and Federico Peinado
	Website: https://narratech.com/project/goap-npc/
 */
#include "GOAPAtom.h"

#if WITH_EDITORONLY_DATA
#include "GameplayTagsEditorModule.h"

void FAtom::PostSerialize(const FArchive& Ar)
{
	if (Ar.IsLoading() && !name_DEPRECATED.IsEmpty())
	{
		FString tagName = TEXT("GOAP.") + name_DEPRECATED;
		tag = UGameplayTagsManager::Get().RequestGameplayTag(FName(tagName), false);
		if (!tag.IsValid())
		{
			IGameplayTagsEditorModule& tagsEditor = IGameplayTagsEditorModule::Get();
			bool result = tagsEditor.AddNewGameplayTagToINI(tagName);

			tag = UGameplayTagsManager::Get().RequestGameplayTag(FName(tagName));
			if (tag.IsValid())
			{
				name_DEPRECATED = "";
			}
			else
			{
				UE_LOG(LogTemp, Fatal, TEXT("Can't get Gameplay tag for (%s)"), *tagName);
			}
		}
	}

}
#endif // WITH_EDITORONLY_DATA
