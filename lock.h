#ifndef LOCK_H
#define LOCK_H

#include <QPushButton>

class Lock : public QPushButton
{
    Q_OBJECT

public:
    enum State
    {
        LOCKED,
        UNLOCKED
    };

    explicit Lock(int x, QWidget *parent = 0);
    State state() { return _state; }

private:
    State _state;
    int _x;

signals:

public slots:
    void setState(State);
};

#endif // LOCK_H
