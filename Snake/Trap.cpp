#include "Trap.h"


/// <summary>
/// Constructor
/// </summary>
Trap::Trap(const Vector2f& pos)
{
	setSize(Vector2f(10, 10));
	setPosition(pos);
	setFillColor(Color::Black);
}

/// <summary>
/// Destructor
/// </summary>
Trap::~Trap()
{
}