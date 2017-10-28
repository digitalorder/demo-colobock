#ifndef LOCKSLOGIC_H
#define LOCKSLOGIC_H

#include <QObject>
#include "locksarray.h"
#include "rockersmodel.h"

class LocksLogic : public QObject
{
    Q_OBJECT
    int _size;
    bool _is_blocked;

public:
    explicit LocksLogic(int size, QObject *parent = 0);

signals:
    void blockControllers();
    void unblockControllers();
    void lockStateChangedSignal(int x, Lock::State state);

public slots:
    void newRockersStateSlot(const RockersModel &state);
};

#endif // LOCKSLOGIC_H
