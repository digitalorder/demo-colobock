#ifndef LOCKSARRAY_H
#define LOCKSARRAY_H

#include <QGridLayout>
#include <QVector>
#include "lock.h"
#include "locksmodel.h"
#include "settings.h"

class LocksArray : public QGridLayout
{
    Q_OBJECT

    QVector<Lock *> _lockMap;
    Lock * getLock(int x);
public:
    explicit LocksArray(const Settings & settings, QWidget *parent = 0);
    int size() { return _lockMap.size(); }
    void setState(int x, Lock::State state);
    void reinit(const Settings &settings);

public slots:
    void updateLocksStates(const LocksModel &state);
};

#endif // LOCKSARRAY_H
