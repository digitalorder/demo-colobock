#include "lockslogic.h"

LocksLogic::LocksLogic(LocksArray *locks, QObject *parent) : QObject(parent), _locks(locks)
{

}

void LocksLogic::newGameAction(int matrixSize)
{
    _locks->reinit(matrixSize);
}

void LocksLogic::newRockersStateSlot(RockersState state)
{
    LocksState locksState(_locks->size());
    for (int x = 0; x < _locks->size(); x++)
    {
        Lock::State lockState = Lock::UNLOCKED;
        for (int y = 0; y < _locks->size(); y++)
        {
             if (state.read(x, y))
             {
                 lockState = Lock::LOCKED;
                 break;
             }
        }
        _locks->setState(x, lockState);
        locksState.assign(x, lockState);
    }

    emit newLocksStateSignal(locksState);
}
