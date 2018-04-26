#pragma once

#include <vector>
#include <memory>
#include "Part.h"

using namespace std;


class Snake : public Drawable
{
public:
	Snake();
	~Snake();

	void move();
	void addNewPart();
	void reset();

	Part& getHead();
	Part& getTail();

	bool canSetDirection(Direction dir);
	void setDirection(Direction dir);

	bool headIntersectsWithTail();

	// Inherited via Drawable
	virtual void draw(RenderTarget& target, RenderStates states) const override;

private:
	vector<unique_ptr<Part>> parts;
};

