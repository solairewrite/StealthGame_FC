// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS_Blackhole.generated.h"


class USphereComponent;

UCLASS()
class FPSGAME_API AFPS_Blackhole : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPS_Blackhole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	// 内部的球,摧毁进入物体
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* InnerSphereComponent;

	// 外部的球,吸引物体
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* OuterSphereComponent;

	// InnerSphereComponent->OnComponentBeginOverlap.AddDynamic
	// 点击查询绑定方法的参数
	UFUNCTION()
		void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
