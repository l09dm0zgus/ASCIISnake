#pragma once
#include <vector>
#include <memory>
#include <atomic>

#include "GameObject.h"

class Scene
{
private:
	int width{ 0 };
	int height{ 0 };
	int score{ 0 };

	//used for thread safety
	//because we adding game objects in vector in threads,so size() can return wrong size 
	//in more complicated game need write own a thread safe container with using mutex
	std::atomic<int> numberOfGameObjects{0};
	


	std::vector<std::shared_ptr<GameObject>> gameObjects;
    GameObject::Event processKeyboard();
	GameObject::Event collisionEvent;
	void addScore();
	void startGame();
	void showLoseMenu();
	void showMainMenu();
	void clear();
public:
	//atomic because read/write in threads
	std::atomic<bool> IsRunning{ true };
	void testCollisions();
	void update();
	void processEvents();
	explicit Scene(int width,int height);
	void draw();
	void addGameObject(const std::shared_ptr<class GameObject> &gameObject);
};

