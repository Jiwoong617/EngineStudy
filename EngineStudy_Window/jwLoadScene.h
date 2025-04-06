#pragma once
#include "..\\EngineStudy_Source\\jwSceneManager.h"
#include "jwPlayScene.h"
#include "jwTitleScene.h"
#include "jwToolScene.h"

namespace jw
{

	void LoadScenes()
	{
		//SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<ToolScene>(L"ToolScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}