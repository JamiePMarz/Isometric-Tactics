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
	int scale = 3;

	//MAPS
	{	
		assets->addTexture("map0_ts", "Assets/map0_ts.png");
		IsoMap* map = new IsoMap("map0_ts", scale, 32, "Assets/map0_20x15.map", 20, 15);
		assets->addIsoMap("map0", map);
	}

	{
		assets->addTexture("map1_ts", "Assets/map1_ts.png");
		IsoMap* map = new IsoMap("map1_ts", scale, 32, "Assets/map1_10x8.map", 10, 8);
		assets->addIsoMap("map1", map);
	}

	{
		assets->addTexture("map2_ts", "Assets/map2_ts.png");
		IsoMap* map = new IsoMap("map2_ts", scale, 32, "Assets/map2_10x10.map", 10, 10);
		assets->addIsoMap("map2", map);
	}

	{
		assets->addTexture("map3_ts", "Assets/map3_ts.png");
		IsoMap* map3 = new IsoMap("map3_ts", scale, 32, "Assets/map3_19x10.map", 19, 10);
		assets->addIsoMap("map3", map3);
	}

	//////////
	assets->addTexture("ph_1", "Assets/ph_1.png");
	assets->addTexture("ph_2", "Assets/ph_2.png");
	assets->addTexture("ph_3", "Assets/ph_3.png");
	assets->addTexture("ph_4", "Assets/ph_4.png");
	assets->addTexture("ph_5", "Assets/ph_5.png");


	assets->addTexture("tile_highlighted", "Assets/tile_highlighted.png");
	assets->addTexture("tile_cusor", "Assets/tile_cusor.png");
	assets->addTexture("collider", "Assets/collider.png");
	//

	combatManager = new CombatManager(entityManager);
	
	
	combatManager->startCombat("map3");

	//unit 1
	//make add unit func
	unit1.addComponent<TransformComponent>(scale);
	unit1.addComponent<SpriteComponent>("ph_1");//only draw if placed
	unit1.addComponent<StatsComponent>();
	unit1.addGroup(groupUnits);
	unit1.addGroup(groupRoster);
	combatManager->setUnitsTurn(&unit1);

	unit2.addComponent<TransformComponent>(scale);
	unit2.addComponent<SpriteComponent>("ph_2");
	unit2.addComponent<StatsComponent>();
	unit2.addGroup(groupUnits);
	unit2.addGroup(groupRoster);

	unit3.addComponent<TransformComponent>(scale);
	unit3.addComponent<SpriteComponent>("ph_3");
	unit3.addComponent<StatsComponent>();
	unit3.addGroup(groupUnits);
	unit3.addGroup(groupRoster);

	unit4.addComponent<TransformComponent>(scale);
	unit4.addComponent<SpriteComponent>("ph_4");
	unit4.addComponent<StatsComponent>();
	unit4.addGroup(groupUnits);
	unit4.addGroup(groupRoster);

	unit5.addComponent<TransformComponent>(scale);
	unit5.addComponent<SpriteComponent>("ph_5");
	unit5.addComponent<StatsComponent>();
	unit5.addGroup(groupUnits);
	unit5.addGroup(groupRoster);

	
	



	

	//
	std::cout << "b start map0\n"
		<< "n start map1\n"
		<< "m end combat\n";
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
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:

			break;
		case SDL_BUTTON_RIGHT:

			break;

		default:
			break;
		}

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			setRunning(false);
			break;

		case SDLK_b:
			std::cout << "b pressed to start combat\n";

			combatManager->startCombat("map0");

			break;

		case SDLK_n:
			std::cout << "n pressed to start combat\n";

			combatManager->startCombat("map1");

			break;

		case SDLK_m:
			std::cout << "m pressed to end combat\n";
			combatManager->endCombat();

			break;

		default:
			break;
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

	for (auto& u : units) { u->draw(); }


	SDL_RenderPresent(WindowManager::renderer);
}

void Game::clean()
{
	windowManager->windowClean();
}
