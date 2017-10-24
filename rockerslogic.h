#ifndef SWITCHLOGIC_H
#define SWITCHLOGIC_H

#include <QObject>
#include "rockersmatrix.h"
#include "rockersstate.h"
#include "logger.h"

class RockersLogic : public QObject
{
    Q_OBJECT
    RockersMatrix * _matrix;
    RockersState getState();
    void toggleRelatedRockers(int x, int y);

public:
    explicit RockersLogic(RockersMatrix *matrix, QWidget * parent = 0);
    void emitNewRockersStateSignal();

signals:
    void newRockersStateSignal(RockersState state);
    void rockerSwitchedSignal(int x, int y);
    void undoUserActionSignal();

public slots:
    void rockerSwitchedSlot(int x, int y);
    void revertAction(int x, int y);
};

#endif // SWITCHLOGIC_H
