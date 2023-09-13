
#include "../include/AssetManager.hpp"


AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager() {}


//adds a texture to the texture list
void AssetManager::AddTexture(const std::string& id, const char* path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

//gets a texture from the texture list
SDL_Texture* AssetManager::GetTexture(const std::string& id)
{
    return textures[id];
}
