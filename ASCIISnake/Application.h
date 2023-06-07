#pragma once
#include <chrono>
#include <memory>

using namespace std::chrono_literals;
class Application
{
private:
	void clear();
	int sceneWidth{ 0 };
	int sceneHeight{ 0 };
	std::shared_ptr<class Scene> scene;
	std::chrono::milliseconds updatePeriod = 250ms;
public:
	Application(int sceneWidth,int sceneHeight);
	void run();

};

