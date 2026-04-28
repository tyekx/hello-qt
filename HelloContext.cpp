#include "HelloContext.h"

#include <qdebug.h>
#include <QtConcurrent>

HelloContext::HelloContext(QObject *parent) : QObject(parent) {}

MyFutureTask<void>* HelloContext::dispatch() {
  QPromise<void> promise;
  QFuture<void> future = promise.future();
  
  QThreadPool::globalInstance()->start([this, promise = std::move(promise)]() mutable {
    promise.setProgressRange(0, 100);
    promise.start();

    for (int i = 0; i < 1000; i++) {
      if (promise.isCanceled()) {
        promise.finish();
        return;
      }
      promise.setProgressValue((int)((i / 1000.0) * 100));
      QThread::msleep(1);
    }
    promise.finish();
  });

  return new MyFutureTask<void>(future);
}

