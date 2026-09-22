// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ItemAction_PlaySoundAtLocation.h"

#include "Kismet/GameplayStatics.h"

bool UItemAction_PlaySoundAtLocation::Execute_Implementation(AActor* ItemOwner, UItemInstance* ItemInstance) {
	UWorld* World = GetWorld();
	if (!World || !ItemOwner || !SoundToPlay) {
		return false;
	}
	UGameplayStatics::PlaySoundAtLocation(World, SoundToPlay, SoundPlayLocation, SoundPlayRotation,
	                                      VolumeMultiplier, PitchMultiplier, StartTime, SoundAttenuation, SoundConcurrency);
	return true;
}
