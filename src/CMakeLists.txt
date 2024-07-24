find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

add_subdirectory(core)

find_package(OpenCV REQUIRED)

add_executable(rayTracing
    cli/main.cpp
)

qt_add_executable(appQtRayTracing
    gui/main.cpp
    gui/imageprovider.cpp
    gui/renderedimageresponse.cpp
    gui/imagerenderrunnable.cpp
)

qt_add_qml_module(appQtRayTracing
    URI gui
    VERSION 1.0
    QML_FILES
        gui/main.qml
        gui/aboutWindow.qml
    RESOURCES
        gui/assets/rotating_gear.gif
)

target_link_libraries(rayTracing
    PRIVATE
    core
    nlohmann_json::nlohmann_json
    ${OpenCV_LIBS}
)

target_include_directories(rayTracing INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

target_link_libraries(appQtRayTracing 
    PRIVATE
    core
    Qt6::Quick
    nlohmann_json::nlohmann_json
)

target_include_directories(appQtRayTracing INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(appQtRayTracing PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION  ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
