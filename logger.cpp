#include "logger.h"
#include <QDebug>

Logger::Logger(QObject *parent) : QObject(parent), _move_counter(0)
{

}

std::ostream &operator<<(std::ostream& os, const Logger& l)
{
    os << "Log includes: ";
    for (auto i = l._undo_history.begin(); i != l._undo_history.end(); ++i)
    {
        os << "[" << i->x() << ", " << i->y() << "]";
    }
    return os;
}

void Logger::updateMoveCounter()
{
    _move_counter++;
    emit moveCounterChanged(_move_counter);
}

void Logger::newUserAction(int x, int y)
{
    updateMoveCounter();
    _move_history.append(UserAction(x, y));
    _undo_history.clear();
    emit undoAvailablityChanged(!_move_history.empty());
    emit redoAvailablityChanged(!_undo_history.empty());
    qDebug() << "Logger lengths: " << _move_history.size();
}

void Logger::redoLastUserAction()
{
    updateMoveCounter();
    UserAction a = _undo_history.takeLast();
    _move_history.append(a);
    emit undoAvailablityChanged(!_move_history.empty());
    emit redoAvailablityChanged(!_undo_history.empty());
    emit revertAction(a.x(), a.y());
}

void Logger::undoLastUserAction()
{
    updateMoveCounter();
    UserAction a = _move_history.takeLast();
    _undo_history.append(a);
    emit undoAvailablityChanged(!_move_history.empty());
    emit redoAvailablityChanged(!_undo_history.empty());
    emit revertAction(a.x(), a.y());
}
