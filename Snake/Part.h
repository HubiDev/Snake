#pragma once

#include <SFML/Graphics.hpp>
#include "Directions.h"

using namespace sf;

class Part : public RectangleShape
{
public:
	Part(const Vector2f& pos);
	~Part();

	//Getter & Setter
	Direction getDirection();
	void setDirection(Direction val);

	bool canSetDirection(Direction val);
	void move();

private:
	Direction direction = Direction::Left;
};

