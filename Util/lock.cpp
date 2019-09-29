#include "lock.h"

Lock::Lock( QMutex* mutex, QString file, QString func, int line ) :
  _mutex( mutex )
{
#ifndef TEST_FUNC_TIMING
    Q_UNUSED(file)
    Q_UNUSED(func)
    Q_UNUSED(line)
#endif

    //qDebug("Lock %lld: %s %s %d", (quint64)_mutex, file.toLatin1().data(), func.toLatin1().data(), line  );
    _mutex->lock();
}

Lock::~Lock()
{
    _mutex->unlock();
    //qDebug("Released Lock for: %lld", (quint64)_mutex );
}
