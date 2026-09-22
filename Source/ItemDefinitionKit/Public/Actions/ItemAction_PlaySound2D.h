// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemAction.h"
#include "ItemAction_PlaySound2D.generated.h"

/**
 * 
 */
UCLASS()
class ITEMDEFINITIONKIT_API UItemAction_PlaySound2D : public UItemAction {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> SoundToPlay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	float VolumeMultiplier = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	float PitchMultiplier = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	float StartTime = 0;

	UFUNCTION
	()
	virtual bool Execute_Implementation(AActor* ItemOwner, UItemInstance* ItemInstance) override;
};
