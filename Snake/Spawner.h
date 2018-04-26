#pragma once
#include <SFML\Graphics.hpp>
#include <stdlib.h>
#include "Geometry.h"

using namespace sf;

template<typename T>
class Spawner : public Drawable
{
public:

	//Constructor & Destructor
	Spawner<T>(int spawnIntervall) 
		: _SpawnIntervall(spawnIntervall)
	{
		_SpawnClock.restart();
	};
	~Spawner<T>() {};


	// Inherited via Drawable
	virtual void draw(RenderTarget& target, RenderStates states) const override
	{
		for (const auto& current : _Spawns)
		{
			target.draw(*current);
		}
	}

	/// <summary>
	/// 
	/// </summary>
	void spawnIfTimerElapsed()
	{
		if (_SpawnClock.getElapsedTime().asMilliseconds() >= _SpawnIntervall)
		{
			//Create random position in the coordinate system of 60x40 where one unit equals 12 pixels
			float x = (rand() % 60) * 12.f;
			float y = (rand() % 40) * 12.f;
			_Spawns.push_back(make_shared<T>(Vector2f(x, y)));
			_SpawnClock.restart();
		}
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="toCompare"></param>
	/// <returns></returns>
	vector<shared_ptr<T>> determineIntersection(const RectangleShape& toCompare)
	{
		vector<shared_ptr<T>> result;

		//For each spawned item check if it intersects with the given one
		for (auto& current : _Spawns)
		{						
			if (Geometry::rectsDoIntersect(current->getPosition(), current->getSize(), toCompare.getPosition(), toCompare.getSize()))
			{
				result.push_back(current);
			}
		}

		return result;
	}

	/// <summary>
	/// Removes a spawened object from the game.
	/// </summary>
	/// <param name="toRemove">the object that should be despawned.</param>
	void despawn(const vector<shared_ptr<T>>& toRemove)
	{
		for (auto& current : toRemove)
		{
			_Spawns.erase(remove(_Spawns.begin(), _Spawns.end(), current));
		}
	}

	/// <summary>
	/// Despawns all objects.
	/// </summary>
	void reset()
	{
		_Spawns.clear();
		_SpawnClock.restart();
	}

private:

	int _SpawnIntervall;
	Clock _SpawnClock;
	vector<shared_ptr<T>> _Spawns;
};
