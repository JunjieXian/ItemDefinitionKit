// Fill out your copyright notice in the Description page of Project Settings.


#include "Fragments/ItemFragment_SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Materials/MaterialInterface.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimationAsset.h"

void UItemFragment_SkeletalMesh::ResetMaterialsToDefault()
{
#if WITH_EDITOR
	Modify();
	UpdateMaterialsFromMesh();
#endif
}

void UItemFragment_SkeletalMesh::ApplyToComponent(USkeletalMeshComponent* MeshComponent) const
{
	if (!MeshComponent)
	{
		return;
	}

	MeshComponent->SetSkeletalMesh(ItemSkeletalMesh);

	for (int32 Index = 0; Index < Materials.Num(); ++Index)
	{
		if (Materials[Index])
		{
			MeshComponent->SetMaterial(Index, Materials[Index]);
		}
	}

	MeshComponent->SetAnimationMode(AnimationMode);
	if (AnimationMode == EAnimationMode::AnimationBlueprint)
	{
		MeshComponent->SetAnimInstanceClass(AnimInstanceClass);
	}
	else if (AnimationMode == EAnimationMode::AnimationSingleNode)
	{
		if (AnimationAsset)
		{
			MeshComponent->SetAnimation(AnimationAsset);
			MeshComponent->Play(true);
		}
	}
}

#if WITH_EDITOR
void UItemFragment_SkeletalMesh::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropName = PropertyChangedEvent.GetPropertyName();
	const FName MemberPropName = PropertyChangedEvent.GetMemberPropertyName();

	if (PropName == GET_MEMBER_NAME_CHECKED(UItemFragment_SkeletalMesh, ItemSkeletalMesh) ||
		MemberPropName == GET_MEMBER_NAME_CHECKED(UItemFragment_SkeletalMesh, ItemSkeletalMesh))
	{
		if (ItemSkeletalMesh != CachedMesh.Get())
		{
			UpdateMaterialsFromMesh();
			CachedMesh = ItemSkeletalMesh;
		}
		else if (ItemSkeletalMesh && Materials.Num() != ItemSkeletalMesh->GetMaterials().Num())
		{
			SyncMaterialsSlotCount();
		}
	}
}

void UItemFragment_SkeletalMesh::PostLoad()
{
	Super::PostLoad();

	CachedMesh = ItemSkeletalMesh;
	if (ItemSkeletalMesh)
	{
		if (Materials.Num() == 0)
		{
			UpdateMaterialsFromMesh();
		}
		else if (Materials.Num() != ItemSkeletalMesh->GetMaterials().Num())
		{
			SyncMaterialsSlotCount();
		}
	}
}

void UItemFragment_SkeletalMesh::UpdateMaterialsFromMesh()
{
	Materials.Reset();
	if (ItemSkeletalMesh)
	{
		const TArray<FSkeletalMaterial>& SkeletalMaterials = ItemSkeletalMesh->GetMaterials();
		Materials.Reserve(SkeletalMaterials.Num());
		for (const FSkeletalMaterial& SkeletalMaterial : SkeletalMaterials)
		{
			Materials.Add(SkeletalMaterial.MaterialInterface);
		}
	}
}

void UItemFragment_SkeletalMesh::SyncMaterialsSlotCount()
{
	if (!ItemSkeletalMesh)
	{
		Materials.Reset();
		return;
	}

	const TArray<FSkeletalMaterial>& SkeletalMaterials = ItemSkeletalMesh->GetMaterials();
	const int32 OldNum = Materials.Num();
	const int32 NewNum = SkeletalMaterials.Num();

	Materials.SetNum(NewNum);
	for (int32 Index = OldNum; Index < NewNum; ++Index)
	{
		Materials[Index] = SkeletalMaterials[Index].MaterialInterface;
	}
}
#endif
