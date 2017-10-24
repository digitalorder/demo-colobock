#include "locksstate.h"

LocksState::LocksState(int size)
{
    _storage.resize(size);
}

void LocksState::assign(int x, Lock::State value)
{
    _storage[x] = value;
}

Lock::State LocksState::read(int x)
{
    return _storage[x];
}

