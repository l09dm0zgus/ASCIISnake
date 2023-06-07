#include "Text.h"
#include <iostream>

Text::Text(const std::string& text, int x, int y):text(text)
{
	setPosition(Vec2d(x-offset, y));
	setSymbolsPosition();

	isHaveInput = true;
}

void Text::draw(int j, int i)
{
	bool isPart = false;

	for (auto symbolPosition : symbolsPosition)
	{
		if (i == symbolPosition.y && j == symbolPosition.x)
		{
			std::cout << text[symbolIndex];
			isPart = true;
			symbolIndex++;
			break;
		}
	}
	if (!isPart)
	{
		std::cout << ' ';
	}
	if (symbolIndex >= text.size())
	{
		symbolIndex = 0;
	}
}

GameObject::Event Text::processEvent(const Event& event)
{
	return event;
}


void Text::update()
{
}

void Text::setSymbolsPosition()
{
	int x = getPosition().x;
	int y = getPosition().y;

	for (auto& symbol : text)
	{
		if (symbol == '\n')
		{
			x = getPosition().x;
			y++;
			symbol = '\0';
		}
		symbolsPosition.emplace_back(x, y);
		x++;
	}
}
