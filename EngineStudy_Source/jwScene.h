#pragma once
#include "jwEntity.h"
#include "jwGameObject.h"

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

		void AddGameObject(GameObject* gameobject);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}

