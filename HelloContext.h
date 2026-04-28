#pragma once

#include <QObject>
#include <QFuture>
#include <QFutureWatcher>

class TaskInterface {
public:
  virtual ~TaskInterface() = default;

public:
  virtual void cancel() = 0;
  virtual bool isCanceled() const = 0;
  virtual double progress() const = 0;
};

Q_DECLARE_INTERFACE(TaskInterface, "com.helloqt.TaskInterface")

class MyFutureTaskBase : public QObject, public TaskInterface {
  Q_OBJECT;
  Q_INTERFACES(TaskInterface);

public:
  Q_PROPERTY(double progress READ progress NOTIFY progressChanged)
  Q_SIGNAL void progressChanged();

  Q_SIGNAL void finished();
  Q_SIGNAL void canceled();

  Q_INVOKABLE virtual void cancel() override = 0;

  QFutureWatcher<void>& watcher() { return m_watcher; }

protected:
  template<typename T>
  void bind(const QFuture<T>& future) {
    if (m_watcher.isRunning()) {
      m_watcher.cancel();
    }

    m_watcher.setFuture(future);

    connect(&m_watcher, &QFutureWatcher<void>::progressValueChanged, this, [this](int progress) {
      Q_EMIT progressChanged();
    });

    connect(&m_watcher, &QFutureWatcher<void>::canceled, this, [this]() {
      Q_EMIT canceled();
    });

    connect(&m_watcher, &QFutureWatcher<void>::finished, this, [this]() {
      Q_EMIT finished();
    });

    connect(&m_watcher, &QFutureWatcher<void>::finished, this, [this]() {
      Q_EMIT progressChanged();
      disconnect(&m_watcher, nullptr, this, nullptr);
    }, Qt::ConnectionType::SingleShotConnection);
  }

private:
  QFutureWatcher<void> m_watcher;
};

// Type erasure wrapper for QFuture<T>
template<typename T>
class MyFutureTask : public MyFutureTaskBase {
public:
  explicit MyFutureTask(QFuture<T> future) : m_future(std::move(future)) {
    bind(m_future);
  }

  void cancel() override {
    m_future.cancel();
  }

  bool isCanceled() const override {
    return m_future.isCanceled();
  }

  double progress() const override {
    return (m_future.progressValue() - m_future.progressMinimum()) / static_cast<double>(m_future.progressMaximum() - m_future.progressMinimum()) * 100.0;
  }

private:
  QFuture<T> m_future;
  QFutureWatcher<T> m_watcher;
};

class HelloContext : public QObject {
  Q_OBJECT;

public:
  explicit HelloContext(QObject *parent = nullptr);

  Q_SIGNAL void step1();
  Q_SIGNAL void step2();
  Q_SIGNAL void step3();

  Q_INVOKABLE MyFutureTask<void>* dispatch();
};
