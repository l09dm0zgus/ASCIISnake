#include "Application.h"
#include <Windows.h>
#include <chrono>
#include <thread>
#include "Scene.h"

void Application::clear()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
}

Application::Application(int sceneWidth, int sceneHeight):sceneHeight(sceneWidth),sceneWidth(sceneWidth)
{
	scene = std::make_shared<Scene>(sceneWidth,sceneHeight);
}

void Application::run()
{
	std::thread drawingThread([this]() {
		while (scene->IsRunning)
		{
			scene->draw();
			clear();
		}
		});;

	std::thread logicThread([this]() {
		while (scene->IsRunning)
		{
			//update game object in every 250 ms.
			//Delta Time is`nt used ,besause for moving we need intenger,not float,so we use fixed step update 

			std::this_thread::sleep_for(updatePeriod);
			scene->update();
		}
		});

	std::thread eventsThread([this]() {
		while (scene->IsRunning)
		{
			scene->processEvents();
		}
		});

	std::thread collisionThread([this] {
		while(scene->IsRunning)
		{
			scene->testCollisions();
		}
		});

	logicThread.join();
	drawingThread.join();
	eventsThread.join();
	collisionThread.join();
}
