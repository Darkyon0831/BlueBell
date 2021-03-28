#include "DefaultLayouts.h"

namespace StarLab
{
	const std::vector<Value> DefaultLayouts::DefaultStarLabIn = 
	{
		{ Type::SLFloat3, "position", "POSITION" },
		{ Type::SLFloat4, "color", "COLOR" },
		{ Type::SLFloat2, "uv", "TEXCOORD" }
	};

	const std::vector<Value> DefaultLayouts::DefaultStarLabOut =
	{
		{ Type::SLFloat4, "position", "SV_POSITION" },
		{ Type::SLFloat4, "color", "COLOR" },
		{ Type::SLFloat2, "uv", "TEXCOORD" }
	};

	const std::vector<Value> DefaultLayouts::DefaultStarLabOutPixel =
	{
		{ Type::SLFloat4, "color", "SV_TARGET" }
	};
}