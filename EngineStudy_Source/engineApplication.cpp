#include "engineApplication.h"
#include "jwInput.h"
#include "jwTime.h"
#include "jwSceneManager.h"
#include "jwResources.h"

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
		SceneManager::Update();

	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		clearRenderTarget();

		Time::Render(mBackHdc);
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
		Resources::Release();
	}

	void Application::clearRenderTarget()
	{
		//����� Ŭ���� - ���
		//-1, +1�� �ϴ� ���� : �׵θ��� �߸� �� �ֱ� ������
		Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);
	}

	void Application::copyRenderTarget(HDC source, HDC dest)
	{
		//BackBuffer�� �ִ� ���� ���� ���ۿ� ����(�׸�)
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
		//������ �ػ󵵿� �´� ����� ����
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);
		//�� ���۸� ����ų dc ����
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);
	}

	void Application::initializeETC()
	{
		Input::Initialize();
		Time::Initialize();
		SceneManager::Initialize();
	}
}