#ifndef LOCKSMODEL_H
#define LOCKSMODEL_H

#include <QObject>
#include <QDebug>
#include "lock.h"
#include "primitivetypes.h"
#include "settings.h"

class LocksModel: public QObject, public Blockable
{
    Q_OBJECT
    QVector<Lock::State> _storage;
    bool _is_blocked;

public:
    LocksModel(const Settings & settings, QObject *parent = 0);
    LocksModel(const LocksModel &obj);
    int size() const { return _storage.size(); }
    Lock::State read(int x) const;
    virtual bool isBlocked() { return _is_blocked; }
    virtual void block() { _is_blocked = true; }
    virtual void unblock() { _is_blocked = false; emit locksStateChangedSignal(LocksModel(*this)); }

signals:
    void locksStateChangedSignal(const LocksModel & model);

public slots:
    void lockStateChangedSlot(int x, Lock::State state);
};

QDebug operator <<(QDebug stream, const LocksModel &model);

#endif // LOCKSMODEL_H
