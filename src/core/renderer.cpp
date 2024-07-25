#include <mutex>
#include <thread>
#include "renderer.hpp"

Renderer::Renderer()
{
}

Color Renderer::GetPixel(Scene & scene,
                           const int i,
                           const int j)
{
    point3D iPlaneIntersection(scene.GetHorizontalResolution() * (i-(scene.GetHorizontalSize()/2)),
                                    scene.GetVerticalResolution() * (j-(scene.GetVerticalSize()/2)),
                                    0);

    point3D rayDirection = iPlaneIntersection - scene.GetFocalPoint();
    rayDirection = rayDirection.norm();
    double minDistance = std::numeric_limits<double>::max();
    point3D shadowRay, intersection, normal, closest_obj_intersection, closest_obj_normal;

    int impacted_object = -1;

    //this loop detects of the ray intersects an object
    //and when multiple objects, finds the closest.
    int k = 0;
    for(auto object : scene.GetObjects()){

        if(object->intersects(scene.GetFocalPoint(), rayDirection, intersection, normal)){

            double distance = sqrt((intersection - scene.GetFocalPoint()).dot_product(intersection - scene.GetFocalPoint()));

            if(distance < minDistance){
                minDistance = distance;
                impacted_object = k;
                closest_obj_intersection = intersection;
                closest_obj_normal = normal;
            }
        }
        k++;
    }

    Color pixColor(0,0,0);
    if(impacted_object != -1) {

        for(auto light : scene.GetLights()){

            //determine if there is another object blocking the light
            bool shaded = false;
            shadowRay = (light->location() - closest_obj_intersection).norm();
            if(shadowRay.dot_product(closest_obj_normal) > 0){
                point3D temp1;
                point3D temp2;

                auto objects = scene.GetObjects();
                for(size_t l = 0; l < objects.size(); l++){
                    //test for intersection with other objects
                    if(objects[l]->intersects(closest_obj_intersection, shadowRay, temp1, temp2)){
                        if(temp1.z() > 0){
                            shaded = true;
                            break;
                        }
                    }
                }
                if(!shaded){
                    double scale = closest_obj_normal.dot_product(shadowRay.norm());
                    if (scale < 0){
                        scale *= -1;
                    }
                    pixColor = pixColor + objects[impacted_object]->color() * light->intensity() * scale;
                }
            }
        }
    }

    return pixColor;
}


void Renderer::GetRange(int start_row,
                        int finish_row,
                        Scene & scene,
                        std::vector<std::vector<Color>> & pixMatrix)
{
    std::mutex m;
    for (int i = start_row; i < finish_row; i++){
        for (int j = 0; j < pixMatrix[0].size(); j++) {
            auto value = GetPixel(scene, i, j);
            std::lock_guard<std::mutex> lk(m);
            pixMatrix[i][j] = value;
        }
    }
}

std::vector<std::vector<Color>> Renderer::RenderOnCpu(Scene & scene, int thread_count)
{
    std::vector<std::vector<Color>> pixMatrix(scene.GetHorizontalSize(),
                                              std::vector<Color>(scene.GetVerticalSize(), Color(0,0,0)));
    double maxRed = 0;
    double maxGreen = 0;
    double maxBlue = 0;

    std::vector<std::thread> threads;
    thread_count = std::min(thread_count, scene.GetVerticalSize());
    int starting_row = 0;
    int last_row = pixMatrix.size()/thread_count;
    int range = last_row;

    for (int i = 0; i < thread_count; i++) {
        threads.push_back(std::thread(&Renderer::GetRange,
                                      starting_row,
                                      last_row,
                                      std::ref(scene),
                                      std::ref(pixMatrix)
                                      ));
        starting_row = last_row;
        last_row = range+last_row;
    }
    for (auto & thread: threads) {
        thread.join();
    }

    for(auto & pixelRow: pixMatrix) {
        for (auto & pixel: pixelRow) {
            if(maxRed < pixel.red){
                maxRed = pixel.red;
            }
            if(maxGreen < pixel.green){
                maxGreen = pixel.green;
            }
            if(maxBlue < pixel.blue){
                maxBlue = pixel.blue;
            }
        }
    }

    if (maxRed > 255 || maxBlue > 255 || maxGreen > 255) {
        for(auto & pixelRow: pixMatrix) {
            for (auto & pixel: pixelRow) {
                pixel.red = pixel.red*(255/maxRed);
                pixel.green = pixel.green*(255/maxGreen);
                pixel.blue = pixel.blue*(255/maxBlue);
            }
        }
    }

    return pixMatrix;
}
