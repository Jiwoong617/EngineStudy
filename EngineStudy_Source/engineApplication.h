#pragma once
#include "CommonInclude.h"
#include "jwGameObject.h"

namespace jw
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd, UINT width, UINT height);
		void Run();

		void Update();
		void LateUpdate();
		void Render();
		void Destroy();
		void Release();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		void clearRenderTarget();
		void copyRenderTarget(HDC source, HDC dest);
		void adjustWindowRect(HWND hwnd, UINT width, UINT height);
		void createBuffer(UINT width, UINT height);
		void initializeETC();

	private:
		//���� hwnd
		HWND mHwnd;
		HDC mHdc;

		//�����
		HDC mBackHdc;
		HBITMAP mBackBitmap;

		//ȭ�� ũ��
		UINT mWidth;
		UINT mHeight;

		//std::vector<GameObject*> mGameObjects;
	};
}