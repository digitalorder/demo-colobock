#include "switchesstate.h"
#include <QDebug>

SwitchesState::SwitchesState(int size): _size(size)
{
    _storage.resize(size);
    for (int i = 0; i < size; i++)
    {
        _storage[i].resize(size);
    }
}

int SwitchesState::getIndex(int x, int y)
{
    int result = x + y * _size;
    Q_ASSERT(result < _storage.size());
    return result;
}

void SwitchesState::assign(int x, int y, bool value)
{
    _storage[x][y] = value;
}

bool SwitchesState::read(int x, int y)
{
    return _storage[x][y];
}
