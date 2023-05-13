#pragma once

#include "Ecs.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <SDL.h>

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponet* sprite;

	SDL_Rect tileRect;
	int tileID;
	char* path;


	TileComponent() = default;

	TileComponent(int x,int y,int w,int h,int id){
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "assets/dirt.png";
			break;
		case 1:
			path = "assets/grass.png";
			break;
		case 2:
			path = "assets/water.png";
			break;
		default:
			break;
		}

	}


	void init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, (float)tileRect.w, (float)tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponet>(path);
		sprite = &entity->getComponent<SpriteComponet>();


	}

};