#pragma once

#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class MenuScreen : public Drawable
{
public:
	MenuScreen(int width, int height)
		: _Width(width), _Height(height) 
	{
		if (!_Font.loadFromFile("resources\\NotoSans-Regular.ttf"))
		{
			throw;
		}
	};
	~MenuScreen();

	void addLine(const String& content, unsigned int size, int margin);

	// Inherited via Drawable
	virtual void draw(RenderTarget & target, RenderStates states) const override;

private:
	String _Content;
	Font _Font;
	vector<unique_ptr<Text>> _TextLines;
	vector<int> _Margins;
	Text _ContentText;
	int _Width;
	int _Height;
};

