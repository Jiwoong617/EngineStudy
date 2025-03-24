#pragma once

namespace jw::enums
{
	enum class eLayerType
	{
		None,
		BackGround,
		Player,
		Max = 16,
	};

	enum class eResourceType
	{
		Texture,
		AudioClip,
		Prefab,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Script,

		//ī�޶�� ���� �ʰ� ������Ʈ �Ǿ�ߵ�
		Camera,
		End,
	};
}