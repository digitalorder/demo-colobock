#include "logger.h"
#include <QDebug>

Logger::Logger(QObject *parent) : QObject(parent), _move_counter(0)
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

void Logger::newUserAction(int x, int y)
{
    updateMoveCounter();
    _move_history.append(UserAction(x, y));
    _undo_history.clear();
    emitAvailabilityNotifications();
}

void Logger::redoLastUserAction()
{
    updateMoveCounter();
    UserAction a = _undo_history.takeLast();
    _move_history.append(a);
    emitAvailabilityNotifications();
    emit revertAction(a.x(), a.y());
}

void Logger::undoLastUserAction()
{
    updateMoveCounter();
    UserAction a = _move_history.takeLast();
    _undo_history.append(a);
    emitAvailabilityNotifications();
    emit revertAction(a.x(), a.y());
}

void Logger::newGameAction(int matrixSize)
{
    (void)matrixSize;
    resetMoveCounter();
    _undo_history.clear();
    _move_history.clear();
    emitAvailabilityNotifications();
}

void Logger::disable()
{
    emitNoAvailabilityNotifications();
}

void Logger::enable()
{
    emitAvailabilityNotifications();
}
