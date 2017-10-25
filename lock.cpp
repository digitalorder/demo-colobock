#include "lock.h"

Lock::Lock(int x, QWidget *parent) : QPushButton(parent), _x(x)
{
    QIcon *ico = new QIcon();
    ico->addPixmap(QPixmap(":/images/resources/Locked.jpg"), QIcon::Normal, QIcon::On);
    ico->addPixmap(QPixmap(":/images/resources/Unlocked.jpg"),QIcon::Normal,QIcon::Off);
    setIcon(*ico);
    setIconSize(QSize(20, 32));
    setEnabled(false);
    setCheckable(true);
//    setText("?");
    setMaximumHeight(32);
    setMaximumWidth(20);
}

void Lock::setState(Lock::State state)
{
    _state = state;
    if (_state == Lock::LOCKED)
    {
//        setText("L");
        setChecked(true);
    }
    else
    {
//        setText("U");
        setChecked(false);
    }
}
