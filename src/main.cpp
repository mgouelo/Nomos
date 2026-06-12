#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "database/DatabaseManager.h"
#include "controller/StudentController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    initDatabase();

    QQmlApplicationEngine engine;

    StudentController studentController;

    engine.rootContext()->setContextProperty("studentController", &studentController);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );
    engine.loadFromModule("Nomos", "Main");

    return app.exec();
}
