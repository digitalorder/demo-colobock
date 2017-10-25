#ifndef LOCKSLOGIC_H
#define LOCKSLOGIC_H

#include <QObject>
#include "locksarray.h"
#include "locksstate.h"
#include "rockersstate.h"

class LocksLogic : public QObject
{
    Q_OBJECT
    LocksArray * _locks;

public:
    explicit LocksLogic(LocksArray * locks, QObject *parent = 0);
    void newGameAction(int matrixSize);

signals:
    void newLocksStateSignal(LocksState state);

public slots:
    void newRockersStateSlot(RockersState state);
};

#endif // LOCKSLOGIC_H
