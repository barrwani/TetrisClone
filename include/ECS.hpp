#ifndef TETRISCLONE_ECS_HPP
#define TETRISCLONE_ECS_HPP

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

//returns a new component ID
inline ComponentID getNewComponentTypeID()
{
    //creates a static component ID
    static ComponentID lastID = 0u;
    //returns the component ID and increments it
    return lastID++;
}

//returns the component ID of a given component
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    //checks if T is a base of Component
    static_assert (std::is_base_of<Component, T>::value, "");
    //creates a static component ID for T
    static ComponentID typeID = getNewComponentTypeID();
    //returns the component ID
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

//bitset for components and groups
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

//array for components
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
protected:
    Manager& manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    //bitset for components and groups
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public:
    void update();
    void draw();

    Entity(Manager& amanager) : manager(amanager) {}

    bool isActive() const;
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
        //creates a new component
        T* c(new T(std::forward<TArgs>(mArgs)...));
        //sets the entity of the component to this entity
        c->entity = this;
        //creates a unique pointer to the component
        std::unique_ptr<Component> uPtr{ c };
        //adds the component to the component list
        components.emplace_back(std::move(uPtr));
        //sets the component in the component array
        componentArray[getComponentTypeID<T>()] = c;
        //sets the component in the component bitset
        componentBitSet[getComponentTypeID<T>()] = true;

        //initializes and returns the component
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

#endif //TETRISCLONE_ECS_HPP
