#include "locksarray.h"
#include <QSpacerItem>

LocksArray::LocksArray(int size, QWidget *parent): QGridLayout(parent)
{
    setSpacing(3);
    reinit(size);
}

void LocksArray::locksSwitchedSlot(LocksModel state)
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

void LocksArray::reinit(int matrixSize)
{
    for (int x = 0; x < matrixSize; x++)
    {
        setRowMinimumHeight(0, 16);
        setColumnMinimumWidth(x, 16);
        Lock * lock = new Lock(x);
        addWidget(lock, 0, x);
        _lockMap.append(lock);
    }
}

