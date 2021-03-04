// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "GameManager.h"
#include "Components/CapsuleComponent.h"
#include "Enemy.generated.h"

UCLASS()
class SPACEINVADERS_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float Timer{ 0.f };

	UPROPERTY(EditAnywhere)
		float MoveSpeed{ 100.f };

	class AGameManager* GameManager;

	TArray<FVector> MoveDirections{
		{ -1, 0, 0 },
		{ 0, 1, 0 },
		{ -1, 0, 0 },
		{ 0, -1, 0 }
	};

	float CoolDownBetweenShots{ 3.f };



	void Shoot();


	UPROPERTY(EditAnywhere)
		FVector SpawnOffset {
		-100.f, 0.f, 40.f
	};

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> Bullet;

	UFUNCTION(BlueprintCallable)
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
