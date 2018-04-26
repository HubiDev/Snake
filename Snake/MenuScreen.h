#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "SFML\Graphics.hpp"

using namespace sf;
using namespace std;

class MenuScreen : public Drawable
{
public:

	MenuScreen(int width, int height);
	~MenuScreen();

	void addLine(const String& content, unsigned int size, int margin);
	void addCommand(Keyboard::Key key, const function<void()>& command);

	void update();

	// Inherited via Drawable
	virtual void draw(RenderTarget & target, RenderStates states) const override;

private:

	Font _Font;

	int _Width;
	int _Height;

	vector<unique_ptr<Text>> _TextLines;
	vector<int> _Margins;

	map<Keyboard::Key, function<void()>> _Commands;
};

