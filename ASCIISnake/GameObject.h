#pragma once
#include <utility>
class GameObject
{

public:

	enum class Event : int
	{
		NONE,
		PRESSED_A,
		PRESSED_D,
		PRESSED_S,
		PRESSED_W,
		PRESSED_R,
		PRESSED_E,
		COLLISION,
		PLAYER_DEATH,
		FOOD_EATED
	};

	struct Vec2d
	{
		Vec2d(int x, int y) :x(x), y(y)
		{

		}

		Vec2d() :x(0), y(0)
		{

		}

		int x;
		int y;

		template<typename T>
		Vec2d operator+(T&& right)
		{
			Vec2d result;
			result.x = x + std::forward<T>(right.x);
			result.y = y + std::forward<T>(right.y);
			return result;
		}

		template<typename T>
		Vec2d operator-(T&& right)
		{
			Vec2d result;
			result.x = x - std::forward<T>(right.x);
			result.y = y - std::forward<T>(right.y);
			return result;
		}

		bool operator==(const Vec2d& right)
		{
			return x == right.x && y == right.y;
		}
	};

	Vec2d getPosition() { return position; }

	template<typename T>
	void setPosition(T&& newPosition) { position = std::forward<T>(newPosition); }

	virtual bool testCollision(const Vec2d& position) { return this->position == position; };
	//used for optimization
	bool isHaveInput{ false };

	virtual void update() = 0;

	GameObject() = default;
	virtual ~GameObject() = default;
	virtual void draw(int x, int y) = 0;
	GameObject(GameObject&& drawable) = default;
	GameObject(const GameObject& dravable) = default;
	virtual Event processEvent(const Event& event) = 0;
	GameObject& operator=(GameObject&& drawable) = default;
	GameObject& operator=(const GameObject& drawable) = default;
	virtual void processInput(const Event& event) {};
private:
	Vec2d position;
};