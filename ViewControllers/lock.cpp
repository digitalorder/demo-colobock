#include "lock.h"

Lock::Lock(int x, const Settings &settings, QWidget *parent) : QPushButton(parent), _x(x)
{
    QIcon ico = QIcon();
    ico.addPixmap(QPixmap(settings.resourceFolder() + "Locked.png"), QIcon::Disabled, QIcon::On);
    ico.addPixmap(QPixmap(settings.resourceFolder() + "Unlocked.png"), QIcon::Disabled, QIcon::Off);
    setIcon(ico);
    setIconSize(QSize(19, 32));
    setEnabled(false);
    setCheckable(true);
    setMaximumHeight(32);
    setMaximumWidth(19);
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
