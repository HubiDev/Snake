#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Trap : public RectangleShape
{
public:
	Trap(const Vector2f& pos);
	~Trap();
};

