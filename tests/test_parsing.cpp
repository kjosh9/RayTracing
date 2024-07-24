#include <gtest/gtest.h>
#include <string>
#include <memory>

#include "parse.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "shadedObject.hpp"
#include "color.hpp"

#include "nlohmann/json.hpp"

std::string valid_test_scene = R"({
    "camera": {
        "center": {
            "x": 0,
            "y": 0,
            "z": 0
        },
        "focus": 10,
        "normal": {
            "x": 0,
            "y": 0,
            "z": 1
        },
        "resolution": [
            0.01,
            0.01
        ],
        "size": [
            1024,
            1024
        ]
    },
    "lights": [
        {
            "intensity": 1,
            "location": {
                "x": 5,
                "y": -5,
                "z": 0
            }
        }
    ],
    "objects": [
        {
            "center": {
                "x": 0,
                "y": 0,
                "z": 5
            },
            "color": {
                "b": 0,
                "g": 0,
                "r": 255
            },
            "lambert": 1,
            "radius": 1,
            "type": "sphere"
        },
        {
            "center": {
                "x": 0,
                "y": 5,
                "z": 0
            },
            "color": {
                "b": 255,
                "g": 255,
                "r": 255
            },
            "lambert": 1,
            "normal": {
                "x": 0,
                "y": -1,
                "z": 0
            },
            "type": "plane"
        }
    ]
})";

using json = nlohmann::json;

class ParserTests: public testing::Test {
protected:
    ParserTests() {
        njson_obj = json::parse(valid_test_scene);
    }

    std::vector<std::shared_ptr<Light>> lights = {};
    std::vector<std::shared_ptr<ShadedObject>> objects = {};
    Camera camera{Camera()};
    json njson_obj;
};

TEST_F(ParserTests, ParseCorrectJsonSceneDescription) {
    auto is_valid = parser::parse_json(njson_obj,
                                camera,
                                lights,
                                objects);

    EXPECT_EQ(is_valid, true);

    EXPECT_EQ(camera.center(), point3D(0, 0, 0));
    EXPECT_EQ(camera.focus(), 10);
    EXPECT_EQ(camera.normal(), point3D(0, 0, 1));
    EXPECT_EQ(camera.resolution(), (std::pair<double, double>{0.01, 0.01}));
    EXPECT_EQ(camera.size(), (std::pair<int, int>{1024, 1024}));

    EXPECT_EQ(lights.size(), 1);
    EXPECT_EQ(lights[0]->intensity(), 1);
    EXPECT_EQ(lights[0]->location(), point3D(5, -5, 0));

    EXPECT_EQ(objects.size(), 2);
    EXPECT_EQ(objects[0]->lambert(), 1);
    EXPECT_EQ(objects[0]->center(), point3D(0, 0, 5));
    EXPECT_EQ(objects[0]->color(), Color(255,0,0));

    EXPECT_EQ(objects[1]->lambert(), 1);
    EXPECT_EQ(objects[1]->center(), point3D(0, 5, 0));
    EXPECT_EQ(objects[1]->color(), Color(255,255,255));

    // Todo: Check the specific derived class values
    //EXPECT_EQ(objects[1]->normal(), point3D(0, -1, 0));
}

TEST_F(ParserTests, ParseMissingLightJsonSceneDescription) {
    njson_obj.erase("lights");

    auto is_valid = parser::parse_json(njson_obj,
                                camera,
                                lights,
                                objects);
    EXPECT_EQ(is_valid, false);
}

TEST_F(ParserTests, ParseMissingCameraJsonSceneDescription) {
    njson_obj.erase("camera");

    auto is_valid = parser::parse_json(njson_obj,
                                camera,
                                lights,
                                objects);
    EXPECT_EQ(is_valid, false);
}

TEST_F(ParserTests, ParseMissingObjectsJsonSceneDescription) {
    njson_obj.erase("objects");

    auto is_valid = parser::parse_json(njson_obj,
                                camera,
                                lights,
                                objects);
    EXPECT_EQ(is_valid, false);
}
