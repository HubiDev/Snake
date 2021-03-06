#include <thread>
#include <iostream>
#include <functional>

#include "SFML/Graphics.hpp"

#include "Snake.h"
#include "Bait.h"
#include "Trap.h"
#include "PointCounter.h"
#include "Spawner.h"
#include "MenuScreen.h"

using namespace sf;
using namespace std;

/// <summary>
/// Determines a directions from the currently pressed key.
/// </summary>
/// <returns>A direction</returns>
Direction GetDirectionFromKeyboardInput(Direction last)
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		return Direction::Left;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		return Direction::Top;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		return Direction::Right;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		return Direction::Bottom;
	}

	//Return the old value
	return last;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
int main()
{
	Clock clock;
	RenderWindow window(VideoMode(720, 480), "Snake"); //60x40

	MenuScreen gameOverScreen(720, 480);	
	gameOverScreen.addLine("Game Over", 100, 20);
	gameOverScreen.addLine("Press Enter to try again", 30, 20);
	MenuScreen startScreen(720, 480);
	startScreen.addLine("Snake", 150, 10);
	startScreen.addLine("Press Enter to start", 20, 20);

	Snake snake;
	Spawner<Bait> baitSpawner(5000);
	Spawner<Trap> trapSpawner(1000);
	PointCounter counter;
	Direction lastDirection = Direction::NotSet;
	bool gameOver = false;
	bool gameStarted = false;

	gameOverScreen.addCommand(Keyboard::Return, [&]
	{
		gameOver = false;
		snake.reset();
		baitSpawner.reset();
		trapSpawner.reset();
		counter.reset();
		lastDirection = Direction::NotSet;
	});

	startScreen.addCommand(Keyboard::Return, [&]
	{
		gameStarted = true;
		baitSpawner.reset();
		trapSpawner.reset();
	});

	//Start timers
	clock.restart();
	
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (!gameStarted)
		{
			window.clear(Color::White);
			window.draw(startScreen);
			window.display();
			startScreen.update();
		}
		else
		{
			//Save keyboard input from each iteration
			lastDirection = GetDirectionFromKeyboardInput(lastDirection);

			if (clock.getElapsedTime().asMilliseconds() >= 100 && !gameOver)
			{
				//Redraw
				window.clear(Color::White);

				//Snake
				if (snake.canSetDirection(lastDirection))
				{
					snake.setDirection(lastDirection);
				}

				snake.move();

				auto baitIntersections = baitSpawner.determineIntersection(snake.getHead());

				if (baitIntersections.size() > 0)
				{
					baitSpawner.despawn(baitIntersections);
					snake.addNewPart();
					++counter;
				}

				auto trapIntersections = trapSpawner.determineIntersection(snake.getHead());

				if (trapIntersections.size() > 0)
				{
					gameOver = true;
				}

				if (snake.headIntersectsWithTail())
				{
					gameOver = true;
				}

				baitSpawner.spawnIfTimerElapsed();
				trapSpawner.spawnIfTimerElapsed();

				window.draw(snake);
				window.draw(counter);
				window.draw(baitSpawner);
				window.draw(trapSpawner);

				clock.restart();
				window.display();

				//Check for game over
				auto headPos = snake.getHead().getPosition();
				if (headPos.x < 0 || headPos.y < 0 || headPos.x > 720 || headPos.y > 480)
				{
					gameOver = true;
				}
			}

			if (gameOver)
			{
				window.clear(Color::White);
				window.draw(gameOverScreen);
				window.display();
				gameOverScreen.update();
			}
		}
	}

	return 0;
}