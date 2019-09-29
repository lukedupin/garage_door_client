#include "system.h"

System::System( SharedState* shared ) :
    _sharedState( shared )
{
    QObject::connect( qApp, &QGuiApplication::applicationStateChanged,
                      this, &System::onApplicationStateChanged );
}

void System::onApplicationStateChanged( Qt::ApplicationState state )
{
    auto result = false;
    switch ( state )
    {
        case Qt::ApplicationSuspended:
            qDebug("Application Suspended");
            break;

        case Qt::ApplicationHidden:
            qDebug("Application Hidden");
            break;

        case Qt::ApplicationInactive:
            qDebug("Application Inactive");
            break;

        case Qt::ApplicationActive:
            result = true;
            qDebug("Application Active");
            break;

        default:
            qDebug("Unknown application state: %d", state);
            break;
    }

    if ( _online == result )
        return;
    _online = result;
    _sharedState->Mail->emitApplicationStateChanged( _online );
}
