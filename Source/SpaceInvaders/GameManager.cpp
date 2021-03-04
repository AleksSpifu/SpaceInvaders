// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerBP) {
		Player = GetWorld()->SpawnActor<APlayerPawn>(PlayerBP, PlayerSpawnLocation, GetActorRotation());
	}
	
	NumberOfEnemiesAlive = 0;
	UE_LOG(LogTemp, Warning, TEXT(" nrAlive: %d"), NumberOfEnemiesAlive);

	UE_LOG(LogTemp, Warning, TEXT("%d, %d, %d, %d, %d, %d"), rand(), rand(), rand(), rand(), rand(), rand());
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	Timer += DeltaTime;
	if (TutorialFinished) {

		if (bSpawnWave) {
			SpawnWave();
			bSpawnWave = false;
		}
		if (NumberOfEnemiesAlive == 0 && CurrentWave <= NumberOfWaves) {
			CurrentWave++;
			if (NumberOfWaves >= CurrentWave) {
				bSpawnWave = true;
			}
		}
		if (CurrentWave > NumberOfWaves) {
			OutputHUD = "Congrats! You won! :D You can press Enter to restart.";
		}
		else if (CurrentWave <= NumberOfWaves && GameOver) {
			OutputHUD = "You lost! Press Enter to restart :)";
		}
		else {
			OutputHUD = "Wave: ";
			OutputHUD += OutputHUD.FromInt(CurrentWave);
		}
	}
	else {
		if (Player && Player->TutorialStage <= Tutorials.Num()) {
			TutorialHUD = Tutorials[Player->TutorialStage - 1];
		}
		else {
			TutorialFinished = true;
			TutorialHUD = "";
		}
	}

}

void AGameManager::SpawnWave()
{
	TArray<AActor*> Bullets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABullet::StaticClass(), Bullets);
	if (Bullets.Num() > 0) {
		TArray<ABullet*> Bullets1;
		for (AActor* Bullet : Bullets) {
			Bullets1.Add(Cast<ABullet>(Bullet));
		}
		for (ABullet* Bullet : Bullets1) {
			Bullet->Destroy();
		}
	}

	NumberOfEnemiesLeftToSpawn = NumberOfEnemiesInFirstWave;
	if (CurrentWave > 1) {
		NumberOfEnemiesLeftToSpawn += CurrentWave * DifficultyIncreasePerWave;
	}

	if (NumberOfEnemiesLeftToSpawn > 200) {
		NumberOfEnemiesLeftToSpawn = 200;
	}

	FVector SpawnLocation = CentreOfMap;
	int FullRows{ NumberOfEnemiesLeftToSpawn / 20 };
	
	if (FullRows > 0) {
		NumberOfEnemiesLeftToSpawn = NumberOfEnemiesLeftToSpawn % 20;
	}

	for (int i = 0; i < FullRows; i++) {
		for (int j = 0; j < 20; j++) {
			SpawnLocation.Y = -1425 + (150 * j);
			GetWorld()->SpawnActor<AEnemy>(EnemyBP, SpawnLocation, GetActorRotation());
			NumberOfEnemiesAlive++;
		}
		SpawnLocation.X += 150;
	}

	for (int i = 0; i < NumberOfEnemiesLeftToSpawn; i++) {
		SpawnLocation.Y = (0 - ((150 * NumberOfEnemiesLeftToSpawn) / 2) + 75) + (150 * i);
		GetWorld()->SpawnActor<AEnemy>(EnemyBP, SpawnLocation, GetActorRotation());
		NumberOfEnemiesAlive++;
	}

	/*for (AEnemy* enemy : Enemies) {
		enemy->SetGameManager(this);
	}*/
}

void AGameManager::Restart()
{
	if (Timer > 1.f) {
		UE_LOG(LogTemp, Warning, TEXT("Restart!"));
		TArray<AActor*> Enemies{};
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), Enemies);
		if (Enemies.Num() > 0) {
			TArray<AEnemy*> Enemies1;
			for (AActor* Enemy : Enemies) {
				Enemies1.Add(Cast<AEnemy>(Enemy));
			}
			for (AEnemy* Enemy : Enemies1) {
				Enemy->Destroy();
				NumberOfEnemiesAlive--;
			}
		}

		TArray<AActor*> Bullets;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABullet::StaticClass(), Bullets);
		if (Bullets.Num() > 0) {
			TArray<ABullet*> Bullets1;
			for (AActor* Bullet : Bullets) {
				Bullets1.Add(Cast<ABullet>(Bullet));
			}
			for (ABullet* Bullet : Bullets1) {
				Bullet->Destroy();
			}
		}

		Player->SetActorLocation(PlayerSpawnLocation);
		CurrentWave = 0;
		GameOver = false;
		Timer = 0.f;

	}
	
	
}

