#ifndef BARWANIENGINE_ECS_HPP
#define BARWANIENGINE_ECS_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>



class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;


inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static_assert (std::is_base_of<Component, T>::value, "");
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;


using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component{
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() = default;

};

class Entity{
private:
    Manager& manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
public:
    void update();
    void draw();

    Entity(Manager& amanager) : manager(amanager) {}

    [[nodiscard]] bool isActive() const;
    void destroy();

    //checks if entity is in a given group
    bool hasGroup(Group agroup) {return groupBitSet[agroup];}

    //adds entity to a group
    void addGroup(Group agroup);

    //removes entity from group
    void delGroup(Group agroup) {groupBitSet[agroup] = false;}


    //Checks if Entity has given Component
    template<typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
    //Adding Component to an Entity
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));
        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }
    //Getting Component from an Entity
    template <typename T> [[nodiscard]] bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }
};

class Manager{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
    void update();
    void draw();
    void refresh();

    void addToGroup(Entity* aentity, Group agroup);

    std::vector<Entity*>& getGroup(Group agroup);

    Entity& addEntity();
};

#endif //BARWANIENGINE_ECS_HPP
