#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QVector>
#include <iostream>

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

class Logger : public QObject
{
    Q_OBJECT
    QVector<UserAction> _move_history;
    QVector<UserAction> _undo_history;
    int _move_counter;
    void updateMoveCounter();
    void resetMoveCounter();
    void emitAvailabilityNotifications();

public:
    explicit Logger(QObject *parent = 0);

signals:
    void revertAction(int x, int y);
    void undoAvailablityChanged(bool enabled);
    void redoAvailablityChanged(bool enabled);
    void moveCounterChanged(int value);

public slots:
    void newUserAction(int x, int y);
    void redoLastUserAction();
    void undoLastUserAction();
    void newGameAction(int matrixSize);
};

#endif // LOGGER_H
