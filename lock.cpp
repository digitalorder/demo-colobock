#include "lock.h"

Lock::Lock(int x, QWidget *parent) : QPushButton(parent), _x(x)
{
    setEnabled(false);
    setText("?");
}

void Lock::setState(Lock::State state)
{
    _state = state;
    if (_state == Lock::LOCKED)
    {
        setText("L");
    }
    else
    {
        setText("U");
    }
}
