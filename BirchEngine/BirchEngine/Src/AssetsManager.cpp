#include "AssetsManager.h"
#include "ECS/Components.h"


AssetsManager::AssetsManager(Manager* man):manager(man)
{

}

AssetsManager::~AssetsManager()
{

}

void AssetsManager::CreateProjectile(Vector2D pos,Vector2D vel, int range, int speed, std::string id)
{
	auto& projecttile(manager->addEntity());
	projecttile.addComponent<TransformComponent>(pos.x,pos.y,32,32,1);
	projecttile.addComponent<SpriteComponent>(id, false);
	projecttile.addComponent<ProjecttileComponent>(range,speed,vel);
	projecttile.addComponent<ColliderComponent>("projectile");
	projecttile.addGroup(Game::groupProjectiles);

}

void AssetsManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));


}

SDL_Texture* AssetsManager::GetTexture(std::string id)
{
	return textures[id];
}
