#include "Scene.h"
#include "Scene.h"
#include "Snake.h"
#include "Food.h"
#include "Text.h"
#include <conio.h>
#include <iostream>

GameObject::Event Scene::processKeyboard()
{
	GameObject::Event event{GameObject::Event::NONE};

	//For working input in Win11 need to click somewhere in  terminal window
	//why is not working without clicking in terminal window - idk
	if(_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			event = GameObject::Event::PRESSED_W;
			break;
		case 's':
			event = GameObject::Event::PRESSED_S;
			break;
		case 'd':
			event = GameObject::Event::PRESSED_D;
			break;
		case 'a':
			event = GameObject::Event::PRESSED_A;
			break;
		case 'W':
			event = GameObject::Event::PRESSED_W;
			break;
		case 'S':
			event = GameObject::Event::PRESSED_S;
			break;
		case 'D':
			event = GameObject::Event::PRESSED_D;
			break;
		case 'A':
			event = GameObject::Event::PRESSED_A;
			break;
		case 'R':
			startGame();
			break;
		case 'r' :
			startGame();
			break;
		case 'E':
			IsRunning = false;
			break;
		case 'e':
			IsRunning = false;
			break;
		}
	}
	return event;
}

void Scene::addScore()
{
	score += 10;
}

void Scene::startGame()
{
	clear();

	auto snake = std::make_shared<Snake>(width, height, static_cast<int>(width / 2), static_cast<int>(height / 2));
	auto food = std::make_shared<Food>(width, height);

	addGameObject(food);
	addGameObject(snake);
}

void Scene::showLoseMenu()
{
	clear();
	auto text = std::make_shared<Text>("SCORE : " + std::to_string(score) + "\nPRESS R TO RESTART\nPRESS E TO EXIT\n", static_cast<int>(width / 2), static_cast<int>(height / 2));
	addGameObject(text);
}

void Scene::showMainMenu()
{

	clear();
	auto text = std::make_shared<Text>("SNAKE\nPRESS R TO START\n", static_cast<int>(width / 2), static_cast<int>(height / 2));
	addGameObject(text);
}

void Scene::clear()
{
	numberOfGameObjects = 0;
	gameObjects.clear();

}


void Scene::testCollisions()
{
	//if ths game have many objects with complex shapes for checking collisions need use physics engine and quad/octrees,
	//but this game is simple terminal game we iterating all objects in loops
	if (numberOfGameObjects > 1)
	{
		for (auto gameObject1 : gameObjects)
		{
			for (auto gameObject2 : gameObjects)
			{
				if (gameObject1->testCollision(gameObject2->getPosition()) && gameObject1 != gameObject2)
				{
					//inform game objects about colliding,and get their event
					collisionEvent = gameObject1->processEvent(GameObject::Event::COLLISION);
					collisionEvent = gameObject2->processEvent(GameObject::Event::COLLISION);
				}
			}
		}
	}
	
}
void Scene::update()
{
	//update game objects
	for (auto& gameObject : gameObjects)
	{
		gameObject->update();
	}
}
void Scene::processEvents()
{
	GameObject::Event currentEvent = GameObject::Event::NONE;

	if (numberOfGameObjects > 0)
	{
		for (auto gameObject : gameObjects)
		{
			if (gameObject->isHaveInput)
			{
				 gameObject->processInput(processKeyboard());
			}

			currentEvent = gameObject->processEvent(currentEvent);

			switch (currentEvent)
			{
			case GameObject::Event::PLAYER_DEATH:
				showLoseMenu();
				break;
			default:
				break;
			}
			switch (collisionEvent)
			{
			case GameObject::Event::FOOD_EATED:
				addScore();
				break;
			default:
				break;
			}
		}
	}
	//clear collision event
	collisionEvent = GameObject::Event::NONE;
}

Scene::Scene(int width, int height) : width(width),height(height)
{
	showMainMenu();
}

void Scene::draw()
{
	std::cout << "SCORE: " << score << "\n";
	//draw field
	for (int i = 0; i < height; i++)
	{
		std::cout << "\t\t#";
		for (int j = 0; j < width - 2; j++)
		{
			if (i == 0 || i == height - 1)
			{
				std::cout << '#';
			}
			else
			{
				if (numberOfGameObjects > 0)
				{
					//setting current cursor position to game object and draw it
					for (auto& gameObject : gameObjects)
					{
						gameObject->draw(j, i);
					}
				}
			}
		
		}
		std::cout << "#\n";
	}

}

void Scene::addGameObject(const std::shared_ptr<class GameObject>& gameObject)
{
	gameObjects.push_back(gameObject);
	numberOfGameObjects++;
}
