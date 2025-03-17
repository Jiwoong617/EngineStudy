#include "engineApplication.h"
#include "jwInput.h"
#include "jwTime.h"

namespace jw
{
	Application::Application() 
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mBackHdc(NULL)
		, mBackBitmap(NULL)
	{

	}
	Application::~Application()
	{
	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0,0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(mHwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(mHwnd, true);

		//윈도우 해상도에 맞는 백버퍼 생성
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);
		//백 버퍼를 가르킬 dc 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);

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
		//백버퍼 클리어 - 흰색
		Rectangle(mBackHdc, 0, 0, mWidth, mHeight);

		Time::Render(mBackHdc);
		mPlayer.Render(mBackHdc);

		//BackBuffer에 있는 것을 원본 버퍼에 복사(그림)
		BitBlt(mHdc, 0, 0, mWidth, mHeight,
			mBackHdc, 0, 0, SRCCOPY);
	}
}