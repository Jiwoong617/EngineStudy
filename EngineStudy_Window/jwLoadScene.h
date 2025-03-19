#pragma once
#include "..\\EngineStudy_Source\\jwSceneManager.h"
#include "jwPlayScene.h"
#include "jwTitleScene.h"

namespace jw
{

	void LoadScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}