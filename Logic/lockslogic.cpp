#include "lockslogic.h"

LocksLogic::LocksLogic(int size, QObject *parent) : QObject(parent), _size(size)
{

}

void LocksLogic::newRockersStateSlot(const RockersModel &state)
{
    qDebug() << "LocksLogic: received new model:" << state;
    emit blockControllers();
    for (int y = 0; y < _size; y++)
    {
        Lock::State lockState = Lock::UNLOCKED;
        for (int x = 0; x < _size; x++)
        {
             if (state.read(x, y))
             {
                 lockState = Lock::LOCKED;
                 break;
             }
        }
        emit lockStateChangedSignal(y, lockState);
    }

    emit unblockControllers();
}