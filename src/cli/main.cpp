#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "sphere.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "renderer.hpp"
#include "point3d.hpp"
#include "color.hpp"
#include "parse.hpp"

using namespace std;

int main(int argc, char** argv) {

    int thread_count = 1;
    string scene_file;
    string output_file;
    for (int i = 1; i < argc; ++i) {
        string argument = argv[i];

        if (argument == "--help" || argument == "-h") {
            std::cout << "-s, --scene         selected input scene file" << endl;
            std::cout << "-o, --output        output file, .png will be appended" << endl;
            std::cout << "-t, --threads       number of threads used to process scene" << endl;
            return 0;

        } else if (argument == "--scene" || argument == "-s") {
            if (i+1 == argc) {
                std::cout << "No scene file specified" << endl;
                return -1;
            }
            scene_file = argv[i+1];
            i++;
        } else if (argument == "--output" || argument  == "-o") {
            if (i+1 == argc) {
                std::cout << "No output file specified" << endl;
                return -1;
            }
            output_file = argv[i+1];
            i++;

        } else if (argument == "--threads" || argument == "-t") {
            if (i+1 == argc) {
                std::cout << "No thread count specified" << endl;
            }
            thread_count = stoi(argv[i+1]);
            i++;
        } else {
            std::cout << "Invalid argument: " << argument << endl;
        }
    }

    if (scene_file.empty()) {
        std::cout << "No scene file specified" << endl;
        return -1;
    } else {
        cout << "scene file: " << scene_file << endl;
    }
    Renderer new_renderer = Renderer();
    std::vector<std::shared_ptr<Light>> lights = {};
    std::vector<std::shared_ptr<ShadedObject>> objects = {};
    Camera camera = Camera();

    auto valid_image = parser::parse(scene_file,
                                    camera,
                                    lights,
                                    objects);

    Scene new_scene = Scene(camera, lights, objects);

    if (!valid_image) {
        cout << "invalid scene description" << endl;
        return -1;
    }

    vector<vector<Color>> pixMatrix = new_renderer.RenderOnCpu(new_scene, thread_count);
    cv::Mat image(pixMatrix.size(), pixMatrix[0].size(), CV_8UC3);

    for (int i=0; i < pixMatrix.size(); i++) {
        for (int j=0; j < pixMatrix[0].size(); j++) {
            image.at<cv::Vec3b>(pixMatrix.size() - i, pixMatrix[0].size() -j) = cv::Vec3b(pixMatrix[i][j].blue,
                                                  pixMatrix[i][j].green,
                                                  pixMatrix[i][j].red);
        }
    }


    if (output_file.empty()) {
        output_file = "output.png";
    } else {
        output_file += ".png";
    }

    cv::imwrite(output_file, image);

    return 0;
}