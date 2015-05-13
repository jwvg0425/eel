#pragma once
#include "base/macro.h"

NS_EEL_BEGIN

class Timer
{
public:
	Timer();
	~Timer() = default;

	float TotalTime() const;
	float DeltaTime() const;

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	double m_SecondsPerCount;
	double m_DeltaTime;

	long long int m_BaseTime;
	long long int m_PausedTime;
	long long int m_StopTime;
	long long int m_PrevTime;
	long long int m_CurrTime;

	bool m_Stopped;
};

NS_EEL_END