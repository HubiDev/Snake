#include "MenuScreen.h"

/// <summary>
/// Constructor
/// </summary>


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
/// 
/// </summary>
/// <param name="target"></param>
/// <param name="states"></param>
void MenuScreen::draw(RenderTarget& target, RenderStates states) const
{
	for (const auto& current : _TextLines)
	{
		target.draw(*current);
	}
}
