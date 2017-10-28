#ifndef LOCKSARRAY_H
#define LOCKSARRAY_H

#include <QGridLayout>
#include <QVector>
#include "lock.h"
#include "locksmodel.h"

class LocksArray : public QGridLayout
{
    Q_OBJECT

    QVector<Lock *> _lockMap;
    Lock * getLock(int x);
public:
    explicit LocksArray(int size = 2, QWidget *parent = 0);
    int size() { return _lockMap.size(); }
    void setState(int x, Lock::State state);
    void reinit(int matrixSize);

public slots:
    void updateLocksStates(const LocksModel &state);
};

#endif // LOCKSARRAY_H
