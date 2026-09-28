// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFragment.h"
#include "ItemFragment_SkeletalMesh.generated.h"

class USkeletalMesh;
class USkeletalMeshComponent;
class UAnimInstance;
class UAnimationAsset;
class UMaterialInterface;

/**
 * 物品骨骼网格体与材质定义片段
 */
UCLASS()
class ITEMDEFINITIONKIT_API UItemFragment_SkeletalMesh : public UItemFragment {
	GENERATED_BODY()

public:
	/** 物品使用的骨骼网格体 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkelMesh")
	TObjectPtr<USkeletalMesh> ItemSkeletalMesh;

	/** 材质列表：选择网格体后会自动填充其默认材质，可在此处覆盖替换 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkelMesh", meta = (DisplayName = "Materials", EditFixedSize))
	TArray<TObjectPtr<UMaterialInterface>> Materials;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim Options")
	TEnumAsByte<EAnimationMode::Type> AnimationMode = EAnimationMode::AnimationBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim Options",
		meta = (EditCondition = "AnimationMode == EAnimationMode::AnimationBlueprint", EditConditionHides))
	TSubclassOf<UAnimInstance> AnimInstanceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim Options",
		meta = (EditCondition = "AnimationMode == EAnimationMode::AnimationSingleNode", EditConditionHides))
	TObjectPtr<UAnimationAsset> AnimationAsset;

	/** 将材质列表重置为网格体的默认材质 */
	UFUNCTION(CallInEditor, Category = "SkelMesh", meta = (DisplayName = "Reset Materials To Default"))
	void ResetMaterialsToDefault();

	/** 将骨骼网格体、材质及动画配置应用到指定的 SkeletalMeshComponent */
	UFUNCTION(BlueprintCallable, Category = "Item|SkelMesh")
	void ApplyToComponent(USkeletalMeshComponent* MeshComponent) const;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostLoad() override;

private:
	void UpdateMaterialsFromMesh();
	void SyncMaterialsSlotCount();

	TWeakObjectPtr<USkeletalMesh> CachedMesh;
#endif
};
