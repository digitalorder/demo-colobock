#ifndef ROCKER_H
#define ROCKER_H

#include <QPushButton>

class Rocker : public QPushButton
{
    Q_OBJECT
    const int _x;
    const int _y;

    QString stateToText();
private slots:
    void clickedEventCatcher(bool);
    void toggledEventCatcher(bool);

public:
    enum State
    {
        HORIZONTAL,
        VERTICAL
    };

    explicit Rocker(int x, int y, State state, QWidget *parent = 0);
    Rocker::State getState();
    void toggleState();

private:
    void setState(State state);

signals:
    void clickedOverride(int x, int y);

public slots:
};

#endif // ROCKER_H
