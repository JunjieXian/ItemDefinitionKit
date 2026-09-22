// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemFragment.generated.h"

class UItemInstance;

/**
 * Item属性配置的片段
 */
UCLASS(Blueprintable, BlueprintType, Abstract, DefaultToInstanced, EditInlineNew)
class ITEMDEFINITIONKIT_API UItemFragment : public UObject {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnInstanceCreated(UItemInstance* ItemInstance);
};

inline void UItemFragment::OnInstanceCreated_Implementation(UItemInstance* ItemInstance) {
}
