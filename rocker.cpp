#include "rocker.h"

void Rocker::clickedEventCatcher(bool)
{
    emit clickedOverride(_x, _y);
}

void Rocker::toggledEventCatcher(bool state)
{
    if (state)
    {
        setText("|");
    }
    else
    {
        setText("-");
    }
}

void Rocker::setState(State state)
{
    bool boolRepresentation = state == VERTICAL;
    setChecked(boolRepresentation);
    toggledEventCatcher(boolRepresentation);
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
    setMaximumHeight(32);
    setMaximumWidth(32);
    setMinimumHeight(32);
    setMinimumWidth(32);
    setCheckable(true);
    setState(state);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(this, &Rocker::clicked, this, &Rocker::clickedEventCatcher);
    connect(this, &Rocker::toggled, this, &Rocker::toggledEventCatcher);
}
