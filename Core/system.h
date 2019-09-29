#ifndef SYSTEM_H
#define SYSTEM_H

#include <Shared/shared_state.h>

class System : public QObject
{
    Q_OBJECT

    private:
    SharedState* _sharedState = nullptr;
    bool _online = false;

    public:
    explicit System( SharedState* shared_state );

    public slots:
    //Detect application changes
    void onApplicationStateChanged( Qt::ApplicationState state );
};

#endif
