#include "switchlogic.h"
#include <QDebug>

SwitchLogic::SwitchLogic(RockerMatrix *matrix, QWidget *parent) : QObject(parent)
{
    _matrix = matrix;
}

void SwitchLogic::rockerSwitched(int x, int y)
{
    qDebug() << "SwitchLogic: rocker (" << x << "," << y << ") switched";
    for (int i = 0; i < _matrix->size(); i++)
    {
        if (i != x)
        {
            _matrix->toggleRocker(i, y);
        }
        if (i != y)
        {
            _matrix->toggleRocker(x, i);
        }
    }
}
