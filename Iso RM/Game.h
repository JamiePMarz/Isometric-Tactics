#pragma once
#include "SDL.h"
#include "AssetManager.h"
#include "IsometricMap.h"
#include "WindowManager.h"
#include "Keyboard_Mouse.h"
#include "CombatManager.h"

class AssetManager;
class IsometricMap;

enum gameState
{
	gsCombat

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
		groupSelected,
		groupClickable,
		groupSelectedTile

	};


	//public vars
	static AssetManager* assets;
	static SDL_Event event;

	//getters and setters
	bool isRunning() const { return running; }
	void setRunning(bool run) { running = run; }
	static IsometricMap* map;

	gameState getState() { return state; }
	
private:
	bool running;
	
	static int mouseX, mouseY;
	gameState state = gsCombat;

};