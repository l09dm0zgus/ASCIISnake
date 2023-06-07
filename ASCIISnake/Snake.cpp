#include "Snake.h"
#include <iostream>
#include <algorithm>

Snake::Snake(int sceneWidth, int sceneHeight, int x, int y) : sceneWidth(sceneWidth), sceneHeight(sceneHeight)
{

	parts.emplace_back(x,y);

	setPosition(Vec2d(x, y));

	isHaveInput = true;
}

void Snake::move(int x, int y)
{
	setPosition(Vec2d(x + getPosition().x, y + getPosition().y));

	parts.push_back(getPosition());


	if (parts.size() > lenght)
	{
		parts.erase(parts.begin());
	}
}

void Snake::draw(int j, int i)
{
	bool isBodyPart = false;

	for (auto part : parts)
	{
		if (i == part.y && j == part.x)
		{
			std::cout << '0';
			isBodyPart = true;
			break;
		}
	}
	if (!isBodyPart)
	{
		std::cout << ' ';
	}
}

GameObject::Event Snake::processEvent(const Event& event)
{
	if (isDead)
	{
		return Event::PLAYER_DEATH;
	}
	if (event == Event::COLLISION)
	{
		grow();
		return Event::FOOD_EATED;
	}
	return event;
}

void Snake::processInput(const Event& event)
{
	switch (event)
	{
	case Event::PRESSED_A:
		directionX = -1;
		directionY = 0;
		break;
	case Event::PRESSED_D:
		directionX = 1;
		directionY = 0;
		break;
	case Event::PRESSED_S:
		directionX = 0;
		directionY = 1;
		break;
	case Event::PRESSED_W:
		directionX = 0;
		directionY = -1;
		break;
	default:
		break;
	}
}

void Snake::update()
{
	for (auto& part : parts)
	{
		//check collision with field
		if (part.x <= 1 || part.x >= sceneWidth - 3 || part.y <= 1 || part.y >= sceneHeight - 2 )
		{
			die();
		}
	
	}

	//check head collision with tail
	for (int i = 1; i < parts.size(); i++)
	{
		if (parts[0] == parts[i])
		{
			die();
		}
	}


	if (!isDead)
	{
		move(directionX, directionY);
	}

}

bool Snake::testCollision(const Vec2d& position)
{
	for (auto& part : parts)
	{
		if (part == position)
		{
			return true;
		}
	}
	return false;
}

void Snake::die()
{
	isDead = true;
	parts.erase(parts.begin(), parts.end());
}

void Snake::grow()
{
	lenght++;
}
