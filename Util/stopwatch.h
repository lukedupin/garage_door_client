#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QElapsedTimer>

//Handy stop watch class
class Stopwatch
{
    QElapsedTimer _timer;
    qint64 _offset;

    public:
    Stopwatch( qint64 offset = 0 );

    //Setup the offset
    qint64 setOffset( qint64 offset );

    //Start a new timer with a new offset
    qint64 start( qint64 offset = 0 );
    qint64 restart( qint64 offset = 0 );

    //Get the current elapsed time with offset
    qint64 elapsed();
};

#endif
