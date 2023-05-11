#pragma once

#include "SDL.h"
#include <iostream>

class Game
{

public:
	Game();

	~Game();

	//初始化 标题 X位置 Y位置 宽 高 游戏是否全屏
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	//事件处理
	void handleEvents();
	
	//更新方法
	void update();
	//渲染器
	void render();
	//清理
	void clean();

	bool running() { return isRunning; }

private:

	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;


};

