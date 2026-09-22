// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFragment.h"
#include "ItemFragment_SkeletalMesh.generated.h"

/**
 * 
 */
UCLASS()
class ITEMDEFINITIONKIT_API UItemFragment_SkeletalMesh : public UItemFragment {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkelMesh")
	TObjectPtr<USkeletalMesh> ItemSkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim Options")
	TEnumAsByte<EAnimationMode::Type> AnimationMode = EAnimationMode::AnimationBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim Options",
		meta = (EditCondition = "AnimationMode == EAnimationMode::AnimationBlueprint", EditConditionHides))
	TSubclassOf<UAnimInstance> AnimInstanceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim Options",
		meta = (EditCondition = "AnimationMode == EAnimationMode::AnimationSingleNode", EditConditionHides))
	TObjectPtr<UAnimationAsset> AnimationAsset;
};
