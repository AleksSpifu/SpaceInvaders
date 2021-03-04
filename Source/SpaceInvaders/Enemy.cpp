// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Skaffer først en referanse til sjefen
	GameManager = Cast<AGameManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGameManager::StaticClass()));

	// Og setter en tilfeldig verdi som start-verdi på hvor lenge det tar før de begynner å skyte.
	CoolDownBetweenShots = FMath::RandRange(2.f, 7.f);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;

	if (!GameManager->GameOver) {

		// Hele bevegelses-opplegget her er litt dust men jeg syns det var en morsom måte å gjøre ting på.
		// Jeg plusser på deltatime på Timer hele tiden, også bruker jeg modulo operatoren for å gjøre den om til
		// et tall mellom 0 og 3
		int Direction = (int)Timer % 4;

		// Deretter bruker jeg en TArray med vektorer i forskjellige retninger, og henter Array-posisjonen fra Direction over her.
		//På denne måten bytter de retning hvert sekund, fra en liste med retninger definert i header filen.

		AddActorLocalOffset(MoveDirections[Direction] * DeltaTime * MoveSpeed);

		// hvis fienden kommer seg helt til slutten av banen er det game over.
		if (GetActorLocation().X < -3775) {

			GameManager->GameOver = true;
		}

		// Her har tiden til de skal skyte gått, de skyter, også legger til en verdi til Cooldown sånn at de må vente litt før de kan skyte igjen.
		// For at spillet skal bli vanskeligere og vanskeligere får jeg et tall som er mellom antall bølger og antall bølger + 3,
		// Også fjerner jeg bølgen de er på.
		// Hvis det er 10 bølger, og de er på bølge 3, blir det et tall mellom 10 og 13, minus 3, så et tall mellom 7 og 10. 
		// Mens på runde 9 så blir det (10, 13) - 9 = 1, 4. Mellom 1 og 4 sekunder mellom hvert skudd.
		if (Timer > CoolDownBetweenShots) {
			Shoot();
			CoolDownBetweenShots += FMath::RandRange((float)GameManager->NumberOfWaves, (float)GameManager->NumberOfWaves + 3.f);
			CoolDownBetweenShots -= GameManager->CurrentWave;
		}

	}
}



void AEnemy::Shoot()
{

	// De skal ikke skyte hvis spilleren har tapt.
	if (!GameManager->GameOver) {
		if (Bullet) {

			// Det her er ganske lett å lese vil jeg tro. Grunnen til at jeg plusser på 180 grader i Z aksen er fordi jeg ikke roterer
			// Fiendene slik at de står "mot spilleren". Fram til jeg innså at de skulle skyte så virka ikke det nødvendig, og dette 
			// er en sånn "quick and dirty" fiks for det, men det holder nok her siden det ikke er så mye mer funksjonalitet som skal legges til.
			FRotator Rotation = GetActorRotation();
			Rotation.Yaw += 180.f;
			ABullet* BulletSpawned = GetWorld()->SpawnActor<ABullet>(Bullet, GetActorLocation() + SpawnOffset, Rotation);
			UE_LOG(LogTemp, Warning, TEXT("Bang!"));
			if (BulletSpawned) {
				BulletSpawned->bIsFromPlayer = false;
			}
		}
	}
}

void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	// Her også vil jeg tro det er ganske lett å lese. Hvis det er en kule så slett kula uansett, men fiendene skal kun dø hvis kula kom fra spilleren. 
	// Ligger et lite delay siden de ikke rekker å fortelle kula at den ikke kommer fra spilleren før de treffer eventuelle fiender foran seg selv. 
	if (OtherActor->IsA(ABullet::StaticClass())) {
		ABullet* bullet = Cast<ABullet>(OtherActor);
		OtherActor->Destroy();
		if (bullet->bIsFromPlayer && bullet->TimeAlive > .1f) {
			UE_LOG(LogTemp, Warning, TEXT("I'm Hit!"));

			// Fortell GameManager at det er færre fiender i live, slik at den vet når neste bølge skal komme. 
			GameManager->NumberOfEnemiesAlive--;
			UE_LOG(LogTemp, Warning, TEXT("Enemies left: %d"), GameManager->NumberOfEnemiesAlive);
			Destroy();

		}
	}

	// Hvis de treffer spilleren er det game over.
	else if (OtherActor->IsA(APlayerPawn::StaticClass())) {
		GameManager->GameOver = true;
	}
}

