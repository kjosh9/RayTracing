#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <QObject>
#include "imageprovider.hpp"
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationDomain("Josh Labs");
    app.setApplicationName("QtRayTracing");
    QQuickView * view = new QQuickView;
    QQmlEngine * engine = view->engine();

    QObject::connect(engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);
    
    ImageProvider my_image_provider;
    engine->addImageProvider(QLatin1String("rendered_image"), &my_image_provider);

    view->setSource(QUrl::fromLocalFile("gui/gui/main.qml"));

    QObject* root_item = view->rootObject();
    QObject::connect(root_item, SIGNAL(saveFile(QString)),
                     &my_image_provider, SLOT(saveImage(QString)));

    QObject::connect(root_item, SIGNAL(saveFileNoName()),
                     &my_image_provider, SLOT(saveImage()));

    QObject::connect(root_item, SIGNAL(setThreadCount(int)),
                     &my_image_provider, SLOT(setThreadCount(int)));

    view->show();
    return app.exec();
}
