#ifndef SWITCHESSTATE_H
#define SWITCHESSTATE_H

#include <QVector>

class SwitchesState
{
    int _size;
    QVector<QVector<bool>> _storage;
    int getIndex(int x, int y);

public:
    SwitchesState(int size);
    void assign(int x, int y, bool value);
    bool read(int x, int y);
};

#endif // SWITCHESSTATE_H
