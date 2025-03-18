#pragma once
#include "jwScene.h"

namespace jw
{
	class SceneManager
	{
	public:
		template <typename T>
		static Scene* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			scene->Initialize();

			mScene.insert(std::make_pair(name, scene));
			return scene;
		}
		static Scene* LoadScene(const std::wstring& name)
		{
			auto find = mScene.find(name);
			if (find == mScene.end())
				return nullptr;

			mActiveScene = find->second;
			return mActiveScene;
		}

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

	private :
		static std::map<std::wstring, Scene*> mScene;
		static Scene* mActiveScene;
	};
}


