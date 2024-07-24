#include <QPainter>
#include <QColor>
#include <QDebug>
#include <chrono>
#include <memory>

#include "imagerenderrunnable.hpp"
#include "core/sphere.hpp"
#include "core/scene.hpp"
#include "core/camera.hpp"
#include "core/light.hpp"
#include "core/renderer.hpp"
#include "core/point3d.hpp"
#include "core/parse.hpp"
#include "core/color.hpp"

ImageRenderRunnable::ImageRenderRunnable(const QString &id,
                                         const int thread_count,
                                         QObject *parent)
  : QObject(parent)
  , id_{id}
  , thread_count_{thread_count}
{
}

void ImageRenderRunnable::run()
{
    using namespace std::chrono;
    auto start_time = high_resolution_clock::now();
    QString scene_filename_ = id_;
    scene_filename_.replace("file://", "");

    Renderer new_renderer = Renderer();
    std::vector<std::shared_ptr<Light>> lights = {};
    std::vector<std::shared_ptr<ShadedObject>> objects = {};
    Camera camera = Camera();

    auto valid_image = parser::parse(scene_filename_.toStdString(),
                                     camera,
                                     lights,
                                     objects);


    Scene new_scene = Scene(camera, lights, objects);

    //loop through the pixMatrix to create the image
    QImage scene_image_ = QImage(new_scene.GetCamera().size().first,
                          new_scene.GetCamera().size().second,
                          QImage::Format_ARGB32_Premultiplied);

    QPainter painter(&scene_image_);
    painter.fillRect(scene_image_.rect(), Qt::black);

    if (!valid_image) {
        emit done(scene_image_);
        return;
    }

    std::vector<std::vector<Color>> pixMatrix = new_renderer.RenderOnCpu(new_scene, thread_count_);

    for(int i=0; i<pixMatrix.size(); i++){
        for (int j=0; j<pixMatrix[0].size(); j++) {
            QColor newColor;
            newColor.setRgb(pixMatrix[i][j].red, pixMatrix[i][j].green, pixMatrix[i][j]
            .blue);
            scene_image_.setPixel(i , j, newColor.rgb());
        }
    }

    auto render_duration = duration_cast<milliseconds>(high_resolution_clock::now() - start_time);
    qDebug() << "Render time: " << render_duration.count()/1000.0 << "seconds";
    emit done(scene_image_);
}
