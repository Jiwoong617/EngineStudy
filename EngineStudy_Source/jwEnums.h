#pragma once

namespace jw::enums
{
	enum class eLayerType
	{
		None,
		BackGround,
		Tile,

		Animal,
		Player,
		Floor,
		Particle,
		Max = 16,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Animation,
		Prefab,
		End,
	};

	enum class eComponentType
	{
		Transform,
		Colider,
		Rigidbody,
		Script,
		SpriteRenderer,
		Animator,

		//ī�޶�� ���� �ʰ� ������Ʈ �Ǿ�ߵ�
		Camera,
		End,
	};

	enum class eColliderType
	{
		Circle2D,
		Rect2D,
		End,
	};

	enum class eUIType
	{
		HpBar,
		Button,
		End,
	};
}