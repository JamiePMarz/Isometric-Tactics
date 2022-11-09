#pragma once
#include "CombatManager.h"
#include "CombatComponents.h"
#include "Macros.h"
#include <SDL.h>
#include "AssetManager.h"
#include "WindowManager.h"
#include "Keyboard_Mouse.h"

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

	void gameStartCombat(std::string mapID);
	void gameEndCombat();

	//public vars
	AssetManager* assets = nullptr;
	SDL_Event event;

	//getters and setters
	bool getRunning() const { return running; }
	void setRunning(bool newRunning) { running = newRunning; }

	gameState getGameState() const { return state; }
	void setGameState(gameState newState)
	{ 
		//LOG(newState);
		state = newState;
	}
	
private:
	bool running;
	
	int mouseX, mouseY;
	gameState state = neutral;

};

