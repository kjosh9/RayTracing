#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <string>
#include <memory>

#include "camera.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "light.hpp"


class Scene{

public:
    Scene(Camera camera,
          std::vector<std::shared_ptr<Light>> lights,
          std::vector<std::shared_ptr<ShadedObject>> objects);
    ~Scene();

    Camera GetCamera();
    Color GetImagePlane();
    point3D GetFocalPoint();
    int GetVerticalSize();
    int GetHorizontalSize();
    double GetVerticalResolution();
    double GetHorizontalResolution();
    std::vector<std::shared_ptr<Light>> GetLights();
    std::vector<std::shared_ptr<ShadedObject>> GetObjects();

private:
    Camera camera_;
    std::vector<std::shared_ptr<Light>> lights_;
    std::vector<std::shared_ptr<ShadedObject>> objects_;
    Color imagePlane_;
    point3D focalPoint_;
};

#endif
