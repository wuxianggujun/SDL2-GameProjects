#pragma once

#include "SDL.h"
#include <iostream>

class Game
{

public:
	Game();

	~Game();

	//��ʼ�� ���� Xλ�� Yλ�� �� �� ��Ϸ�Ƿ�ȫ��
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	//�¼�����
	void handleEvents();
	
	//���·���
	void update();
	//��Ⱦ��
	void render();
	//����
	void clean();

	bool running() { return isRunning; }

private:

	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;


};

