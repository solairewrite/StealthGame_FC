// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/FPSGameState.h"

// 注意_Implementation
void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		APawn* Pawn = It->Get();
		if (Pawn && Pawn->IsLocallyControlled())
		{
			Pawn->DisableInput(nullptr);
		}
	}
}
