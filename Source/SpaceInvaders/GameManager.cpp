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

	// Starter hvertfall med å spawne spilleren.
	if (PlayerBP) {
		Player = GetWorld()->SpawnActor<APlayerPawn>(PlayerBP, PlayerSpawnLocation, GetActorRotation());
	}
	

	NumberOfEnemiesAlive = 0;

}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	// Her også har jeg en Timer for å følge med på hvor lang tid det har gått. Det er kun for å stoppe spilleren fra å spamme Restart.
	Timer += DeltaTime;

	// Det er først en tutorial, og først når den er ferdig kan spillet starte.
	if (TutorialFinished) {
		
		if (bSpawnWave) {
			SpawnWave();
			bSpawnWave = false;
		}

		// Hvis alle er døde og det er flere bølger igjen, kjør neste bølge.
		if (NumberOfEnemiesAlive == 0 && CurrentWave <= NumberOfWaves) {
			CurrentWave++;
			if (NumberOfWaves >= CurrentWave) {
				bSpawnWave = true;
			}
		} 
		// OutputHUD er på venstresiden av skjermen, og viser vanligvis hvilken bølge man er på, men viser også 
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
		// Denne vil sørge for at uansett hvor mange steg det er i tutorial Arrayen vil den gå gjennom alle, også si at den er ferdig.
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
	// Jeg skal prøve å forklare det så godt jeg kan.

	// Starter hvertfall med å fjerne alle kulene som er på banen.
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
	// Slik at det blir fler og fler hver bølge.
	NumberOfEnemiesLeftToSpawn = NumberOfEnemiesInFirstWave;
	if (CurrentWave > 1) {
		NumberOfEnemiesLeftToSpawn += CurrentWave * DifficultyIncreasePerWave;
	}

	// Fant ut at rundt 200 var det det var plass til, så alt over det blir kutta til 200.
	if (NumberOfEnemiesLeftToSpawn > 200) {
		NumberOfEnemiesLeftToSpawn = 200;
	}

	// Av en eller annen grunn er ikke kartet mitt i midten, så jeg bare lagde en vektor med ca hvor midten er.
	FVector SpawnLocation = CentreOfMap;

	// Fant ut at 20 per rad holdt, så jeg deler fiendene på 20 og kutter av desimaltallet for å finne hvor mange
	// fulle rader det er. 
	int FullRows{ NumberOfEnemiesLeftToSpawn / 20 };
	
	// Hvis det er noen fulle rader, gjør jeg om NumberOfEnemiesLeftToSpawn til det som blir til overs ved hjelp av modulo operatoren.
	if (FullRows > 0) {
		NumberOfEnemiesLeftToSpawn = NumberOfEnemiesLeftToSpawn % 20;
	}

	// Hvis det er noen fulle rader, så kan vi bare spawne hele raden uten å tenke så mye på plasseringen. 
	// Denne går rad for rad, og spawner 20 fiender hver rad, også flytter seg 1,5 meter bakover for neste rad.
	for (int i = 0; i < FullRows; i++) {
		for (int j = 0; j < 20; j++) {
			SpawnLocation.Y = -1425 + (150 * j);
			GetWorld()->SpawnActor<AEnemy>(EnemyBP, SpawnLocation, GetActorRotation());
			NumberOfEnemiesAlive++;
		}
		SpawnLocation.X += 150;
	}

	// Når den er ferdig (Eller hvis det var under 20 fiender) Kommer den hit, og den beste måten jeg kan beskrive det på er at den
	// Starter på midten, også finner den ut hvor mye plass hele raden vil ta, også går den halvparten av det til venstre.
	// Så spawner den 1, og flytter seg mot høyre. På denne måten blir de alltid sentrert uansett hvor mange det er. 

	for (int i = 0; i < NumberOfEnemiesLeftToSpawn; i++) {
		SpawnLocation.Y = (0 - ((150 * NumberOfEnemiesLeftToSpawn) / 2) + 75) + (150 * i);
		GetWorld()->SpawnActor<AEnemy>(EnemyBP, SpawnLocation, GetActorRotation());
		NumberOfEnemiesAlive++;
	}


}

void AGameManager::Restart()
{
	// Denne bare nullstiller alt, sletter alle fiender og kuler, setter ned currentwave, nullstiller Timeren og 
	// Hvis spillet ble tapt så bytter den tilbake game over til false.
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

