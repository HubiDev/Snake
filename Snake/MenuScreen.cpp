#include "MenuScreen.h"

/// <summary>
/// Constructor.
/// </summary>
/// <param name="width">The width of the menu.</param>
/// <param name="height">The height of the menu.</param>
MenuScreen::MenuScreen(int width, int height)
	: _Width(width), _Height(height)
{
	if (!_Font.loadFromFile("resources\\NotoSans-Regular.ttf"))
	{
		throw runtime_error("Couldn't load 'resources\\NotoSans-Regular.ttf'");
	}
};

/// <summary>
/// Destructor
/// </summary>
MenuScreen::~MenuScreen()
{
}

/// <summary>
/// Adds a line of text to the menu.
/// </summary>
/// <param name="content">The text that should be shown.</param>
/// <param name="size">The size the text should have.</param>
/// <param name="margin">The margin of the text.</param>
void MenuScreen::addLine(const String& content, unsigned int size, int margin)
{
	//Add a new line of text to the vector and get a reference to the added element
	_TextLines.push_back(make_unique<Text>(content, _Font, size));
	_Margins.push_back(margin);
	auto& newText = _TextLines.at(_TextLines.size() - 1);
	newText.get()->setFillColor(Color::Black);

	int contentHeight = 0;

	for (int i = 0; i < _TextLines.size(); ++i)
	{
		contentHeight += _TextLines.at(i).get()->getCharacterSize();
		contentHeight += 2 * _Margins[i];
	}

	double offsetY = (_Height - contentHeight) / 2;
	double offsetX = 0;
	int usedSpace = 0;
	int curentMargin = 0;

	//Set positions of all lines
	for (int i = 0; i < _TextLines.size(); ++i)
	{
		auto& current = _TextLines.at(i);
		curentMargin = _Margins[i];
		offsetX = (_Width - current.get()->getLocalBounds().width) / 2;

		current.get()->setPosition(static_cast<float>(offsetX),
			static_cast<float>(offsetY + usedSpace + curentMargin));
		usedSpace += 2 * curentMargin + current.get()->getCharacterSize();
	}
}

/// <summary>
/// Adds a command which is executed when the given key is pressed.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="command">The command.</param>
void MenuScreen::addCommand(Keyboard::Key key, const function<void()>& command)
{
	//Check if command for key was already added
	if (_Commands.find(key) != _Commands.end())
	{
		_Commands[key] = command;
	}
	else
	{
		_Commands.insert({ key, command });
	}
}

/// <summary>
/// Updates the menu screen.
/// </summary>
void MenuScreen::update()
{
	for (auto& current : _Commands)
	{
		if (Keyboard::isKeyPressed(current.first))
		{
			current.second();
		}
	}
}

/// <summary>
/// Draws the menu.
/// </summary>
void MenuScreen::draw(RenderTarget& target, RenderStates states) const
{
	for (const auto& current : _TextLines)
	{
		target.draw(*current);
	}
}
