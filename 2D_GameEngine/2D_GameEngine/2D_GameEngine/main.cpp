#include "Game.hpp"

Game* game = nullptr;

//删除const char的const，不然运行不成功
int main(int argc,char * argv[]) {
	game = new Game();
	game->init("BirchEngine",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,false);


	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();

	}

	game->clean();

	return 0;
}