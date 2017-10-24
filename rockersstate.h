#ifndef SWITCHESSTATE_H
#define SWITCHESSTATE_H

#include <QVector>
#include "rocker.h"

class RockersState
{
    int _size;
    QVector<QVector<Rocker::State>> _storage;
    int getIndex(int x, int y);

public:
    RockersState(int size);
    void assign(int x, int y, Rocker::State value);
    Rocker::State read(int x, int y);
};

#endif // SWITCHESSTATE_H
