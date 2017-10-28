#include "winlogic.h"
#include "lock.h"

WinLogic::WinLogic(QObject *parent) :
    QObject(parent)
{

}

void WinLogic::newLocksStateSlot(LocksModel state)
{
    for (int i = 0; i < state.size(); i++)
    {
        if (state.read(i) == Lock::LOCKED)
        {
            return;
        }
    }

    emit win();
}
