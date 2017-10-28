#ifndef LOCKSSTATE_H
#define LOCKSSTATE_H

#include <QDebug>
#include "lock.h"

class LocksModel
{
    QVector<Lock::State> _storage;

public:
    LocksModel(int size);
    int size() const { return _storage.size(); }
    void assign(int x, Lock::State value);
    Lock::State read(int x) const;
};

QDebug operator <<(QDebug stream, const LocksModel &model);

#endif // LOCKSSTATE_H
