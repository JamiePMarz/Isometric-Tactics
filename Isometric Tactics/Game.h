#pragma once
#include "Macros.h"
#include "SDL.h"
#include "AssetManager.h"
#include "WindowManager.h"
#include "Keyboard_Mouse.h"
#include "CombatManager.h"
#include "IsoMap.h"

class AssetManager;

enum gameState
{
	combat,
	neutral

};



class Game
{
public:
	Game();
	~Game();

	void initialize();

	void handleEvents();
	void update();
	void render();

	void clean();

	enum groupLabels : std::size_t
	{
		groupTiles,
		groupUnits,
		groupColliders,
		groupClickable,
		groupEnemies,
		groupRange,
		groupRoster

	};


	//public vars
	static AssetManager* assets;
	static SDL_Event event;

	//getters and setters
	bool getRunning() const { return running; }
	void setRunning(bool newRunning) { running = newRunning; }

	gameState getGameState() const { return state; }
	static void setGameState(gameState newState)
	{ 
		//LOG(newState);
		state = newState;
	}
	
private:
	bool running;
	
	int mouseX, mouseY;
	static gameState state;

};