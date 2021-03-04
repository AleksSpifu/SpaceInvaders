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

	// Starter hvertfall med � spawne spilleren.
	if (PlayerBP) {
		Player = GetWorld()->SpawnActor<APlayerPawn>(PlayerBP, PlayerSpawnLocation, GetActorRotation());
	}
	

	NumberOfEnemiesAlive = 0;

}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	// Her ogs� har jeg en Timer for � f�lge med p� hvor lang tid det har g�tt. Det er kun for � stoppe spilleren fra � spamme Restart.
	Timer += DeltaTime;

	// Det er f�rst en tutorial, og f�rst n�r den er ferdig kan spillet starte.
	if (TutorialFinished) {
		
		if (bSpawnWave) {
			SpawnWave();
			bSpawnWave = false;
		}

		// Hvis alle er d�de og det er flere b�lger igjen, kj�r neste b�lge.
		if (NumberOfEnemiesAlive == 0 && CurrentWave <= NumberOfWaves) {
			CurrentWave++;
			if (NumberOfWaves >= CurrentWave) {
				bSpawnWave = true;
			}
		} 
		// OutputHUD er p� venstresiden av skjermen, og viser vanligvis hvilken b�lge man er p�, men viser ogs� 
		// Om man vinner eller taper.
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
		// Denne vil s�rge for at uansett hvor mange steg det er i tutorial Arrayen vil den g� gjennom alle, ogs� si at den er ferdig.
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
	// Dette her ser helt forferdelig ut og jeg skammer meg, men det funker i hvertfall.
	// Jeg skal pr�ve � forklare det s� godt jeg kan.

	// Starter hvertfall med � fjerne alle kulene som er p� banen.
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

	// Deretter legger jeg inn hvor mange fiender som skal spawnes, og ganger med vanskelighetsgraden som kan stilles inn i editoren, 
	// Slik at det blir fler og fler hver b�lge.
	NumberOfEnemiesLeftToSpawn = NumberOfEnemiesInFirstWave;
	if (CurrentWave > 1) {
		NumberOfEnemiesLeftToSpawn += CurrentWave * DifficultyIncreasePerWave;
	}

	// Fant ut at rundt 200 var det det var plass til, s� alt over det blir kutta til 200.
	if (NumberOfEnemiesLeftToSpawn > 200) {
		NumberOfEnemiesLeftToSpawn = 200;
	}

	// Av en eller annen grunn er ikke kartet mitt i midten, s� jeg bare lagde en vektor med ca hvor midten er.
	FVector SpawnLocation = CentreOfMap;

	// Fant ut at 20 per rad holdt, s� jeg deler fiendene p� 20 og kutter av desimaltallet for � finne hvor mange
	// fulle rader det er. 
	int FullRows{ NumberOfEnemiesLeftToSpawn / 20 };
	
	// Hvis det er noen fulle rader, gj�r jeg om NumberOfEnemiesLeftToSpawn til det som blir til overs ved hjelp av modulo operatoren.
	if (FullRows > 0) {
		NumberOfEnemiesLeftToSpawn = NumberOfEnemiesLeftToSpawn % 20;
	}

	// Hvis det er noen fulle rader, s� kan vi bare spawne hele raden uten � tenke s� mye p� plasseringen. 
	// Denne g�r rad for rad, og spawner 20 fiender hver rad, ogs� flytter seg 1,5 meter bakover for neste rad.
	for (int i = 0; i < FullRows; i++) {
		for (int j = 0; j < 20; j++) {
			SpawnLocation.Y = -1425 + (150 * j);
			GetWorld()->SpawnActor<AEnemy>(EnemyBP, SpawnLocation, GetActorRotation());
			NumberOfEnemiesAlive++;
		}
		SpawnLocation.X += 150;
	}

	// N�r den er ferdig (Eller hvis det var under 20 fiender) Kommer den hit, og den beste m�ten jeg kan beskrive det p� er at den
	// Starter p� midten, ogs� finner den ut hvor mye plass hele raden vil ta, ogs� g�r den halvparten av det til venstre.
	// S� spawner den 1, og flytter seg mot h�yre. P� denne m�ten blir de alltid sentrert uansett hvor mange det er. 

	for (int i = 0; i < NumberOfEnemiesLeftToSpawn; i++) {
		SpawnLocation.Y = (0 - ((150 * NumberOfEnemiesLeftToSpawn) / 2) + 75) + (150 * i);
		GetWorld()->SpawnActor<AEnemy>(EnemyBP, SpawnLocation, GetActorRotation());
		NumberOfEnemiesAlive++;
	}


}

void AGameManager::Restart()
{
	// Denne bare nullstiller alt, sletter alle fiender og kuler, setter ned currentwave, nullstiller Timeren og 
	// Hvis spillet ble tapt s� bytter den tilbake game over til false.
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

