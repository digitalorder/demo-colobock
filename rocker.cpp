#include "rocker.h"

QString Rocker::stateToText()
{
    if (state == Rocker::HORIZONTAL)
    {
        return QString("|");
    }
    else
    {
        return QString("-");
    }
}

void Rocker::clickedEventCatcher(bool)
{
    emit clickedOverride(x, y);
}

Rocker::Rocker(int x, int y, QWidget *parent) : QPushButton(parent), x(x), y(y)
{
    setMaximumHeight(32);
    setMaximumWidth(32);
    setText(stateToText());

    connect(this, &Rocker::clicked, this, &Rocker::clickedEventCatcher);
}

