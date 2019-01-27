// Fill out your copyright notice in the Description page of Project Settings.

#include "BP_LaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ABP_LaunchPad::ABP_LaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = OverlapComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ABP_LaunchPad::OverlapLaunchPad);

	LaunchStrength = 1500;
	LaunchPitchAngle = 35.0f;

}

// Called when the game starts or when spawned
void ABP_LaunchPad::BeginPlay()
{
	Super::BeginPlay();

}

void ABP_LaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// 发射速度和方向
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch = LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter)
	{
		// Character自带的发射方法
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
		UGameplayStatics::PlaySound2D(this, LaunchSound);
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());
	}
}

