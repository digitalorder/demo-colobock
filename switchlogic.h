#ifndef SWITCHLOGIC_H
#define SWITCHLOGIC_H

#include <QObject>
#include "rockermatrix.h"

class SwitchLogic : public QObject
{
    Q_OBJECT
    RockerMatrix * _matrix;
public:
    explicit SwitchLogic(RockerMatrix *matrix, QWidget * parent = 0);

signals:

public slots:
    void rockerSwitched(int x, int y);
};

#endif // SWITCHLOGIC_H
