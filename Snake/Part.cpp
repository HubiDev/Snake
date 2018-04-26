#include "Part.h"


/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
Part::Part(const Vector2f& pos)
{
	setSize(Vector2f(10, 10));
	setPosition(pos);
	setFillColor(Color::Blue);
}

/// <summary>
/// 
/// </summary>
Part::~Part()
{
}


Direction Part::getDirection()
{
	return direction;
}


void Part::setDirection(Direction val)
{
	direction = val;
}

/// <summary>
/// 
/// </summary>
/// <param name="direction"></param>
/// <returns></returns>
bool Part::canSetDirection(Direction val)
{	
	switch (val)
	{
	case Direction::Left:
		if (direction == Direction::Right)
			return false;
		break;
	case Direction::Top:
		if (direction == Direction::Bottom)
			return false;
		break;
	case Direction::Right: 
		if (direction == Direction::Left)
			return false;
		break;
	case Direction::Bottom:
		if (direction == Direction::Top)
			return false;
		break;
	default:
		return false; //Invalid value
		break;
	}

	return true;
}

/// <summary>
/// 
/// </summary>
void Part::move()
{
	auto pos = getPosition();

	switch (direction)
	{
	case 0: //left
		setPosition(Vector2f(pos.x - 12, pos.y));
		break;
	case 1: //up
		setPosition(Vector2f(pos.x, pos.y - 12));
		break;
	case 2: //down
		setPosition(Vector2f(pos.x + 12, pos.y));
		break;
	case 3: //right
		setPosition(Vector2f(pos.x, pos.y + 12));
		break;
	default:
		break;
	}
}