#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "database/DatabaseManager.h"
#include "controller/StudentController.h"
#include "model/StudentModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    initDatabase();

    QQmlApplicationEngine engine;

    StudentController studentController;
    engine.rootContext()->setContextProperty("studentController", &studentController);

    StudentModel studentModel;
    engine.rootContext()->setContextProperty("studentModel", &studentModel);

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
