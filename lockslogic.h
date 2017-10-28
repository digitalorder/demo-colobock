#ifndef LOCKSLOGIC_H
#define LOCKSLOGIC_H

#include <QObject>
#include "locksarray.h"
#include "locksmodel.h"
#include "rockersmodel.h"

class LocksLogic : public QObject
{
    Q_OBJECT
    LocksArray * _locks;

public:
    explicit LocksLogic(LocksArray * locks, QObject *parent = 0);

signals:
    void newLocksStateSignal(LocksModel state);

public slots:
    void newRockersStateSlot(const RockersModel &state);
};

#endif // LOCKSLOGIC_H
