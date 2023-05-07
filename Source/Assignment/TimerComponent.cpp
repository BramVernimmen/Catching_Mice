// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerComponent.h"

// Sets default values for this component's properties
UTimerComponent::UTimerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MaxTime = 100.0f; // This will be changable in blueprints, just a base value...
	m_CurrentTime = MaxTime; // Start at MaxTime
}


// Called when the game starts
void UTimerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTimerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTimerComponent::ResetTimer()
{
	m_CurrentTime = MaxTime;
}

void UTimerComponent::ChangeActiveState()
{
	m_IsActive = !m_IsActive;
}

float UTimerComponent::GetTimeLeftPercentage() const
{
	return m_CurrentTime / MaxTime;
}

bool UTimerComponent::IsTimeUp() const
{
	if (GetTimeLeftPercentage() <= 0.0f)
		return true;

	return false;
}

void UTimerComponent::AddTime(float deltaTime)
{
	m_CurrentTime += deltaTime;
	// add time, make sure we don't exceed MaxTime
	if (m_CurrentTime >= MaxTime)
		m_CurrentTime = MaxTime;

}

// is BlueprintNativeEvent, we need to write _Implementation after it
void UTimerComponent::DoCountDown_Implementation(float deltaTime, bool& isTimeUp)
{
	// check if Timer is actually active
	if (m_IsActive == false)
		return;

	float orignalTime = m_CurrentTime;

	// remove time, make sure we don't go below 0
	m_CurrentTime -= deltaTime;
	m_CurrentTime = FMath::Clamp(m_CurrentTime, 0.0f, MaxTime);

	isTimeUp = IsTimeUp();

	if (isTimeUp && orignalTime > m_CurrentTime)
	{
		// call Event
		OnTimeIsUp.Broadcast();
	}
}

