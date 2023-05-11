#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

/**
 * 此代码定义了 C++ 中的基本实体组件系统(ECS)。
 * ECS 是一种用于游戏开发和其他应用程序的模式，
 * 用于管理和组织实体的不同组件（例如角色、对象等）
 */

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

//BitSet中存储的是true和false值
using ComponentBitSet = std::bitset<maxComponents>; 
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;
	virtual void init() {}
	virtual void update(){}
	virtual void draw(){}

	virtual ~Component() {}

};

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update() {
		for (auto& c : components) c->update();
	}

	void draw() {
		for (auto& c : components) c->draw();
	}

	bool isActive() const{ return active; }

	void destory() { active = false; }

	template <typename T> bool	hasComponent() const {
		return componentBitSet[getComponentID<T>];
	}

	//这会将您在调用函数时输入的参数转发给组件 T 的构造函数
	template <typename T,typename... TArgs> 
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		//如果添加了组件就会设置为true
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update() {
		for (auto& e : entities) e->update();
	}

	void draw() {
		for (auto& e : entities) e->draw();
	}

	void refresh() {
		//entities.erase 采用第一对/最后一对，并擦除该范围内的所有实体（也可以在单个索引上运行）
		entities.erase(
			//remove_if 在一个范围内迭代一个数组或向量，遵循一元谓词。简单来说，它从传入的 <first> 到 <last> 索引，如果匹配 <rule> 则删除实体。
			std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity) {
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}


};