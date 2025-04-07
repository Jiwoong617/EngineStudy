#include "jwSceneManager.h"
#include "jwDontDestroyOnLoad.h"


namespace jw
{
	std::map<std::wstring, Scene*> SceneManager::mScene = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Scene* SceneManager::mDontDestroyOnLoad = nullptr;

	void SceneManager::Initialize()
	{
		mDontDestroyOnLoad = CreateScene<DontDestroyOnLoad>(L"DontDestroyOnLoad");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
		mDontDestroyOnLoad->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
		mDontDestroyOnLoad->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
		mDontDestroyOnLoad->Render(hdc);
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
		mDontDestroyOnLoad->Destroy();
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
		//이전 Scene Exit 함수 호출
		if (mActiveScene) mActiveScene->OnExit();

		auto find = mScene.find(name);
		if (find == mScene.end())
			return nullptr;

		mActiveScene = find->second;
		//현재 scene Enter함수 호출
		mActiveScene->OnEnter();

		return mActiveScene;
	}

	std::vector<GameObject*> SceneManager::GetGameObjects(eLayerType layer)
	{
		//DontDestroyOnLoad의 레이어와 현재 Scene의 레이어의 게임오브젝트들을 합쳐서 반환
		//충돌처리 하기위해
		std::vector<GameObject*> gameObjects = mActiveScene->GetLayer(layer)->GetGameObjects();
		std::vector<GameObject*> dontDestroyOnLoad = mDontDestroyOnLoad->GetLayer(layer)->GetGameObjects();

		gameObjects.insert(gameObjects.end(), dontDestroyOnLoad.begin(), dontDestroyOnLoad.end());

		return gameObjects;
	}
}