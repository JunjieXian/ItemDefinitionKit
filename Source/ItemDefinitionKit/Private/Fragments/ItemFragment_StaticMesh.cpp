// Fill out your copyright notice in the Description page of Project Settings.


#include "Fragments/ItemFragment_StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"

void UItemFragment_StaticMesh::ResetMaterialsToDefault()
{
#if WITH_EDITOR
	Modify();
	UpdateMaterialsFromMesh();
#endif
}

void UItemFragment_StaticMesh::ApplyToComponent(UStaticMeshComponent* MeshComponent) const
{
	if (!MeshComponent)
	{
		return;
	}

	MeshComponent->SetStaticMesh(ItemMesh);

	for (int32 Index = 0; Index < Materials.Num(); ++Index)
	{
		if (Materials[Index])
		{
			MeshComponent->SetMaterial(Index, Materials[Index]);
		}
	}
}

#if WITH_EDITOR
void UItemFragment_StaticMesh::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropName = PropertyChangedEvent.GetPropertyName();
	const FName MemberPropName = PropertyChangedEvent.GetMemberPropertyName();

	if (PropName == GET_MEMBER_NAME_CHECKED(UItemFragment_StaticMesh, ItemMesh) ||
		MemberPropName == GET_MEMBER_NAME_CHECKED(UItemFragment_StaticMesh, ItemMesh))
	{
		if (ItemMesh != CachedMesh.Get())
		{
			UpdateMaterialsFromMesh();
			CachedMesh = ItemMesh;
		}
		else if (ItemMesh && Materials.Num() != ItemMesh->GetStaticMaterials().Num())
		{
			SyncMaterialsSlotCount();
		}
	}
}

void UItemFragment_StaticMesh::PostLoad()
{
	Super::PostLoad();

	CachedMesh = ItemMesh;
	if (ItemMesh)
	{
		if (Materials.Num() == 0)
		{
			UpdateMaterialsFromMesh();
		}
		else if (Materials.Num() != ItemMesh->GetStaticMaterials().Num())
		{
			SyncMaterialsSlotCount();
		}
	}
}

void UItemFragment_StaticMesh::UpdateMaterialsFromMesh()
{
	Materials.Reset();
	if (ItemMesh)
	{
		const TArray<FStaticMaterial>& StaticMaterials = ItemMesh->GetStaticMaterials();
		Materials.Reserve(StaticMaterials.Num());
		for (const FStaticMaterial& StaticMaterial : StaticMaterials)
		{
			Materials.Add(StaticMaterial.MaterialInterface);
		}
	}
}

void UItemFragment_StaticMesh::SyncMaterialsSlotCount()
{
	if (!ItemMesh)
	{
		Materials.Reset();
		return;
	}

	const TArray<FStaticMaterial>& StaticMaterials = ItemMesh->GetStaticMaterials();
	const int32 OldNum = Materials.Num();
	const int32 NewNum = StaticMaterials.Num();

	Materials.SetNum(NewNum);
	for (int32 Index = OldNum; Index < NewNum; ++Index)
	{
		Materials[Index] = StaticMaterials[Index].MaterialInterface;
	}
}
#endif
