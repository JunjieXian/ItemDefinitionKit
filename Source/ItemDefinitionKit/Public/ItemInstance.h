// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ItemInstance.generated.h"

class UItemFragment;
class UItemDefinition;

/**
 * 
 */
UCLASS(BlueprintType)
class ITEMDEFINITIONKIT_API UItemInstance : public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UItemDefinition> ItemDefinition;

	/// 使用GameplayTag来存储不同需求的属性值
	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag, float> ItemAttributes;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item Attributes", meta = (Categories = "Item.Attributes"))
	float GetAttributeValue(FGameplayTag AttributeTag);

	UFUNCTION(BlueprintCallable, Category = "Item Attributes", meta = (Categories = "Item.Attributes"))
	void SetAttributeValue(FGameplayTag AttributeTag, float AttributeValue);

	UFUNCTION(BlueprintCallable, Category = "Item Instance", meta = (AutoCreateRefTerm = "initAttributes"))
	void Initialize(TSubclassOf<UItemDefinition> ItemDef, const TMap<FGameplayTag, float>& InitAttributes);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DeterminesOutputType = "FragmentClass"), Category = "Fragments")
	const UItemFragment* FindFragmentByClass(const TSubclassOf<UItemFragment> FragmentClass);
};
