#pragma once
#include "CommonInclude.h"
#include "jwComponent.h"

namespace jw
{
	class GameObject
	{
	public:
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

		eState GetActive() { return mState; }
		void SetActive(bool power)
		{
			if (power == true) mState = eState::Active;
			if (power == false) mState = eState::Paused;
		}
		void Death() { mState = eState::Dead; }

	private:
		//게임 오브젝트 생성 시, transform을 가지고 있게
		void initializeTransform();


	private:
		eState mState;
		std::vector<Component*> mComponents;
	};
}

