#include "rockerslogic.h"

RockersLogic::RockersLogic(RockersMatrix *matrix, QWidget *parent) : QObject(parent)
{
    _matrix = matrix;
    emitNewRockersStateSignal();
}

void RockersLogic::emitNewRockersStateSignal()
{
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
            state.assign(x, y, _matrix->rockerState(y, x));
        }
    }

    return state;
}

void RockersLogic::toggleRelatedRockers(int x, int y)
{
    int delta = 1;
    int toggled_count;
    do
    {
        toggled_count = 0;
        if (x - delta >= 0)
        {
            _matrix->toggleRocker(x - delta, y);
            toggled_count++;
        }
        if (x + delta < _matrix->size())
        {
            _matrix->toggleRocker(x + delta, y);
            toggled_count++;
        }
        if (y - delta >= 0)
        {
            _matrix->toggleRocker(x, y - delta);
            toggled_count++;
        }
        if (y + delta < _matrix->size())
        {
            _matrix->toggleRocker(x, y + delta);
            toggled_count++;
        }
        delta++;
    } while (toggled_count > 0);
}

void RockersLogic::rockerSwitchedSlot(int x, int y)
{
    toggleRelatedRockers(x, y);
    emit rockerSwitchedSignal(x, y);
    emitNewRockersStateSignal();
}

void RockersLogic::revertAction(int x, int y)
{
    toggleRelatedRockers(x, y);
    _matrix->toggleRocker(x, y);
    emitNewRockersStateSignal();
}

void RockersLogic::newGameAction(int matrixSize)
{
    if (matrixSize == _matrix->size())
    {
        _matrix->shuffle();
    }
    else
    {
        _matrix->reinit(matrixSize);
    }
    emitNewRockersStateSignal();
}
