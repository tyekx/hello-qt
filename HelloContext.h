#pragma once

#include <QObject>

class HelloContext : public QObject {
  Q_OBJECT;

public:
  explicit HelloContext(QObject *parent = nullptr);

public:
  Q_INVOKABLE QString greet(const QString &name);

signals:
public slots:
};
