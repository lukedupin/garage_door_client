#ifndef LOCK_H
#define LOCK_H

#include <QObject>
#include <QMutex>

//Handy
#define ScopeLock( x ) \
    auto&& __lock__ __attribute__((unused)) = Lock( &x, __FILE__, __func__, __LINE__ )

class Lock : QObject
{
  QMutex* _mutex;

  public:
  Lock( QMutex* mutex, QString file, QString func, int line );

  ~Lock();
};

#endif
