#include "logger.h"
#include <QDebug>

Logger::Logger(): _move_counter(0), _is_blocked(false)
{
}

void Logger::updateMoveCounter()
{
    _move_counter++;
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

void Logger::newUserAction(int x, int y, ActionSource source)
{
    if (source == ActionSource::CONTROLLER)
    {
        updateMoveCounter();
        _move_history.append(UserAction(x, y));
        _undo_history.clear();
        emitAvailabilityNotifications();
    }
}

void Logger::moveAction(QVector<UserAction> &to, QVector<UserAction> &from)
{
    updateMoveCounter();
    UserAction a = from.takeLast();
    to.append(a);
    emitAvailabilityNotifications();
    emit revertAction(a.x(), a.y(), ActionSource::UNDO_REDO);
}

void Logger::redoLastUserAction()
{
    moveAction(_move_history, _undo_history);
}

void Logger::undoLastUserAction()
{
    moveAction(_undo_history, _move_history);
}

void Logger::disable()
{
    emitNoAvailabilityNotifications();
}

void Logger::enable()
{
    emitAvailabilityNotifications();
}
