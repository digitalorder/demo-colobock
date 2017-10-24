#include "rockerslogic.h"
#include <QDebug>

RockersLogic::RockersLogic(RockersMatrix *matrix, QWidget *parent) : QObject(parent)
{
    _matrix = matrix;
    RockersState s = getState();
    emit newRockersStateSignal(s);
}

RockersState RockersLogic::getState()
{
    RockersState state(_matrix->size());
    for (int x = 0; x < _matrix->size(); x++)
    {
        for (int y = 0; y < _matrix->size(); y++)
        {
            state.assign(x, y, _matrix->rockerState(x, y));
        }
    }

    return state;
}

void RockersLogic::rockerSwitched(int x, int y)
{
    qDebug() << "RockersLogic: rocker (" << x << "," << y << ") switched";
    for (int i = 0; i < _matrix->size(); i++)
    {
        _matrix->toggleRocker(i, y);
        _matrix->toggleRocker(x, i);
    }

    RockersState s = getState();
    emit newRockersStateSignal(s);
}
