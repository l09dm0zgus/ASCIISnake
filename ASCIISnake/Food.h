#pragma once
#include "GameObject.h"

class Food : public GameObject
{
public:
	explicit Food(int sceneWidth,int sceneHeight);
	Event processEvent(const Event& event) override;
	void draw(int j, int i) override;
	void update() override;
private:
	char symbol{'*'};
	int sceneHeight{ 25 };
	int sceneWidth{ 50 };
	void generateNewPosition();
	int minimalX{5};
	int minimalY{5};
};

