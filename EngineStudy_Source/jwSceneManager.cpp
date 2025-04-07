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

	std::vector<GameObject*> SceneManager::GetGameObjects(eLayerType layer)
	{
		//DontDestroyOnLoad�� ���̾�� ���� Scene�� ���̾��� ���ӿ�����Ʈ���� ���ļ� ��ȯ
		//�浹ó�� �ϱ�����
		std::vector<GameObject*> gameObjects = mActiveScene->GetLayer(layer)->GetGameObjects();
		std::vector<GameObject*> dontDestroyOnLoad = mDontDestroyOnLoad->GetLayer(layer)->GetGameObjects();

		gameObjects.insert(gameObjects.end(), dontDestroyOnLoad.begin(), dontDestroyOnLoad.end());

		return gameObjects;
	}
}