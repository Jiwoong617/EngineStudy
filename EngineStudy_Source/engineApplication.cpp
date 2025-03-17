#include "engineApplication.h"
#include "jwInput.h"
#include "jwTime.h"

namespace jw
{
	Application::Application() 
		: mHwnd(nullptr)
		, mHdc(nullptr)
	{

	}
	Application::~Application()
	{
	}

	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);
		Input::Initialize();
		Time::Initialize();

		mPlayer.Setposition(0.0f, 0.0f);
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();

		mPlayer.Update();
	}

	void Application::LateUpdate()
	{
	}

	void Application::Render()
	{
		Time::Render(mHdc);

		mPlayer.Render(mHdc);
	}
}