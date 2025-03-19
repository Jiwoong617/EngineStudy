#pragma once
#include "jwEntity.h"
#include "jwGameObject.h"
#include "jwLayer.h"

namespace jw
{
	class Scene : public Entity
	{
	public:
		Scene();
		~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		//Scene 이동 관련
		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* gameObj, const enums::eLayerType type);
		Layer* GetLayer(const enums::eLayerType type) { return mLayers[(UINT)type]; }

	private:
		void CreateLayers();

	private:
		std::vector<Layer*> mLayers;
	};
}

