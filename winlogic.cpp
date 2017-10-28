#include "winlogic.h"
#include "lock.h"

WinLogic::WinLogic(QObject *parent) :
    QObject(parent), _is_blocked(false)
{

}

void WinLogic::newLocksStateSlot(LocksModel state)
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
