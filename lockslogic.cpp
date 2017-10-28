#include "lockslogic.h"

LocksLogic::LocksLogic(LocksArray *locks, QObject *parent) : QObject(parent), _locks(locks)
{

}

void LocksLogic::newRockersStateSlot(const RockersModel &state)
{
    qDebug() << "LocksLogic: received new model:" << state;
    LocksModel locksState(_locks->size());
    for (int y = 0; y < _locks->size(); y++)
    {
        Lock::State lockState = Lock::UNLOCKED;
        for (int x = 0; x < _locks->size(); x++)
        {
             if (state.read(x, y))
             {
                 lockState = Lock::LOCKED;
                 break;
             }
        }
        _locks->setState(y, lockState);
        locksState.assign(y, lockState);
    }

    emit newLocksStateSignal(locksState);
}
