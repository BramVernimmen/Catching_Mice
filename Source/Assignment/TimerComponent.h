// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, IsBlueprintBase = "true") )
class ASSIGNMENT_API UTimerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float MaxTime;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float m_CurrentTime;
	bool m_IsActive{true};

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Time")
	void ResetTimer();

	UFUNCTION(BlueprintCallable, Category = "Time")
	void ChangeActiveState();

	UFUNCTION(BlueprintCallable, Category = "Time")
	float GetTimeLeftPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Time")
	bool IsTimeUp() const;

	UFUNCTION(BlueprintCallable, Category = "Time")
	void AddTime(float deltaTime);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Time")
	void DoCountDown(float deltaTime, bool& isTimeUp);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeIsUpSignature);
	UPROPERTY(BlueprintAssignable, Category = "Time")
	FOnTimeIsUpSignature OnTimeIsUp;
};
