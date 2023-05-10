#include "LevelScreen.h"
#include "TitleScreen.h"
#include "BossScreen.h"
#include "Game.h"

Game::Game()
	: window(sf::VideoMode::getDesktopMode(), "Buccaneer Blitz", sf::Style::Fullscreen)
	, gameClock()
	, currentScreen(nullptr)
{
	//window setup
	window.setMouseCursorVisible(false);

	//Setup screens
	currentScreen = new BossScreen(this);
}

void Game::RunGameLoop()
{
	//repeat as long as the window is open
	while (window.isOpen())
	{
		Update();
		Draw();
		EventHandling();
	}
}

void Game::EventHandling()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		//close the game if escape is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

void Game::Update()
{
	sf::Time frameTime = gameClock.restart();

	//TODO: Update current screen
	if (currentScreen)
	{
		currentScreen->Update(frameTime);
	}

	//TODO: Handle changes to other screens
}

void Game::Draw()
{
	//TODO: Check for issues; see levelscreen.cpp
	//window.clear();

	if (currentScreen)
	{
		currentScreen->Draw(window);
	}

	window.display();
}

sf::RenderWindow* Game::GetWindow()
{
	return &window;
}

void Game::ChangeGameState(GameState newGameState)
{
	switch (newGameState)
	{
	case GameState::TITLESCREEN:
		currentScreen = new TitleScreen(this);
		break;
	case GameState::LEVELSCREEN:
		currentScreen = new LevelScreen(this);
		break;
	case GameState::BOSSSCREEN:
		currentScreen = new BossScreen(this);
		break;
	default:
		break;
	}
}


