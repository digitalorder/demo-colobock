#ifndef LOCKSSTATE_H
#define LOCKSSTATE_H

#include "lock.h"

class LocksModel
{
    QVector<Lock::State> _storage;

public:
    LocksModel(int size);
    int size() { return _storage.size(); }
    void assign(int x, Lock::State value);
    Lock::State read(int x);
};

#endif // LOCKSSTATE_H
