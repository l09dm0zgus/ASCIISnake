#pragma once
#include "GameObject.h"
#include <string>
#include <vector>

class Text : public GameObject
{
public:
	explicit Text(const std::string &text, int x, int y);
	void draw(int j, int i) override;
	Event processEvent(const Event& event) override;
	void update() override;
private:
	void setSymbolsPosition();
	std::string text;
	std::vector<Vec2d> symbolsPosition;
	int symbolIndex{ 0 };
	int offset{ 10 };
};

