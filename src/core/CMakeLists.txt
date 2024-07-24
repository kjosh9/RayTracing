include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.zip
)

FetchContent_MakeAvailable(json)

add_library(core
    STATIC
    camera.cpp
    color.cpp
    light.cpp
    point3d.cpp
    plane.cpp
    renderer.cpp
    scene.cpp
    shadedObject.cpp
    sphere.cpp
    parse.cpp
)

target_link_libraries(core
PRIVATE
    nlohmann_json::nlohmann_json
)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})