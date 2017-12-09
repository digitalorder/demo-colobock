#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QVector>
#include <iostream>
#include "useraction.h"
#include "primitivetypes.h"

class Logger : public QObject, public Blockable
{
    Q_OBJECT
    UserActions _move_history;
    UserActions _undo_history;
    int _move_counter;
    bool _is_blocked;
    bool _full_undo_in_progress;
    void incMoveCounter();
    void decMoveCounter();
    void resetMoveCounter();
    void emitAvailabilityNotifications();
    void emitNoAvailabilityNotifications();
    void moveAction(UserActions &to, UserActions &from);

public:
    explicit Logger(QObject * parent = 0): QObject(parent), _move_counter(0), _is_blocked(false), _full_undo_in_progress(false) { }
    virtual bool isBlocked() { return _is_blocked; }
    virtual void block() { _is_blocked = true; emitNoAvailabilityNotifications(); }
    virtual void unblock();

signals:
    void revertAction(const Coord &coord, ActionSource source);
    void revertActions(const UserActions &actions);
    void undoAvailablityChanged(bool enabled);
    void redoAvailablityChanged(bool enabled);
    void moveCounterChanged(int value);

public slots:
    void newUserAction(const Coord& coord, ActionSource source);
    void redoLastUserAction();
    void undoLastUserAction();
    void undoAllUserActions();
    void disable();
    void enable();
};

#endif // LOGGER_H
