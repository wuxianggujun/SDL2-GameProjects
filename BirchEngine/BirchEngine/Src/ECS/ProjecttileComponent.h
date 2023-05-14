#pragma once

#include "Ecs.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjecttileComponent : public Component {
public:
	ProjecttileComponent(int rng,int sp,Vector2D ve1):range(rng),speed(sp),velocity(ve1) {

	}
	~ProjecttileComponent() {

	}



	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
		
	}


	void update() override
	{
		distance += speed;

		if (distance > range)
		{
			std::cout << "Out of Range" << std::endl;

			entity->destory();
		}else if (transform->position.x > Game::camera.x+ Game::camera.w || 
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h||
			transform->position.y < Game::camera.y)
		{
			std::cout << "Out of bounds!" << std::endl;
			entity->destory();
		}
	}

private:
	TransformComponent* transform;

	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D velocity;
};