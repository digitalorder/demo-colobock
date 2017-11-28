#ifndef LOCK_H
#define LOCK_H

#include "settings.h"
#include <QPushButton>
#include <QDebug>

class Lock : public QPushButton
{
    Q_OBJECT

public:
    enum State
    {
        LOCKED,
        UNLOCKED
    };

    explicit Lock(int x, const Settings &settings, QWidget *parent = 0);
    State state() { return _state; }

private:
    State _state;
    int _x;

signals:

public slots:
    void setState(State);
};

QDebug operator <<(QDebug os, const Lock::State& state);


#endif // LOCK_H
