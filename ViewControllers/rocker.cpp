#include "rocker.h"

void Rocker::clickedEventCatcher(bool)
{
    emit clickedOverride(_x, _y);
}

void Rocker::setState(State state)
{
    bool boolRepresentation = state == VERTICAL;
    setChecked(boolRepresentation);
}

Rocker::State Rocker::getState()
{
    if (isChecked())
    {
        return VERTICAL;
    }
    else
    {
        return HORIZONTAL;
    }
}

void Rocker::toggleState()
{
    if (getState() == HORIZONTAL)
    {
        setState(VERTICAL);
    }
    else
    {
        setState(HORIZONTAL);
    }
}

Rocker::Rocker(int x, int y, State state, QWidget *parent) : QPushButton(parent), _x(x), _y(y)
{
    QIcon ico = QIcon();
    ico.addPixmap(QPixmap(":/images/resources/Vertical.jpg"), QIcon::Normal, QIcon::On);
    ico.addPixmap(QPixmap(":/images/resources/Vertical.jpg"), QIcon::Disabled, QIcon::On);
    ico.addPixmap(QPixmap(":/images/resources/Horizontal.jpg"),QIcon::Normal,QIcon::Off);
    ico.addPixmap(QPixmap(":/images/resources/Horizontal.jpg"),QIcon::Disabled,QIcon::Off);
    setIcon(ico);
    setIconSize(QSize(32, 32));
    setFixedSize(QSize(32, 32));
    setCheckable(true);
    setState(state);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(this, &Rocker::clicked, this, &Rocker::clickedEventCatcher);
}
