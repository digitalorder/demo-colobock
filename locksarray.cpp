#include "locksarray.h"

LocksArray::LocksArray(int size, QWidget *parent): QGridLayout(parent)
{
    setSpacing(0);
    for (int x = 0; x < size; x++)
    {
        setRowMinimumHeight(0, 32);
        setColumnMinimumWidth(x, 32);
        Lock * lock = new Lock(x);
        addWidget(lock, 0, x);
        _lockMap.append(lock);
    }
}

void LocksArray::locksSwitched(LocksState state)
{
    for (int x = 0; x < _lockMap.size(); x++)
    {
        _lockMap.at(x)->setState(state.read(x));
    }
}

Lock::State LocksArray::lockState(int x)
{
    return _lockMap.at(x)->state();
}

