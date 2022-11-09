#include "Game.h"

WindowManager* windowManager = nullptr;
SDL_Renderer* WindowManager::renderer = nullptr;

Keyboard_Mouse* keyboardMouse = nullptr;

EntityManager entityManager;
CombatManager* combatManager = nullptr;

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
	running = windowManager->getInitialized();

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

	CombatMovement* combatMove = new CombatMovement();
	CombatMenu* combatMenu = new CombatMenu();
	CombatPlacement* combatPlacement = new CombatPlacement();
	combatManager->combatComponents.resize(combatManager->maxCCSize);
	combatManager->combatComponents.assign(combatManager->maxCCSize, nullptr);
	combatManager->combatComponents[CombatManager::move] = combatMove;
	combatManager->combatComponents[CombatManager::menu] = combatMenu;
	combatManager->combatComponents[CombatManager::placement] = combatPlacement;

	for (auto& cc : combatManager->combatComponents)
	{
		if (cc != nullptr)
			cc->combatManager = combatManager;
	}

	//units
	unit1.addComponent<UnitComponent>(&unit1);
	unit2.addComponent<UnitComponent>(&unit2);
	unit3.addComponent<UnitComponent>(&unit3);
	unit4.addComponent<UnitComponent>(&unit4);
	unit5.addComponent<UnitComponent>(&unit5);

	unit1.addGroup(EntityManager::groupRoster);
	unit2.addGroup(EntityManager::groupRoster);
	unit3.addGroup(EntityManager::groupRoster);
	unit4.addGroup(EntityManager::groupRoster);
	unit5.addGroup(EntityManager::groupRoster);

	combatManager->setUnitsTurn(&unit1);

#if MY_DEBUG == 1
	LOG("press b to start map0\n"
	 << "press n to start map1\n"
	 << "press m to end combat\n");
#endif
}

void Game::gameStartCombat(std::string mapID)
{
	if (state != combat)
	{
		state = combat;
		if (combatManager != nullptr)
			combatManager->startCombat(mapID);
		else
			std::cout << "combatManager == nullptr\n";
	}
}

void Game::gameEndCombat()
{
	if (state == combat)
	{
		state = neutral;
		combatManager->endCombat();
	}
}

//below are group vectors
auto& tiles(entityManager.getGroup(EntityManager::groupTiles));
auto& units(entityManager.getGroup(EntityManager::groupUnits));

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	Keyboard_Mouse::event = event;

	switch (event.type)
	{
	case SDL_QUIT:
		running = false;
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mouseX, &mouseY);
		keyboardMouse->setMouseXY(mouseX, mouseY);
		break;

	case SDL_MOUSEBUTTONDOWN://does nothing
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

	default:
		break;
	}

	//keyboard presses
#if MY_DEBUG == 1
	if (keyboardMouse->keyPress(SDLK_ESCAPE))
		running = false;

	if (keyboardMouse->keyPress(SDLK_b))
	{
		LOG("b pressed");
		gameStartCombat("map0");
	}

	if (keyboardMouse->keyPress(SDLK_n))
	{
		LOG("n pressed");
		gameStartCombat("map1");
	}

	if (keyboardMouse->keyPress(SDLK_m))
	{
		LOG("m pressed");
		gameEndCombat();
	}
#endif
}


void Game::update()
{
	entityManager.refresh();
	entityManager.update();
	switch (state)
	{
	case combat:
		combatManager->update();
		break;
	default:
		break;
	}
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
