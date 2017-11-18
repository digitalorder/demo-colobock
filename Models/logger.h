#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QVector>
#include <iostream>
#include "primitivetypes.h"

class UserAction
{
    Coord _coord;

public:
    UserAction(): _coord(Coord()) {}
    UserAction(const Coord &coord): _coord(coord) {}
    UserAction(const UserAction& a) = default;
    UserAction(UserAction&& a) = default;
    UserAction& operator=(UserAction&& a) = default;
    UserAction& operator=(const UserAction& a) = default;

    Coord coord() const { return _coord; }
};

class Logger : public QObject, public Blockable
{
    Q_OBJECT
    QVector<UserAction> _move_history;
    QVector<UserAction> _undo_history;
    int _move_counter;
    bool _is_blocked;
    void incMoveCounter();
    void decMoveCounter();
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
    void revertAction(const Coord &coord, ActionSource source);
    void undoAvailablityChanged(bool enabled);
    void redoAvailablityChanged(bool enabled);
    void moveCounterChanged(int value);

public slots:
    void newUserAction(const Coord& coord, ActionSource source);
    void redoLastUserAction();
    void undoLastUserAction();
    void disable();
    void enable();
};

#endif // LOGGER_H
