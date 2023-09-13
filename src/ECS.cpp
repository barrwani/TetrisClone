#include "../include/ECS.hpp"


void Entity::update()
{
    for(auto& c : components) c->update();
}

void Entity::draw()
{
    for(auto& c : components) c->draw();
}

bool Entity::isActive() const { return active;}
void Entity::destroy(){ active = false;}

void Manager::update()
{
    for(auto& e : entities) e->update();
}

void Manager::draw()
{
    for(auto& e : entities) e->draw();
}

//refreshes the entity list
void Manager::refresh()
{
    for(auto i(0u); i < maxGroups; i++)
    {
        //gets a reference to the vector of entities in a group
        auto& v(groupedEntities[i]);
        //removes entities that are not active or not in a group
        v.erase(std::remove_if(std::begin(v), std::end(v),
                               [i](Entity* mEntity)
                               {
                                   return !mEntity->isActive() || !mEntity->hasGroup(i);
                               }),
                std::end(v));
    }
    //removes entities that are not active
    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                  [](const std::unique_ptr<Entity> &mEntity)
                                  {
                                      return !mEntity->isActive();
                                  }),
                   std::end(entities));
}

//adds an entity to the entity list
Entity& Manager::addEntity()
{
    //creates a new entity
    auto *e = new Entity(*this);
    //creates a unique pointer to the entity
    std::unique_ptr<Entity> uPtr{ e };
    //adds the entity to the entity list
    entities.emplace_back(std::move(uPtr));
    return *e;
}

//adds an entity to a group
void Entity::addGroup(Group agroup)
{
    groupBitSet[agroup] = true;
    manager.addToGroup(this, agroup);
}

//returns a group's vector of entities
std::vector<Entity*>& Manager::getGroup(Group agroup)
{
    return groupedEntities[agroup];
}

//Adds an entity to a given group
void Manager::addToGroup(Entity* aentity, Group agroup)
{
    groupedEntities[agroup].emplace_back(aentity);
}