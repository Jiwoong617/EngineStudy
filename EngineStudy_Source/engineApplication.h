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

	private:
		void clearRenderTarget();
		void copyRenderTarget(HDC source, HDC dest);
		void adjustWindowRect(HWND hwnd, UINT width, UINT height);
		void createBuffer(UINT width, UINT height);
		void initializeETC();

	private:
		//메인 hwnd
		HWND mHwnd;
		HDC mHdc;

		//백버퍼
		HDC mBackHdc;
		HBITMAP mBackBitmap;

		//화면 크기
		UINT mWidth;
		UINT mHeight;

		//std::vector<GameObject*> mGameObjects;
	};
}