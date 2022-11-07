#include "Game.h"
#include <algorithm>

WindowManager* windowManager = nullptr;
SDL_Renderer* WindowManager::renderer = nullptr;

SDL_Event Game::event;

Keyboard_Mouse* keyboardMouse = nullptr;

AssetManager* Game::assets = nullptr;

EntityManager entityManager;
CombatManager* combatManager = nullptr;
gameState Game::state = neutral;

//move after movement reset deleted
Entity& unit1(entityManager.addEntity()); 
Entity& unit2(entityManager.addEntity());
Entity& unit3(entityManager.addEntity());
Entity& unit4(entityManager.addEntity());
Entity& unit5(entityManager.addEntity());


Game::Game()
{}
Game::~Game()
{}

void Game::initialize()
{
	windowManager = new WindowManager();
	windowManager->initialize("Isometric Tactics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, false);
	running = windowManager->isInitialized();

	keyboardMouse = new Keyboard_Mouse();

	assets = new AssetManager();
	int scale = 2;

	//maps
	assets->createMapAsset("Assets/map0_ts.png", scale, "Assets/map0_20x15.map", "map0");
	assets->createMapAsset("Assets/map1_ts.png", scale, "Assets/map1_10x8.map", "map1");
	assets->createMapAsset("Assets/map2_ts.png", scale, "Assets/map2_10x10.map", "map2");
	assets->createMapAsset("Assets/map3_ts.png", scale, "Assets/map3_19x10.map", "map3");

	//unit sprites
	assets->addTexture("ph_1", "Assets/ph_1.png");
	assets->addTexture("ph_2", "Assets/ph_2.png");
	assets->addTexture("ph_3", "Assets/ph_3.png");
	assets->addTexture("ph_4", "Assets/ph_4.png");
	assets->addTexture("ph_5", "Assets/ph_5.png");

	//tile/curosr sprites
	assets->addTexture("tile_highlighted", "Assets/tile_highlighted.png");
	assets->addTexture("tile_cusor", "Assets/tile_cusor.png");
	assets->addTexture("collider", "Assets/collider.png");

	combatManager = new CombatManager(entityManager);
	combatManager->startCombat("map1");

	//units
	unit1.addComponent<UnitComponent>(&unit1);
	unit2.addComponent<UnitComponent>(&unit2);
	unit3.addComponent<UnitComponent>(&unit3);
	unit4.addComponent<UnitComponent>(&unit4);
	unit5.addComponent<UnitComponent>(&unit5);

	unit1.addGroup(groupRoster);
	unit2.addGroup(groupRoster);
	unit3.addGroup(groupRoster);
	unit4.addGroup(groupRoster);
	unit5.addGroup(groupRoster);

	combatManager->setUnitsTurn(&unit1);

	LOG("press b to start map0\n"
	 << "press n to start map1\n"
	 << "press m to end combat\n");

}

//below are group vectors
auto& tiles(entityManager.getGroup(Game::groupTiles));
auto& units(entityManager.getGroup(Game::groupUnits));

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		running = false;
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mouseX, &mouseY);
		keyboardMouse->setMouseXY(mouseX, mouseY);
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			//do stuff
			break;
		case SDL_BUTTON_RIGHT:
			//do stuff
			break;

		default:
			break;
		}
	case SDL_KEYDOWN:

		//escape
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			LOG("escape pressed");
			setRunning(false);
		}

		//b
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
		{
			LOG("b pressed");
			combatManager->startCombat("map0");
		}

		//n
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
		{
			LOG("n pressed");
			combatManager->startCombat("map1");
		}

		//m
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
		{
			LOG("m pressed");
			combatManager->endCombat();
		}

	default:
		break;
	}
}


void Game::update()
{
	entityManager.refresh();
	entityManager.update();
	combatManager->update();
}


void Game::render()
{
	SDL_RenderClear(WindowManager::renderer);

	for (auto& t : tiles) { t->draw(); }

	sort(units.begin(), units.end(),
		[](const Entity* e1, const Entity* e2)
		{
			return e1->getComponent<TransformComponent>().grid.y < e2->getComponent<TransformComponent>().grid.y;
		});

	for (auto& u : units) { u->draw(); }

	SDL_RenderPresent(WindowManager::renderer);
}

void Game::clean()
{
	windowManager->windowClean();
}
