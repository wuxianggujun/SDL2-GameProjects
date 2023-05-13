#include "Ecs.h"

void Entity::addGroup(Group mGroup) {
	groupBitSet[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}