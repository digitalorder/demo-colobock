#include "winlogic.h"
#include "lock.h"

WinLogic::WinLogic(QObject *parent) :
    QObject(parent)
{

}

int cnt = 0;

void WinLogic::newLocksStateSlot(LocksState state)
{
//    for (int i = 0; i < state.size(); i++)
//    {
//        if (state.read(i) == Lock::LOCKED)
//        {
//            return;
//        }
//    }

//    emit win();

    if (cnt++ == 5)
    {
        emit win();
    }
}
