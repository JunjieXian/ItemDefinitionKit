// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/ItemAction.h"
#include "ItemAction_PlaySoundAtLocation.generated.h"

/**
 * 
 */
UCLASS()
class ITEMDEFINITIONKIT_API UItemAction_PlaySoundAtLocation : public UItemAction {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> SoundToPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	FVector SoundPlayLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	FRotator SoundPlayRotation = FRotator::ZeroRotator;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	float VolumeMultiplier = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	float PitchMultiplier = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	float StartTime = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	TObjectPtr<USoundAttenuation> SoundAttenuation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	TObjectPtr<USoundConcurrency> SoundConcurrency;

	UFUNCTION()
	virtual bool Execute_Implementation(AActor* ItemOwner, UItemInstance* ItemInstance) override;
};
