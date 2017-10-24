#include "lock.h"

Lock::Lock(int x, QWidget *parent) : QPushButton(parent), _x(x)
{
    setEnabled(false);
    setText("?");
    setMaximumHeight(32);
    setMaximumWidth(16);
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
