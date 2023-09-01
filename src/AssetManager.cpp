
#include "../include/AssetManager.hpp"


AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager() {}


void AssetManager::AddTexture(const std::string& id, const char* path)
{
    textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(const std::string& id)
{
    return textures[id];
}
