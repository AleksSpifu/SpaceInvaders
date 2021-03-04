// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bullet.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameManager.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SPACEINVADERS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float MoveSpeed{ 100.f };

	class AGameManager* GameManager;

	int TutorialStage{ 1 };

	void ToggleGodMode();

	void Restart();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	void MoveRight(float speed);

	void MoveUp(float speed);

	void Shoot();

	UPROPERTY(EditAnywhere)
	bool bGodMode{ false };

	UPROPERTY(EditAnywhere)
	FVector SpawnOffset{ 0.f };

	TArray<ABullet*> Bullets;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> Bullet;

	FVector CurrentDirection{ 0.f };

	bool ShotTaken{ false };

	float LastShotTaken{ 0.f };

	UPROPERTY(EditAnywhere)
	float CooldownBetweenShots{ 10.f };

};
