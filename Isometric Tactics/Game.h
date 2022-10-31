#pragma once
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
		groupSelected,//in use?
		groupClickable,
		groupEnemies,
		groupRange

	};


	//public vars
	static AssetManager* assets;
	static SDL_Event event;

	//getters and setters
	bool isRunning() const { return running; }
	void setRunning(bool setRunning) { running = setRunning; }

	gameState getGameState() const { return state; }
	static void setGameState(gameState setGameState)
	{ 
		std::cout << "game state becomes: " << setGameState << std::endl;
		state = setGameState; 
	}
	
private:
	bool running;
	
	int mouseX, mouseY;
	static gameState state;

};