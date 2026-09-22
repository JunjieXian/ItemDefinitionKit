// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemFunctionLibrary.h"
#include "ItemDefinition.h"

UItemInstance* UItemFunctionLibrary::ConstructItemInstanceInitialize(const TSubclassOf<UItemDefinition> ItemDefinition, const TMap<FGameplayTag, float>& InitAttributes,
                                                                     UObject* Outer) {
	if (!ItemDefinition) {
		return nullptr;
	}

	if (!Outer) {
		Outer = GetTransientPackage();
	}

	UItemInstance* ItemInstance = NewObject<UItemInstance>(Outer);
	ItemInstance->Initialize(ItemDefinition, InitAttributes);
	return ItemInstance;
}
