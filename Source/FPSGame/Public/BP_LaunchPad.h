// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_LaunchPad.generated.h"


class UBoxComponent;

UCLASS()
class FPSGAME_API ABP_LaunchPad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABP_LaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* OverlapComp;

	UFUNCTION()
		void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchPitchAngle;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchPad")
		UParticleSystem* ActivateLaunchPadEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		USoundBase* LaunchSound;

};
