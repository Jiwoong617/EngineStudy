#pragma once
#include "CommonInclude.h"
#include "jwComponent.h"

namespace jw
{
	class GameObject
	{
	public:
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
				if (component) //�̰� �߸� �Ƴ�;;
					break;
			}

			return component;
		}

	private:
		//���� ������Ʈ ���� ��, transform�� ������ �ְ�
		void initializeTransform();


	private:
		std::vector<Component*> mComponents;
	};
}

