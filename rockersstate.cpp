#include "rockersstate.h"

RockersState::RockersState(int size): _size(size)
{
    _storage.resize(size);
    for (int i = 0; i < size; i++)
    {
        _storage[i].resize(size);
    }
}

int RockersState::getIndex(int x, int y)
{
    int result = x + y * _size;
    return result;
}

void RockersState::assign(int x, int y, Rocker::State value)
{
    _storage[x][y] = value;
}

Rocker::State RockersState::read(int x, int y)
{
    return _storage[x][y];
}
