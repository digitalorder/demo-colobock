#ifndef USERACTION_H
#define USERACTION_H

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

typedef QVector<UserAction> UserActions;

#endif // USERACTION_H
