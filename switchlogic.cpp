#include "switchlogic.h"
#include <QDebug>

SwitchLogic::SwitchLogic(RockerMatrix *matrix, QWidget *parent) : QObject(parent)
{
    _matrix = matrix;
    SwitchesState s = getState();
    emit newSwitchesState(s);
}

SwitchesState SwitchLogic::getState()
{
    SwitchesState state(_matrix->size());
    for (int x = 0; x < _matrix->size(); x++)
    {
        for (int y = 0; y < _matrix->size(); y++)
        {
            state.assign(x, y, _matrix->rockerState(x, y));
        }
    }

    return state;
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

    SwitchesState s = getState();
    emit newSwitchesState(s);
}
