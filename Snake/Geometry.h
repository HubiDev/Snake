#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

namespace Geometry
{
	static bool rectsDoIntersect(const Vector2f& posA, const Vector2f& sizeA, const Vector2f& posB, const Vector2f& sizeB)
	{
		if (posA.x < posB.x + sizeB.x && posA.x + sizeA.x > posB.x &&
			posA.y < posB.y + sizeB.y && posA.y + sizeA.y > posB.y)
		{
			return true;
		}

		return false;
	}
}
