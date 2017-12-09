#ifndef WINLOGIC_H
#define WINLOGIC_H

#include <QObject>
#include "rockersmodel.h"
#include "locksmodel.h"

class WinLogic : public QObject, public Blockable
{
    Q_OBJECT
    bool _is_blocked;

public:
    explicit WinLogic(QObject * parent = 0): QObject(parent), _is_blocked(false) { }
    virtual bool isBlocked() { return _is_blocked; }
    virtual void block() { _is_blocked = true; }
    virtual void unblock() { _is_blocked = false; }

signals:
    void win();

public slots:
    void newLocksStateSlot(const LocksModel &state);
};

#endif // WINLOGIC_H
