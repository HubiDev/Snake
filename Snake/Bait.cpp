#include "Bait.h"


/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
Bait::Bait(const Vector2f& pos)
{
	setSize(Vector2f(10, 10));
	setPosition(pos);
	setFillColor(Color::Red);
}


/// <summary>
/// 
/// </summary>
Bait::~Bait()
{
}