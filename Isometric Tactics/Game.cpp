#include "Game.h"

WindowManager* windowManager = nullptr;
SDL_Renderer* WindowManager::renderer = nullptr;

SDL_Event Game::event;

Keyboard_Mouse* keyboardMouse = nullptr;

AssetManager* Game::assets = nullptr;

EntityManager entityManager;
CombatManager* combatManager = nullptr;
gameState Game::state = neutral;

//move after movement reset deleted
auto& unit1(entityManager.addEntity());


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
	assets->addTexture("map0_ts", "Assets/map0_ts.png");
	IsoMap* map0 = new IsoMap("map0_ts", scale, 32, "Assets/map0_20x15.map", 20, 15);
	assets->addIsoMap("map0", map0);

	assets->addTexture("map1_ts", "Assets/map1_ts.png");
	IsoMap* map1 = new IsoMap("map1_ts", scale, 32, "Assets/map1_10x8.map", 10, 8);
	assets->addIsoMap("map1", map1);

	assets->addTexture("placeHolder", "Assets/placeHolderSprite.png");
	assets->addTexture("tile_highlighted", "Assets/tile_highlighted.png");
	assets->addTexture("tile_cusor", "Assets/tile_cusor.png");
	//

	combatManager = new CombatManager(entityManager);
	
	//temp
	combatManager->startCombat("map0");
	unit1.addComponent<TransformComponent>(2, 2, 32, 32, scale);//create unit roster in battle manager
	unit1.addComponent<SpriteComponent>("placeHolder");
	unit1.addComponent<StatsComponent>();
	unit1.addGroup(groupUnits);
	combatManager->setUnitsTurn(&unit1);
	//
}


//below are vectors
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
		if (SDL_BUTTON_LEFT == event.button.button)
		{}

		if (SDL_BUTTON_RIGHT == event.button.button)
		{}

		break;

	case SDL_KEYDOWN:
		/*if ( event.key.keysym.sym == SDLK_c && event.key.repeat == 0)
		{
			std::cout << "sdlk_c pressed\n";
			combatManager->startCombat("testTS", 3, 32, "Assets/textMap_20x15.map", 20, 15);
		}*/

		if (event.key.keysym.sym == SDLK_ESCAPE)
			setRunning(false);

		break;

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

	for (auto& u : units) { u->draw(); }


	SDL_RenderPresent(WindowManager::renderer);
}

void Game::clean()
{
	windowManager->windowClean();
}
