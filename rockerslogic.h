#ifndef SWITCHLOGIC_H
#define SWITCHLOGIC_H

#include <QObject>
#include "rockersmatrix.h"
#include "rockersstate.h"

class RockersLogic : public QObject
{
    Q_OBJECT
    RockersMatrix * _matrix;
    RockersState getState();
public:
    explicit RockersLogic(RockersMatrix *matrix, QWidget * parent = 0);

signals:
    void newRockersStateSignal(RockersState state);

public slots:
    void rockerSwitched(int x, int y);
};

#endif // SWITCHLOGIC_H
