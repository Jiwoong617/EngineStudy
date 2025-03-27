#pragma once

namespace jw::enums
{
	enum class eLayerType
	{
		None,
		BackGround,
		Player,
		Animal,
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
		SpriteRenderer,
		Animator,
		Script,

		//ī�޶�� ���� �ʰ� ������Ʈ �Ǿ�ߵ�
		Camera,
		End,
	};
}