// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFragment.h"
#include "ItemFragment_StaticMesh.generated.h"

class UStaticMesh;
class UStaticMeshComponent;
class UMaterialInterface;

/**
 * 物品静态网格体与材质定义片段
 */
UCLASS()
class ITEMDEFINITIONKIT_API UItemFragment_StaticMesh : public UItemFragment {
	GENERATED_BODY()

public:
	/** 物品使用的静态网格体 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMesh> ItemMesh;

	/** 材质列表：选择网格体后会自动填充其默认材质，可在此处覆盖替换 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (DisplayName = "Materials", EditFixedSize))
	TArray<TObjectPtr<UMaterialInterface>> Materials;

	/** 将材质列表重置为网格体的默认材质 */
	UFUNCTION(CallInEditor, Category = "Mesh", meta = (DisplayName = "Reset Materials To Default"))
	void ResetMaterialsToDefault();

	/** 将网格体及材质配置应用到指定的 StaticMeshComponent */
	UFUNCTION(BlueprintCallable, Category = "Item|Mesh")
	void ApplyToComponent(UStaticMeshComponent* MeshComponent) const;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostLoad() override;

private:
	void UpdateMaterialsFromMesh();
	void SyncMaterialsSlotCount();

	TWeakObjectPtr<UStaticMesh> CachedMesh;
#endif
};
