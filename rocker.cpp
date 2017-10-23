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

Rocker::Rocker(QWidget *parent) : QPushButton(parent)
{
    setMaximumWidth(height());
    setText(stateToText());
}
