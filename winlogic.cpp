#include "winlogic.h"
#include "lock.h"

WinLogic::WinLogic(int size, QObject *parent) :
    QObject(parent), _size(size)
{

}

bool WinLogic::winState(LocksState * state)
{
    for (int i = 0; i < _size; i++)
    {
        if (state->read(i) == Lock::LOCKED)
        {
            return false;
        }
    }

    return true;
}

void WinLogic::newSwitchesState(SwitchesState state)
{
    LocksState s(_size);
    for (int x = 0; x < _size; x++)
    {
        s.assign(x, Lock::UNLOCKED);
        for (int y = 0; y < _size; y++)
        {
             if (state.read(x, y))
             {
                 s.assign(x, Lock::LOCKED);
                 break;
             }
        }
    }

    emit newLocksState(s);
    if (winState(&s)) {
        emit win();
    }
}
