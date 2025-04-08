#include "engineApplication.h"
#include "jwInput.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwResources.h"
#include "jwCollisionManager.h"
#include "jwUIManager.h"
#include "jwFmod.h"

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
		adjustWindowRect(hwnd, width, height);
		createBuffer(width, height);
		initializeETC();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
		Destroy();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();

		CollisionManager::Update();
		UIManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		CollisionManager::LateUpdate();
		UIManager::LateUpdate();
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		clearRenderTarget();

		Time::Render(mBackHdc);
		CollisionManager::Render(mBackHdc);
		UIManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);

		copyRenderTarget(mBackHdc, mHdc);
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Release()
	{
		SceneManager::Release();
		UIManager::Release();
		Resources::Release();
	}

	void Application::clearRenderTarget()
	{
		//백버퍼 클리어 - 회색 (이유 : 문제가 생겨 흰색 배경에 흰색이 있으면 안보임)
		HBRUSH grayBrush = (HBRUSH)CreateSolidBrush(RGB(128, 128, 128));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);

		//-1, +1을 하는 이유 : 테두리가 잘릴 수 있기 때문에
		Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);

		(HBRUSH)SelectObject(mBackHdc, oldBrush);
		DeleteObject(grayBrush);
	}

	void Application::copyRenderTarget(HDC source, HDC dest)
	{
		//BackBuffer에 있는 것을 원본 버퍼에 복사(그림)
		BitBlt(dest, 0, 0, mWidth, mHeight, source, 0, 0, SRCCOPY);
	}

	void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0,0, width, height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(mHwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(mHwnd, true);
	}

	void Application::createBuffer(UINT width, UINT height)
	{
		//윈도우 해상도에 맞는 백버퍼 생성
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);
		//백 버퍼를 가르킬 dc 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);
	}

	void Application::initializeETC()
	{
		Input::Initialize();
		Time::Initialize();

		Fmod::Initialize();
		CollisionManager::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();
	}
}