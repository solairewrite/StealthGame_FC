// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/FPS_Blackhole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AFPS_Blackhole::AFPS_Blackhole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComponent->SetSphereRadius(100);
	InnerSphereComponent->SetupAttachment(MeshComp);

	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPS_Blackhole::OverlapInnerSphere);
	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComponent->SetSphereRadius(30000); // 比场景还要大
	OuterSphereComponent->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void AFPS_Blackhole::BeginPlay()
{
	Super::BeginPlay();

}

void AFPS_Blackhole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void AFPS_Blackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 获取进入的物体
	TArray<UPrimitiveComponent*> OverlappingComps;
	OuterSphereComponent->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		// 查找所有 collide && simulate physics
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			const float SphereRadius = OuterSphereComponent->GetScaledSphereRadius();
			const float ForceStrength = -2000;
			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

