#include "Game.hpp"

Game* game = nullptr;

//ɾ��const char��const����Ȼ���в��ɹ�
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