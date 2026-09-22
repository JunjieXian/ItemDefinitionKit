// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFragment.h"
#include "ItemFragment_StaticMesh.generated.h"

/**
 * 
 */
UCLASS()
class ITEMDEFINITIONKIT_API UItemFragment_StaticMesh : public UItemFragment {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMesh> ItemMesh;
};
