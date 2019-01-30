// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 *
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// 如果服务器运行函数,所有客户端都运行
	UFUNCTION(NetMulticast, Reliable)
		void MulticastOnMissionComplete(APawn* InstigatorPawn, bool bMissionSuccess);


};
