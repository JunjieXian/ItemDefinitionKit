// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fragments/ItemFragment.h"
#include "UObject/Object.h"
#include "ItemDefinition.generated.h"

/**
 *   Item基础定义，用于描述物品的属性、行为和功能。可以通过继承该类来创建具体的物品定义。
 */
UCLASS(Blueprintable, BlueprintType, Abstract, Const)
class ITEMDEFINITIONKIT_API UItemDefinition : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	FText ItemDescription;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	// TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Fragments")
	TArray<TObjectPtr<UItemFragment>> ItemFragments;

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DeterminesOutputType = "FragmentClass"), Category = "Fragments")
	static const UItemFragment* FindFragmentByClass(const TSubclassOf<UItemDefinition> ItemDefinition, const TSubclassOf<UItemFragment> FragmentClass);
};
