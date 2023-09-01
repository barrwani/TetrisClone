#ifndef BARWANIENGINE_ASSETMANAGER_HPP
#define BARWANIENGINE_ASSETMANAGER_HPP


#include <map>
#include <string>
#include "TextureManager.hpp"
#include "Vector2.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class AssetManager
{
public:
    explicit AssetManager(Manager* man);
    ~AssetManager();



    //texture management
    void AddTexture(const std::string& id, const char* path);
    SDL_Texture* GetTexture(const std::string& id);

private:

    Manager* manager;
    std::map<std::string, SDL_Texture*> textures;
};



#endif //BARWANIENGINE_ASSETMANAGER_HPP
