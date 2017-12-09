#include "winlogic.h"
#include "lock.h"

void WinLogic::newLocksStateSlot(const LocksModel & state)
{
    qDebug() << "WinLogic: received new model: " << state;
    if (isBlocked())
    {
        qDebug() << "Ignoring, because blocked";
        return;
    }
    for (int i = 0; i < state.size(); i++)
    {
        if (state.read(i) == Lock::LOCKED)
        {
            return;
        }
    }

    emit win();
}
