#include "jwTime.h"


namespace jw
{
	LARGE_INTEGER Time::CpuFrequency = {};
	LARGE_INTEGER Time::PrevFrequency = {};
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;


	void Time::Initialize()
	{
		//Cpu 고유 진동수
		QueryPerformanceFrequency(&CpuFrequency);

		//프로그램이 시작했을 때 현재 진동수
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency);
		DeltaTimeValue = 
			static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart) 
			/ static_cast<float>(CpuFrequency.QuadPart);
		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		//static float time = 0.0f;
		//static float fps = 0.0f;

		//time += DeltaTimeValue;
		//fps = 1.0f / DeltaTimeValue;


		////time, fps 출력
		//wchar_t str[50] = L"";
		//wchar_t str2[50] = L"";
		//swprintf_s(str, 50, L"Time : %f", time);
		//swprintf_s(str2, 50, L"Fps : %f", fps);
		//int len = wcsnlen_s(str, 50);


		//TextOut(hdc, 0, 0, str, len);
		//TextOut(hdc, 0, 20, str2, len);
	}
}
