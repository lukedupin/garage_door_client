#include "stopwatch.h"

Stopwatch::Stopwatch( qint64 offset ) :
    _offset( offset )
{}

qint64 Stopwatch::setOffset(qint64 offset)
{
    _offset = offset;
    return _timer.elapsed() + _offset;
}

qint64 Stopwatch::start( qint64 offset )
{
    _offset = offset;
    return _timer.restart() + _offset;
}

qint64 Stopwatch::restart( qint64 offset )
{
    _offset = offset;
    return _timer.restart() + _offset;
}

qint64 Stopwatch::elapsed()
{
    return _timer.elapsed() + _offset;
}
