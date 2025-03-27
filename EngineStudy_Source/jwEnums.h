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

		//카메라는 가장 늦게 업데이트 되어야됨
		Camera,
		End,
	};
}