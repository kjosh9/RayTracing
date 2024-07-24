#include <QString>
#include <QDebug>
#include <QImage>

#include "imageprovider.hpp"
#include "renderedimageresponse.hpp"

ImageProvider::ImageProvider(QObject* parent)
    : QQuickAsyncImageProvider()
{
}

ImageProvider::~ImageProvider()
{
}

QQuickImageResponse * ImageProvider::requestImageResponse(const QString &id,
                                                          const QSize & requestedSize)
{
    scene_filename_ = id;
    auto * response = new RenderedImageResponse(id, thread_count_, requestedSize, &pool_);
    QObject::connect(response, &RenderedImageResponse::done, this, &ImageProvider::setImage);
    return response;
}

void ImageProvider::setImage(QImage image)
{
    scene_image_ = image;
}

void ImageProvider::saveImage()
{
    saveImage(scene_filename_.replace(".json", ".jpeg"));
}

void ImageProvider::saveImage(QString filename)
{
    filename.replace("file://", "");
    if (scene_image_.save(filename)) {
        qDebug() << "Image saved to: " + filename;
    } else {
        qDebug() << "Image save unsuccessful";
    }
}

void ImageProvider::setThreadCount(const int thread_count)
{
    qDebug() << "thread count updated to " << thread_count;
    thread_count_ = thread_count;
}
