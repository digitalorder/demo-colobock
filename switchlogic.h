#ifndef SWITCHLOGIC_H
#define SWITCHLOGIC_H

#include <QObject>
#include "rockermatrix.h"
#include "switchesstate.h"

class SwitchLogic : public QObject
{
    Q_OBJECT
    RockerMatrix * _matrix;
    SwitchesState getState();
public:
    explicit SwitchLogic(RockerMatrix *matrix, QWidget * parent = 0);

signals:
    void newSwitchesState(SwitchesState state);

public slots:
    void rockerSwitched(int x, int y);
};

#endif // SWITCHLOGIC_H
