#include "locksarray.h"
#include <QSpacerItem>

LocksArray::LocksArray(int size, bool darkTheme, QWidget *parent): QGridLayout(parent)
{
    setSpacing(4);
    reinit(size, darkTheme);
}

void LocksArray::updateLocksStates(const LocksModel &state)
{
    for (int x = 0; x < _lockMap.size(); x++)
    {
        _lockMap.at(x)->setState(state.read(x));
    }
}

void LocksArray::setState(int x, Lock::State state)
{
    _lockMap.at(x)->setState(state);
}

void LocksArray::reinit(int matrixSize, bool darkTheme)
{
    for (int x = 0; x < matrixSize; x++)
    {
        setRowMinimumHeight(0, 16);
        setColumnMinimumWidth(x, 16);
        Lock * lock = new Lock(x, darkTheme);
        addWidget(lock, 0, x);
        _lockMap.append(lock);
    }
}

