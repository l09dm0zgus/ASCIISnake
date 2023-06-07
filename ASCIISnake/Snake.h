#pragma once
#include <vector>
#include "GameObject.h"

class Snake : public GameObject
{
public:
	struct  SnakePart
	{
	};
	explicit Snake(int sceneWidth,int sceneHeight,int x, int y);
	void draw(int j, int i) override;
	Event processEvent(const Event &event) override;
	void processInput(const Event& event) override;
	void update() override;
	bool testCollision(const Vec2d &position) override;
private:
	void die();
	void grow();
	
	int sceneHeight{ 0 };
	int sceneWidth{ 0 };
	int directionX{ 1 };
	int directionY{ 0 };
	std::vector<Vec2d> parts;
	void move(int x, int y);
	int lenght{ 1 };
	bool isDead{ false };
};

