#ifndef WINLOGIC_H
#define WINLOGIC_H

#include <QObject>
#include "switchesstate.h"
#include "locksstate.h"

class WinLogic : public QObject
{
    Q_OBJECT
    int _size;
    bool winState(LocksState * state);
public:
    explicit WinLogic(int size, QObject *parent = 0);

signals:
    void newLocksState(LocksState state);
    void win();

public slots:
    void newSwitchesState(SwitchesState state);
};

#endif // WINLOGIC_H
