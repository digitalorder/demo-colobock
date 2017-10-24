#ifndef LOCKSSTATE_H
#define LOCKSSTATE_H

#include "lock.h"

class LocksState
{
    QVector<Lock::State> _storage;

public:
    LocksState(int size);
    void assign(int x, Lock::State value);
    Lock::State read(int x);
};

#endif // LOCKSSTATE_H
