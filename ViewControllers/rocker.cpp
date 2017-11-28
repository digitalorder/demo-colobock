#include "rocker.h"

void Rocker::clickedEventCatcher(bool)
{
    emit clickedOverride(_coord);
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

Rocker::Rocker(const Coord &coord, State state, bool darkTheme, QWidget *parent) : QPushButton(parent), _coord(coord)
{
    QIcon ico = QIcon();
    QString resourceFolder = darkTheme ? QString(":/images/resources/Dark/") : QString(":/images/resources/Light/");
    ico.addPixmap(QPixmap(resourceFolder + "Vertical.png"), QIcon::Normal, QIcon::On);
    ico.addPixmap(QPixmap(resourceFolder + "Vertical.png"), QIcon::Disabled, QIcon::On);
    ico.addPixmap(QPixmap(resourceFolder + "Horizontal.png"),QIcon::Normal,QIcon::Off);
    ico.addPixmap(QPixmap(resourceFolder + "Horizontal.png"),QIcon::Disabled,QIcon::Off);
    setIcon(ico);
    setIconSize(QSize(32, 32));
    setFixedSize(QSize(32, 32));
    setCheckable(true);
    setState(state);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(this, &Rocker::clicked, this, &Rocker::clickedEventCatcher);
}
