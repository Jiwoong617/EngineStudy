#include "jwSceneManager.h"


namespace jw
{
	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (auto& iter : mScene)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		//���� Scene Exit �Լ� ȣ��
		if (mActiveScene) mActiveScene->OnExit();

		auto find = mScene.find(name);
		if (find == mScene.end())
			return nullptr;

		mActiveScene = find->second;
		//���� scene Enter�Լ� ȣ��
		mActiveScene->OnEnter();

		return mActiveScene;
	}
}