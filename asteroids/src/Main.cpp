
#include "Game.h"
#include "UIInteract.h"

void callBack(const Interface* pUI, void* p)
{
	Game* pGame = (Game*)p;

	pGame->handleInput(*pUI);
	pGame->update();
	pGame->draw(*pUI);
}


int main(int argc, char** argv)
{
	vec2 topLeft(-200, 200);
	vec2 bottomRight(200, -200);

	Interface ui(argc, argv, "Asteroids", topLeft, bottomRight);
	Game game(topLeft, bottomRight);
	ui.run(callBack, &game);

	return 0;
}