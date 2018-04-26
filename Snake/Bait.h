#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Bait : public RectangleShape
{
public:
	Bait(const Vector2f& pos);
	~Bait();
};

