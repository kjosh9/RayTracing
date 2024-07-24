#include "scene.hpp"

Scene::Scene(Camera camera,
             std::vector<std::shared_ptr<Light>> lights,
             std::vector<std::shared_ptr<ShadedObject>> objects):
    camera_(camera),
    lights_(lights),
    objects_(objects)
{
    focalPoint_ = camera_.normal() * (-1 * camera_.focus());
}

Scene::~Scene()
{
}

Camera Scene::GetCamera()
{
    return camera_;
}

Color Scene::GetImagePlane()
{
    return imagePlane_;
}

point3D Scene::GetFocalPoint()
{
    return focalPoint_;
}

std::vector<std::shared_ptr<Light>> Scene::GetLights()
{
    return lights_;
}

std::vector<std::shared_ptr<ShadedObject>> Scene::GetObjects()
{
    return objects_;
}

int Scene::GetVerticalSize()
{
    return GetCamera().size().first;
}

int Scene::GetHorizontalSize()
{
    return GetCamera().size().first;
}
