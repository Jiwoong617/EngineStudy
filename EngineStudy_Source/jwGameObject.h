#pragma once
#include "CommonInclude.h"
#include "jwComponent.h"
#include "jwCollider.h"

namespace jw::object
{
	void Destroy(GameObject* gameObject);
}

namespace jw
{
	class GameObject
	{
	public:
		friend void object::Destroy(GameObject* obj);

		enum class eState
		{
			Active,
			Paused,
			Dead,
			End
		};

		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();
			component->Initialize();
			component->SetOwner(this);
			//mComponents.push_back(component);

			mComponents[(UINT)component->GetType()] = component;

			return component;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component = nullptr;
			for (Component* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component) //이걸 잘못 쳤네;;
					break;
			}

			return component;
		}

		eState GetState() { return mState; }
		void SetActive(bool power)
		{
			if (power == true) mState = eState::Active;
			if (power == false) mState = eState::Paused;
		}
		bool IsActive() { return mState == eState::Active; }
		bool IsDead() { return mState == eState::Dead; }

	private:
		//게임 오브젝트 생성 시, transform을 가지고 있게
		void initializeTransform();
		void death() { mState = eState::Dead; }


	private:
		eState mState;
		std::vector<Component*> mComponents;
	};
}

