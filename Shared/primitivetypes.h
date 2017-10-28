#ifndef PRIMITIVETYPES_H
#define PRIMITIVETYPES_H

#include <QDebug>

enum ActionSource
{
    CONTROLLER,
    LOGIC,
    UNDO_REDO,
    MODEL
};

enum SwitchingTiming
{
    DELAYED,
    INSTANT
};

class Blockable
{
public:
    Blockable() {}
    virtual bool isBlocked() = 0;
    virtual void block() = 0;
    virtual void unblock() = 0;
};

QDebug operator <<(QDebug os, const ActionSource& source);
QDebug operator <<(QDebug os, const SwitchingTiming& timing);

#endif // PRIMITIVETYPES_H
