#include <fstream>
#include <iostream>
#include <string>
#include <exception>

#include "parse.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "shadedObject.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace parser {

bool parse_json(const json & JSonObj,
        Camera & camera,
        std::vector<std::shared_ptr<Light>> & lights,
        std::vector<std::shared_ptr<ShadedObject>> & objects) {

    // parse camera info
    auto camera_it = JSonObj.find("camera");
    if (camera_it != JSonObj.end()) {
        int focus;
        camera_it.value().at("focus").get_to(focus);
        camera.setFocus(focus);

        double center_x, center_y, center_z;
        camera_it.value().at("center").at("x").get_to(center_x);
        camera_it.value().at("center").at("y").get_to(center_y);
        camera_it.value().at("center").at("z").get_to(center_z);
        camera.setCenter(point3D(center_x, center_y, center_z));

        double normal_x, normal_y, normal_z;
        camera_it.value().at("normal").at("x").get_to(normal_x);
        camera_it.value().at("normal").at("y").get_to(normal_y);
        camera_it.value().at("normal").at("z").get_to(normal_z);
        camera.setNormal(point3D(normal_x, normal_y, normal_z));

        std::vector<double> res;
        camera_it.value().at("resolution").get_to(res);
        camera.setResolution(res[0], res[1]);

        std::vector<int> size;
        camera_it.value().at("size").get_to(size);
        camera.setSize(size[0], size[1]);
    } else {
        return false;
    }

    // parse lights
    auto lights_it = JSonObj.find("lights");
    if (lights_it != JSonObj.end()) {
        for (const auto light: lights_it.value()) {
            double normal_x, normal_y, normal_z;
            light.at("location").at("x").get_to(normal_x);
            light.at("location").at("y").get_to(normal_y);
            light.at("location").at("z").get_to(normal_z);

            double intensity;
            light.at("intensity").get_to(intensity);

            lights.emplace_back(std::make_shared<Light>(intensity, point3D(normal_x, normal_y, normal_z)));
        }
    } else {
        return false;
    }

    // parse shaded objects
    auto objects_it = JSonObj.find("objects");
    if (objects_it != JSonObj.end()) {

        for (const auto object: objects_it.value()) {
            int color_r, color_g, color_b;
            object.at("color").at("r").get_to(color_r);
            object.at("color").at("g").get_to(color_g);
            object.at("color").at("b").get_to(color_b);

            if (color_r > 255 || color_r < 0 || 
                color_g > 255 || color_g < 0 || 
                color_b > 255 || color_b < 0) {
                return false;
            }
            Color c(color_r, color_g, color_b);
            
            double lambert;
            object.at("lambert").get_to(lambert);

            double center_x, center_y, center_z;
            object.at("center").at("x").get_to(center_x);
            object.at("center").at("y").get_to(center_y);
            object.at("center").at("z").get_to(center_z);
            auto center_point = point3D(center_x, center_y, center_z);

            std::string type;
            object.at("type").get_to(type);
            if (type == "sphere") {
                double radius;
                object.at("radius").get_to(radius);
                objects.emplace_back(std::make_shared<Sphere>(lambert, center_point, c, radius));
            } else if (type == "plane") {
                double normal_x, normal_y, normal_z;
                object.at("normal").at("x").get_to(normal_x);
                object.at("normal").at("y").get_to(normal_y);
                object.at("normal").at("z").get_to(normal_z);
                auto normal_point = point3D(normal_x, normal_y, normal_z);
                objects.emplace_back(std::make_shared<Plane>(lambert, center_point, c, normal_point));
            } else {
                return false;
            }
        }
    } else {
        return false;
    }

    return true;
}

bool parse(std::string filename,
           Camera & camera,
           std::vector<std::shared_ptr<Light>> & lights,
           std::vector<std::shared_ptr<ShadedObject>> & objects)
{
    std::ifstream scene_file(filename);
    if (!scene_file.is_open())
        return false;

    scene_file.seekg (0, scene_file.end);
    int length = scene_file.tellg();
    scene_file.seekg (0, scene_file.beg);

    char * contents_buffer = new char [length];

    scene_file.read(contents_buffer,length);

    auto njson = json::parse(contents_buffer);

    try {
        return parse_json(njson, camera, lights, objects);
    } catch (std::exception /*e*/) {
        return false;
    }
}

} //parser
