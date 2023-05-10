#pragma once
#include <SFML/Graphics.hpp>

enum class GameState
{
	TITLESCREEN,
	LEVELSCREEN,
	BOSSSCREEN
};

class Screen;

class Game
{
public:

	Game();

	void RunGameLoop();

	void EventHandling();
	void Update();
	void Draw();

	sf::RenderWindow* GetWindow();
	void ChangeGameState(GameState newGameState);

private:

	sf::RenderWindow window;
	sf::Clock gameClock;

	Screen* currentScreen;
};