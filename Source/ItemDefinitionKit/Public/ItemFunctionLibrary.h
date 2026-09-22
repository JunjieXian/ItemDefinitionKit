// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInstance.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ITEMDEFINITIONKIT_API UItemFunctionLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Item Blueprint Function Library", meta = (DefaultToSelf = "Outer", AutoCreateRefTerm = "InitAttributes"))
	static UItemInstance* ConstructItemInstanceInitialize(TSubclassOf<UItemDefinition> ItemDefinition, const TMap<FGameplayTag, float>& InitAttributes, UObject* Outer);
};
