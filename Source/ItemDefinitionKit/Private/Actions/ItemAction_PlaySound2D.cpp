// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ItemAction_PlaySound2D.h"

#include "ItemInstance.h"
#include "Kismet/GameplayStatics.h"

bool UItemAction_PlaySound2D::Execute_Implementation(AActor* ItemOwner, UItemInstance* ItemInstance) {
	UWorld* World = GetWorld();
	if (!World || !ItemOwner || !SoundToPlay) {
		return false;
	}

	UGameplayStatics::PlaySound2D(World, SoundToPlay, VolumeMultiplier, PitchMultiplier, StartTime);
	return true;
}
