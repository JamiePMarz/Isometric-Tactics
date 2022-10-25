#include "Game.h"

WindowManager* windowManager = nullptr;
SDL_Renderer* WindowManager::renderer = nullptr;

SDL_Event Game::event;

Keyboard_Mouse* keyboardMouse = nullptr;
int Game::mouseX;
int Game::mouseY;

AssetManager* Game::assets = new AssetManager;

EntityManager entityManager;
CombatManager* combatManager = nullptr;

IsometricMap* Game::map;

//move after movement reset deleted
auto& unit1(entityManager.addEntity());



Game::Game()
{}
Game::~Game()
{}

void Game::initialize()
{
	windowManager = new WindowManager();

	windowManager->initialize("Isometric Tactics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 740, false);
	running = windowManager->isInitialized();

	keyboardMouse = new Keyboard_Mouse();
	combatManager = new CombatManager(entityManager);

	assets->addTexture("testTS", "Assets/testTS.png");
	assets->addTexture("placeHolder", "Assets/placeHolderSprite.png");
	assets->addTexture("tile_highlighted", "Assets/tile_highlighted.png");
	assets->addTexture("tile_cusor", "Assets/tile_cusor.png");

	map = new IsometricMap("testTS", 3, 32);
	map->loadMap("Assets/textMap_20x15.map", 20, 15);
	
	unit1.addComponent<TransformComponent>(2, 2, 32, 32);
	unit1.addComponent<SpriteComponent>("placeHolder");
	unit1.addComponent<StatsComponent>();
	unit1.addGroup(groupUnits);

	combatManager->setUnitsTurn(&unit1);//temp
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
