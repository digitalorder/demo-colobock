#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QVector>
#include <iostream>
#include "primitivetypes.h"

class UserAction
{
    int _x;
    int _y;

public:
    UserAction(): _x(0), _y(0) {}
    UserAction(int x, int y): _x(x), _y(y) {}
    UserAction(const UserAction &a) { _x = a.x(); _y = a.y(); }

    int x() const { return _x; }
    int y() const { return _y; }
};

class Logger : public QObject, public Blockable
{
    Q_OBJECT
    QVector<UserAction> _move_history;
    QVector<UserAction> _undo_history;
    int _move_counter;
    bool _is_blocked;
    void updateMoveCounter();
    void resetMoveCounter();
    void emitAvailabilityNotifications();
    void emitNoAvailabilityNotifications();
    void moveAction(QVector<UserAction> &to, QVector<UserAction> &from);

public:
    explicit Logger();
    virtual bool isBlocked() { return _is_blocked; }
    virtual void block() { _is_blocked = true; emitNoAvailabilityNotifications(); }
    virtual void unblock() { _is_blocked = false; emitAvailabilityNotifications(); }

signals:
    void revertAction(int x, int y, ActionSource source);
    void undoAvailablityChanged(bool enabled);
    void redoAvailablityChanged(bool enabled);
    void moveCounterChanged(int value);

public slots:
    void newUserAction(int x, int y, ActionSource source);
    void redoLastUserAction();
    void undoLastUserAction();
    void disable();
    void enable();
};

#endif // LOGGER_H
