#include "HelloContext.h"

#include <qdebug.h>

HelloContext::HelloContext(QObject *parent) : QObject(parent) {}

QString HelloContext::greet(const QString &name) {
  qDebug() << name;
  return "Hello from Cxx";
}
