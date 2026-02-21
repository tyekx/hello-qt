#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "HelloContext.h"
#include "MyTableModel.h"

int main(int argc, char *argv[]) {
  qmlRegisterType<HelloContext>("HelloContext", 1, 0, "HelloContext");
  qmlRegisterType<MyTableModel>("HelloContext", 1, 0, "MyTableModel");

  QGuiApplication app(argc, argv);


  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/helloqt/Main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
