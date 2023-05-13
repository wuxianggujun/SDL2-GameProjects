#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponet : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	bool animated = false;
	int frams = 0;
	int speed = 100;


public:
	SpriteComponet() = default;
	SpriteComponet(const char* path) {
		setTex(path);
	}
	
	SpriteComponet(const char* path,int nFrams,int mSpeed) {
		animated = true;
		frams = nFrams;
		speed = mSpeed;
		setTex(path);
	}

	~SpriteComponet() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path) {
		texture = TextureManager::LoadTexture(path);
	}

	void init()override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		
	}


	void update() override{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frams);

		}

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width*transform->scale;
		destRect.h = transform->height* transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect);
	}



};