#include "locksarray.h"
#include <QSpacerItem>

LocksArray::LocksArray(int size, QWidget *parent): QGridLayout(parent)
{
    setSpacing(3);
    for (int x = 0; x < size; x++)
    {
        setRowMinimumHeight(0, 16);
        setColumnMinimumWidth(x, 16);
        Lock * lock = new Lock(x);
        addWidget(lock, 0, x);
        _lockMap.append(lock);
    }
}

void LocksArray::locksSwitchedSlot(LocksState state)
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

