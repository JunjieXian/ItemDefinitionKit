// Fill out your copyright notice in the Description page of Project Settings.


#include "Fragments/ItemFragment_InteractUsable.h"

/// 根据需要修改，默认是只要有一个Action被执行成功了，就会返回true
bool UItemFragment_InteractUsable::InteractUse(AActor* ItemOwner, UItemInstance* ItemInstance) {
	bool bAnySucceeded = false;

	for (const TObjectPtr<UItemAction>& Action : OnUseActions) {
		if (Action && Action->Execute(ItemOwner, ItemInstance)) {
			bAnySucceeded = true;
		}
	}

	return bAnySucceeded;
}
