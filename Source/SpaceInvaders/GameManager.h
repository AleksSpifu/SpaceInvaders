// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerPawn.h"
#include "Enemy.h"
#include "GameManager.generated.h"

UCLASS()
class SPACEINVADERS_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class APlayerPawn* Player;

	// Om den har fått beskjed om å spawne neste bølge eller ikke.
	bool bSpawnWave{ false };

	void SpawnWave();

	float Timer{ 0.f };

	UPROPERTY(EditAnywhere)
	int NumberOfWaves{ 1 };

	// Dette er den som viser hvilken bølge spilleren er på.
	UPROPERTY(BlueprintReadWrite)
	FString OutputHUD{""};

	bool TutorialFinished{ false };

	// Og dette er den som viser alle de under her når man starter spillet.
	UPROPERTY(BlueprintReadWrite)
	FString TutorialHUD { "Tutorial!" };

	TArray<FString> Tutorials{
		"Use WASD to move around.",
		"Press Space to shoot.",
		"Press G to toggle God Mode.",
		"Now try to shoot again!",
		"Now turn it off again, it's cheating!",
		"Try to shoot while moving sideways.",
		"Okay, now you are ready. Press Space to start."
	};

	void Restart();

	int CurrentWave{ 0 };

	bool GameOver{ false };


	UPROPERTY(EditAnywhere)
	int NumberOfEnemiesInFirstWave{ 5 };

	int NumberOfEnemiesLeftToSpawn{ 0 };

	int NumberOfEnemiesAlive{ 0 };

	UPROPERTY(EditAnywhere)
	float DifficultyIncreasePerWave{ 1.f };

	FVector CentreOfMap {-2300, 0, 20};

	
	FVector PlayerSpawnLocation{ -3100, 0, 20 };

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerPawn> PlayerBP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemy> EnemyBP;

};
