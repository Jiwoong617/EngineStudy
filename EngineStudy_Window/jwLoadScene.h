#pragma once
#include "..\\EngineStudy_Source\\jwSceneManager.h"
#include "jwPlayScene.h"

namespace jw
{

	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}