#ifndef RENDERER_H
#define RENDERER_H

#include "point3d.hpp"
#include "scene.hpp"

class Renderer
{
public:
    Renderer();
    std::vector<std::vector<Color>> RenderOnCpu(Scene & scene, int thread_count);

private:

    static void GetRange(int start_pixel,
                         int finish_pixel,
                         Scene & scene,
                         std::vector<std::vector<Color>> & pixel_matrix);

    static Color GetPixel(Scene & scene,
                          const int column,
                          const int row);
};

#endif
