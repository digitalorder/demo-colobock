#ifndef SWITCHLOGIC_H
#define SWITCHLOGIC_H

#include <QObject>
#include "rockersmatrix.h"
#include "rockersstate.h"
#include "logger.h"
#include <QTimer>

class RockersLogic : public QObject
{
    Q_OBJECT
    RockersMatrix * _matrix;
    RockersState getState();
    QTimer * _delay_timer;
    void toggleRelatedRockers(int x, int y);
    void startSwitching(int x, int y, bool reverseAction);

public:
    explicit RockersLogic(RockersMatrix *matrix, QWidget * parent = 0);
    void emitNewRockersStateSignal();

signals:
    void newRockersStateSignal(RockersState state);
    void rockerSwitchedSignal(int x, int y);
    void undoUserActionSignal();
    void switchingStarted();
    void switchingComplete();

public slots:
    void rockerSwitchedSlot(int x, int y);
    void revertAction(int x, int y);

private slots:
    void rockerDelayTimeout();
};

#endif // SWITCHLOGIC_H
