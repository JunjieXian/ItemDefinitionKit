// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInstance.h"
#include "ItemDefinition.h"

float UItemInstance::GetAttributeValue(FGameplayTag AttributeTag) {
	return ItemAttributes.FindRef(AttributeTag);
}

void UItemInstance::SetAttributeValue(FGameplayTag AttributeTag, float AttributeValue) {
	ItemAttributes.Add(AttributeTag, AttributeValue);
}

void UItemInstance::Initialize(TSubclassOf<UItemDefinition> ItemDef, const TMap<FGameplayTag, float>& InitAttributes) {
	if (!ItemDef) {
		return;
	}

	ItemDefinition = ItemDef;

	UItemDefinition* ItemCDO = ItemDefinition.GetDefaultObject();
	for (const TObjectPtr<UItemFragment>& Fragment : ItemCDO->ItemFragments) {
		Fragment->OnInstanceCreated(this);
	}

	if (!InitAttributes.IsEmpty()) {
		ItemAttributes = InitAttributes;
	}
}

const UItemFragment* UItemInstance::FindFragmentByClass(const TSubclassOf<UItemFragment> FragmentClass) const {
	if (!ItemDefinition || !FragmentClass) {
		return nullptr;
	}

	return UItemDefinition::FindFragmentByClass(ItemDefinition, FragmentClass);
}
