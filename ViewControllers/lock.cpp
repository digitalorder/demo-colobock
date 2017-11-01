#include "lock.h"

Lock::Lock(int x, QWidget *parent) : QPushButton(parent), _x(x)
{
    QIcon ico = QIcon();
    ico.addPixmap(QPixmap(":/images/resources/Locked.jpg"), QIcon::Normal, QIcon::On);
    ico.addPixmap(QPixmap(":/images/resources/Unlocked.jpg"), QIcon::Normal, QIcon::Off);
    setIcon(ico);
    setIconSize(QSize(20, 32));
    setEnabled(false);
    setCheckable(true);
    setMaximumHeight(32);
    setMaximumWidth(20);
}

void Lock::setState(Lock::State state)
{
    _state = state;
    if (_state == Lock::LOCKED)
    {
        setChecked(true);
    }
    else
    {
        setChecked(false);
    }
}

QDebug operator <<(QDebug os, const Lock::State &state)
{
    if (state == Lock::State::LOCKED)
    {
        os << "Locked";
    }
    else
    {
        os << "Unlocked";
    }
    return os;
}
