#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class PointCounter : public Drawable
{
public:
	PointCounter();
	~PointCounter();

	void Increment();
	void reset();

	// Inherited via Drawable
	virtual void draw(RenderTarget & target, RenderStates states) const override;

	//Operators
	PointCounter& operator++();

private:

	int _PointCounter = 0;
	Font _Font;
	Text _Text;
};

