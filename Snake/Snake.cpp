#include "Snake.h""
#include "Geometry.h"
#include <iostream>

/// <summary>
/// Constructor
/// </summary>
Snake::Snake()
{
	//Create the snake
	parts.push_back(make_unique<Part>(Vector2f(720 / 2, 480 / 2)));
	parts.push_back(make_unique<Part>(Vector2f(720 / 2 + 12, 480 / 2)));
	parts.push_back(make_unique<Part>(Vector2f(720 / 2 + 24, 480 / 2)));
	parts.push_back(make_unique<Part>(Vector2f(720 / 2 + 36, 480 / 2)));
	parts.push_back(make_unique<Part>(Vector2f(720 / 2 + 48, 480 / 2)));
}

/// <summary>
/// Destructor
/// </summary>
Snake::~Snake()
{
}

/// <summary>
/// 
/// </summary>
void Snake::move()
{
	for (int i = static_cast<int>(parts.size()) - 1; i >= 0; --i) //Iterate from tail to head
	{
		const auto& currentPart = parts[i];
		currentPart->move();

		if (i != 0)
		{
			const auto& previous = parts[i - 1];

			if (previous->getDirection() != currentPart->getDirection())
			{
				currentPart->setDirection(previous->getDirection());
			}
		}
	}
}

/// <summary>
/// 
/// </summary>
void Snake::addNewPart()
{
	auto tail = getTail();
	auto direction = tail.getDirection();
	auto pos = tail.getPosition();

	switch (direction)
	{
	case 0: //left --> position right of the tail
	{
		auto newPart = make_unique<Part>(Vector2f(pos.x + 12, pos.y));
		(*newPart).setDirection(Direction::Left);		
		parts.push_back(std::move(newPart));
		break;
	}
	case 1: //up --> position on the bottom of the tail
	{
		auto newPart = make_unique<Part>(Vector2f(pos.x, pos.y + 12));
		(*newPart).setDirection(Direction::Top);
		parts.push_back(std::move(newPart));
		break;
	}
	case 2: //right --> position left of the tail
	{
		auto newPart = make_unique<Part>(Vector2f(pos.x - 12, pos.y));
		(*newPart).setDirection(Direction::Right);
		parts.push_back(std::move(newPart));
		break;
	}
	case 3: //down --> position on the top of the tail
	{
		auto newPart = make_unique<Part>(Vector2f(pos.x, pos.y - 12));
		(*newPart).setDirection(Direction::Bottom);
		parts.push_back(std::move(newPart));
		break;
	}
	default:
		break;
	}
}

/// <summary>
/// Resets the position and apperance of the snake.
/// </summary>
void Snake::reset()
{
	parts.clear();

	parts.push_back(make_unique<Part>(Vector2f(720 / 2, 480 / 2)));
	parts.push_back(make_unique<Part>(Vector2f(720 / 2 + 12, 480 / 2)));
	parts.push_back(make_unique<Part>(Vector2f(720 / 2 + 24, 480 / 2)));
	parts.push_back(make_unique<Part>(Vector2f(720 / 2 + 36, 480 / 2)));
	parts.push_back(make_unique<Part>(Vector2f(720 / 2 + 48, 480 / 2)));
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
Part& Snake::getHead()
{
	return *parts[0];
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
Part& Snake::getTail()
{
	return *parts.back().get();
}

/// <summary>
/// 
/// </summary>
/// <param name="dir"></param>
/// <returns></returns>
bool Snake::canSetDirection(Direction dir)
{
	return (*parts[0]).canSetDirection(dir);
}

/// <summary>
/// 
/// </summary>
/// <param name="dir"></param>
void Snake::setDirection(Direction dir)
{
	(*parts[0]).setDirection(dir);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Snake::headIntersectsWithTail()
{
	bool result = false;

	for (auto& current : parts)
	{
		if (current.get() != parts[0].get()) //head should not compared with itself
		{
			if (Geometry::rectsDoIntersect(current.get()->getPosition(),
				current.get()->getSize(),
				parts[0].get()->getPosition(),
				parts[0].get()->getSize()))
			{
				result = true;
				break;
			}
		}		
	}

	return result;
}

/// <summary>
/// 
/// </summary>
/// <param name="target"></param>
/// <param name="states"></param>
void Snake::draw(RenderTarget& target, RenderStates states) const
{
	for (const auto& current : parts)
	{
		target.draw(*current);
	}
}
