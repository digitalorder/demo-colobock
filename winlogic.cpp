#include "winlogic.h"
#include "lock.h"

WinLogic::WinLogic(QObject *parent) :
    QObject(parent)
{

}

static int call_counter = 0;

void WinLogic::newLocksStateSlot(LocksState state)
{
//    for (int i = 0; i < state.size(); i++)
//    {
//        if (state.read(i) == Lock::LOCKED)
//        {
//            return;
//        }
//    }
//
//    emit win();

    if (call_counter++ == 5)
    {
        call_counter = 0;
        emit win();
    }
}
