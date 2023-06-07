#include "Food.h"
#include <iostream>
#include <random>

Food::Food(int sceneWidth, int sceneHeight) :sceneWidth(sceneWidth), sceneHeight(sceneHeight)
{
	this->sceneWidth = sceneWidth;
	this->sceneHeight = sceneHeight;
	generateNewPosition();
}

GameObject::Event Food::processEvent(const Event& event)
{
	Event currentEvent = Event::NONE;
	switch (event)
	{
	case Event::COLLISION:
		generateNewPosition();
		currentEvent = Event::FOOD_EATED;
		break;
	default:
		break;
	}
	return currentEvent;
}

void Food::draw(int j, int i)
{
	if (j == getPosition().x && i == getPosition().y)
	{
		std::cout << symbol;
	}
	

}

void Food::update()
{
}

void Food::generateNewPosition()
{
	std::random_device randomDevice;
	std::mt19937 mt(randomDevice());

	std::uniform_int_distribution<int> xDistribution(minimalX, sceneWidth - minimalX);
	std::uniform_int_distribution<int> yDistribution(minimalY, sceneHeight - minimalY);

	setPosition(Vec2d(xDistribution(mt), yDistribution(mt)));
}
