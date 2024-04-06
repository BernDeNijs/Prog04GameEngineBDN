#pragma once
#include <memory>
namespace bdnE
{
	enum class KeyState
	{
		pressed,
		pressedThisFrame,
		releasedThisFrame
	};

	class Command;
}

