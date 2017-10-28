#include "locksmodel.h"

LocksModel::LocksModel(int size)
{
    _storage.resize(size);
}

void LocksModel::assign(int x, Lock::State value)
{
    _storage[x] = value;
}

Lock::State LocksModel::read(int x)
{
    return _storage[x];
}

