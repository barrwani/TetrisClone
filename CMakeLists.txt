cmake_minimum_required(VERSION 3.24)
project (TetrisClone)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR C://libs/sdl2/include)
set(SDL2_LIB_DIR C://libs/sdl2/lib/x86)
set(SDL2_IMAGES_DIR C://libs/sdl2_image/include)
set(SDL2_IMAGES_LIB_DIR C://libs/sdl2_image/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_IMAGES_DIR})
link_directories(${SDL2_IMAGES_LIB_DIR})


add_executable(TetrisClone src/main.cpp include/Utils.hpp src/Game.cpp include/Game.hpp include/TextureManager.hpp src/TextureManager.cpp include/ECS.hpp include/Components.hpp include/TransformComponent.hpp include/SpriteComponent.hpp include/Vector2.hpp src/Vector2.cpp include/KeyboardController.hpp src/TransformComponent.cpp src/SpriteComponent.cpp src/KeyboardController.cpp src/ECS.cpp src/CollisionComponent.cpp include/CollisionComponent.hpp src/Collision.cpp include/Collision.hpp
        src/AssetManager.cpp
        include/AssetManager.hpp
        src/TileComponent.cpp
        include/TileComponent.hpp
)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 )
target_link_libraries(${PROJECT_NAME} SDL2_image SDL2)
