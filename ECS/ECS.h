#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>
#include <type_traits>

using ComponentTypeID = std::size_t;

class Component;
class Entity;
class EntityManager;

constexpr std::size_t MaxComponents = 32;
using ComponentBitset = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component*, MaxComponents>;


inline auto GetComponentTypeID() -> ComponentTypeID {
	static int component_type_id = 0;
	return component_type_id++;
}

template <typename T> inline auto GetComponentTypeID() -> ComponentTypeID {
	static_assert(std::is_base_of<Component, T>::value,
		"T must inherit from Component");

	static ComponentTypeID component_type_id = GetComponentTypeID();
	return component_type_id;
};

class Component
{
public:
	// Methods
	Component() = default;
    virtual ~Component() = default;

    virtual void Init() {};
    virtual void Update(double delta_time) {};
    virtual void Render() {};

	// Attributes
    Entity* entity=nullptr;

private:

};

class Entity
{
public:
    // Methods
    void Update(double delta_time);
    void Render();

    bool IsAlive() const;
    void Destroy();

    template <typename T>
    bool HasComponent() const;

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... mArgs);

    template <typename T>
    T& GetComponent() const;

private:
    bool is_alive = true;

    std::vector<std::unique_ptr<Component>> components;
    ComponentArray component_array = { 0 };
    ComponentBitset component_bitset = { 0 };
};

class EntityManager
{
public:
    EntityManager() = default;
    ~EntityManager();

    void Update(double delta_time);;
    void Render();

    void Refresh();

    Entity& CreateEntity();

private:
    std::vector<std::unique_ptr<Entity>> entities;
};


template<typename T>
bool Entity::HasComponent() const {
    return this->component_bitset[GetComponentTypeID<T>()];
}

template<typename T, typename ...TArgs>
T& Entity::AddComponent(TArgs && ...mArgs) {
    assert(!HasComponent<T>());

    T* c = new T(std::forward<TArgs>(mArgs)...); // Можно попробовать передавать entity как аргумент, а потом вызывать конструктор Component(entity) для установки c->entity = entity;
    c->entity = this;
    std::unique_ptr<Component> uPtr{ c };
    components.emplace_back(std::move(uPtr));

    ComponentTypeID c_id = GetComponentTypeID<T>();
    component_array[c_id] = c;
    component_bitset[c_id] = true;

    c->Init();
    return *c;
}

template<typename T>
T& Entity::GetComponent() const {
    assert(HasComponent<T>());
    auto ptr = component_array[GetComponentTypeID<T>()];
    return *static_cast<T*>(ptr); // Лучше static_cast, чем reinterpret_cast
}