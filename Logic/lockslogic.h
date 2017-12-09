#ifndef LOCKSLOGIC_H
#define LOCKSLOGIC_H

#include <QObject>
#include "locksarray.h"
#include "rockersmodel.h"
#include "settings.h"

class LocksLogic : public QObject
{
    Q_OBJECT
    int _size;
    bool _is_blocked;

public:
    explicit LocksLogic(const Settings & settings, QObject * parent = 0): QObject(parent), _size(settings.matrixSize()) { }

signals:
    void blockControllers();
    void unblockControllers();
    void lockStateChangedSignal(int x, Lock::State state);

public slots:
    void newRockersStateSlot(const RockersModel &state);
};

#endif // LOCKSLOGIC_H
