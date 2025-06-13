// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("★★★★★ GAME START ★★★★★"));
    Move();
	UE_LOG(LogTemp, Warning, TEXT("★★★★★ GAME OVER ★★★★★"));
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMyActor::Distance(FVector3d first, FVector3d second, FVector3d third)
{
	float dx = first.X - second.X;
	float dy = first.Y - second.Y;
	return FMath::Sqrt(dx * dx + dy * dy);
}

void AMyActor::Move()
{
    TArray<FVector3d> VectorArray; // FVector3d 배열 생성

    int32 TotalDistance = 0;    // 총 이동거리
    int32 CntEvent = 0;         // 총 이벤트 발생 횟수

    // 시작점
    VectorArray.Add(FVector3d(0.0f, 0.0f, 0.0f));
    UE_LOG(LogTemp, Warning, TEXT("시작점: (X:%d, Y:%d)"), static_cast<int32>(VectorArray[0].X), static_cast<int32>(VectorArray[0].Y));

    // 10회 이동
    for (int32 i = 1; i < 11; i++)
    {
        int32 BeforeX = VectorArray[i - 1].X;
        int32 BeforeY = VectorArray[i - 1].Y;
        VectorArray.Add(FVector3d(BeforeX + Step(), BeforeY + Step(), 0.0f)); // X, Y 값을 임의로 설정
    }

    // 데이터 출력
    for (int32 i = 1; i < VectorArray.Num(); i++)
    {
        //이전 좌표기준 이동 거리를 계산하기 위한 준비
        const FVector3d& Vec = VectorArray[i];
        const FVector3d& BeforeVec = VectorArray[i-1];

        int32 Length = static_cast<int32>(Distance(Vec, BeforeVec));
        TotalDistance += Length;
     
        UE_LOG(LogTemp, Warning, TEXT("Move[%02d회]======================================="), i);
        CreateEvent(CntEvent);
        UE_LOG(LogTemp, Log, TEXT("Total Distance:%d | Now Distance:%d | (X:%d, Y:%d)"), TotalDistance, Length, static_cast<int32>(Vec.X), static_cast<int32>(Vec.Y));
    }

    UE_LOG(LogTemp, Error, TEXT("[이동 10회 완료] 총 이동거리: %d, 총 이벤트 발생횟수: %d"), TotalDistance, CntEvent);
}

int32 AMyActor::Step()
{// 랜덤: 0 혹은 1
    return FMath::RandRange(0, 1);
}

void AMyActor::CreateEvent(int32& CntEvent)
{// 50% 확률로 랜덤하게 이벤트가 발생

    if (FMath::RandRange(0, 1) == 1)
    {
        UE_LOG(LogTemp, Error, TEXT("이벤트 발생 회차: %d"), ++CntEvent);
    }
}
