// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFragment.h"
#include "Actions/ItemAction.h"
#include "ItemFragment_InteractUsable.generated.h"

/**
 * 
 */
UCLASS()
class ITEMDEFINITIONKIT_API UItemFragment_InteractUsable : public UItemFragment {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool InteractUse(AActor* ItemOwner, UItemInstance* ItemInstance);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "Actions")
	TArray<TObjectPtr<UItemAction>> OnUseActions;
};
