#include "rocker.h"

QString Rocker::stateToText()
{
    if (isChecked())
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
    emit clickedOverride(_x, _y);
}

void Rocker::toggledEventCatcher(bool checked)
{
    if (checked)
    {
        setText("|");
    }
    else
    {
        setText("-");
    }
}

Rocker::Rocker(int x, int y, bool state, QWidget *parent) : QPushButton(parent), _x(x), _y(y)
{
    setMaximumHeight(32);
    setMaximumWidth(32);
    setText(stateToText());
    setCheckable(true);
    setChecked(state);
    toggledEventCatcher(state);

    connect(this, &Rocker::clicked, this, &Rocker::clickedEventCatcher);
    connect(this, &Rocker::toggled, this, &Rocker::toggledEventCatcher);
}

