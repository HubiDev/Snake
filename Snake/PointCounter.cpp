#include "PointCounter.h"
#include <string>

/// <summary>
/// Constructor
/// </summary>
PointCounter::PointCounter()
{
	if (_Font.loadFromFile("Resources\\NotoSans-Regular.ttf"))
	{
		_Text.setFont(_Font);
		_Text.setCharacterSize(24);
		_Text.setString("Points: " + to_string(_PointCounter));
		_Text.setFillColor(Color::Black);
		_Text.setPosition(Vector2f(0, 450));
	}
}


/// <summary>
/// Destructor
/// </summary>
PointCounter::~PointCounter()
{
}

/// <summary>
/// 
/// </summary>
void PointCounter::Increment()
{
	++_PointCounter;
	_Text.setString("Points: " + to_string(_PointCounter));
}

/// <summary>
/// Resets the counter.
/// </summary>
void PointCounter::reset()
{
	_PointCounter = 0;
}

/// <summary>
/// 
/// </summary>
/// <param name="target"></param>
/// <param name="states"></param>
void PointCounter::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(_Text);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
PointCounter& PointCounter::operator++()
{
	Increment();
	return *this;
}
