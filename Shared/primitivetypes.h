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

class Coord
{
    int _x;
    int _y;
public:
    Coord(): _x(0), _y(0) {}
    Coord(int x, int y): _x(x), _y(y) {}
    Coord(const Coord& coord) = default;
    Coord(Coord&& coord) = default;
    Coord& operator=(Coord&& other) = default;
    Coord& operator=(const Coord& a) = default;

    int x() const { return _x; }
    int y() const { return _y; }
};

inline bool operator==(const Coord &lhs, const Coord &rhs)
{
    return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}

inline uint qHash(const Coord &key)
{
    return key.x() * 0x100 + key.y();
}

QDebug operator <<(QDebug os, const ActionSource& source);
QDebug operator <<(QDebug os, const SwitchingTiming& timing);
QDebug operator <<(QDebug os, const Coord& coord);

#endif // PRIMITIVETYPES_H
