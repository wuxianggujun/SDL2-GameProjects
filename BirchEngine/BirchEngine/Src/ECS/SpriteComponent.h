#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

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

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFilp = SDL_FLIP_NONE;



	SpriteComponet() = default;
	SpriteComponet(const char* path) {
		setTex(path);
	}
	
	SpriteComponet(const char* path,bool isAnimated) {
		animated = isAnimated;

		Animation idle = Animation(0,3,100);
		Animation walk = Animation(1,8,100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		Play("Idle");

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
		srcRect.y = animIndex*transform->height;



		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width*transform->scale;
		destRect.h = transform->height* transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect,spriteFilp);
	}

	void Play(const char* animName) {
		frams = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;

	}


};