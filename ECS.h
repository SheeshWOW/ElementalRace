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
    virtual ~Component() {};

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
    ComponentArray component_array;
    ComponentBitset component_bitset;
};

class EntityManager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void Update(double delta_time);;
    void Render();

    void Refresh();

    Entity& CreateEntity();
};


// TEST Components
class CounterComponent: public Component
{
public:
	double counter = 0.0;
    void Update(double delta_time) override;
};

class KillComponent : public Component
{
public:
	CounterComponent* cCounter = nullptr;

    void Init() override;
    void Update(double delta_time) override;
};




template<typename T>
bool Entity::HasComponent() const {
    return this->component_bitset[GetComponentTypeID<T>()];
}

template<typename T, typename ...TArgs>
T& Entity::AddComponent(TArgs && ...mArgs) {
    assert(!HasComponent<T>());

    T* c = new T(std::forward<TArgs>(mArgs)...);
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