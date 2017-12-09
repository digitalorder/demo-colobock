#include "logger.h"
#include <QDebug>

void Logger::incMoveCounter()
{
    _move_counter++;
    emit moveCounterChanged(_move_counter);
}

void Logger::decMoveCounter()
{
    _move_counter--;
    emit moveCounterChanged(_move_counter);
}

void Logger::resetMoveCounter()
{
    _move_counter = 0;
    emit moveCounterChanged(_move_counter);
}

void Logger::emitAvailabilityNotifications()
{
    emit undoAvailablityChanged(!_move_history.empty());
    emit redoAvailablityChanged(!_undo_history.empty());
}

void Logger::emitNoAvailabilityNotifications()
{
    emit undoAvailablityChanged(false);
    emit redoAvailablityChanged(false);
}

void Logger::newUserAction(const Coord &coord, ActionSource source)
{
    if (source == ActionSource::CONTROLLER)
    {
        incMoveCounter();
        _move_history.append(UserAction(coord));
        _undo_history.clear();
        emitAvailabilityNotifications();
    }
}

void Logger::moveAction(UserActions &to, UserActions &from)
{
    UserAction a = from.takeLast();
    to.append(a);
    emitAvailabilityNotifications();
    emit revertAction(a.coord(), ActionSource::UNDO_REDO);
}

void Logger::redoLastUserAction()
{
    incMoveCounter();
    moveAction(_move_history, _undo_history);
}

void Logger::undoLastUserAction()
{
    decMoveCounter();
    moveAction(_undo_history, _move_history);
}

void Logger::unblock()
{
    if (_full_undo_in_progress && _move_counter)
    {
        undoLastUserAction();
    }
    else
    {
        _full_undo_in_progress = false;
        _is_blocked = false;
        emitAvailabilityNotifications();
    }
}

void Logger::undoAllUserActions()
{
    _full_undo_in_progress = true;
    undoLastUserAction();
}

void Logger::disable()
{
    emitNoAvailabilityNotifications();
}

void Logger::enable()
{
    emitAvailabilityNotifications();
}
