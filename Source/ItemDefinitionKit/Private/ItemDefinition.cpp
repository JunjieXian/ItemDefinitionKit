// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDefinition.h"

const UItemFragment* UItemDefinition::FindFragmentByClass(const TSubclassOf<UItemDefinition> ItemDefinition, const TSubclassOf<UItemFragment> FragmentClass) {
	if (ItemDefinition && FragmentClass) {
		UItemDefinition* ItemCDO = ItemDefinition.GetDefaultObject();

		for (const TObjectPtr<UItemFragment>& Fragment : ItemCDO->ItemFragments) {
			if (Fragment && Fragment->IsA(FragmentClass)) {
				return Fragment;
			}
		}
	}
	return nullptr;
}
