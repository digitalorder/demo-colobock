#ifndef ROCKER_H
#define ROCKER_H

#include "primitivetypes.h"
#include <QPushButton>

class Rocker : public QPushButton
{
    Q_OBJECT
    const Coord _coord;

    QString stateToText();
private slots:
    void clickedEventCatcher(bool);

public:
    enum State
    {
        HORIZONTAL,
        VERTICAL
    };

    explicit Rocker(const Coord &coord, State state, bool darkTheme, QWidget *parent = 0);
    Rocker::State getState();
    void toggleState();
    void setState(State state);

signals:
    void clickedOverride(const Coord& coord);

public slots:
};

#endif // ROCKER_H
