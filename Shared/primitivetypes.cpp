#include "primitivetypes.h"

QDebug operator <<(QDebug os, const ActionSource& source)
{
    switch (source)
    {
    case CONTROLLER:
        os << "CONTROLLER";
        break;
    case LOGIC:
        os << "LOGIC";
        break;
    case UNDO_REDO:
        os << "UNDO or REDO";
        break;
    case MODEL:
        os << "MODEL";
        break;
    default:
        os << "Unknown";
        break;
    }

    return os;
}

QDebug operator <<(QDebug os, const SwitchingTiming &timing)
{
    switch (timing)
    {
    case DELAYED:
        os << "DELAYED";
        break;
    case INSTANT:
        os << "INSTANT";
        break;
    default:
        os << "Unknown";
        break;
    }

    return os;
}

QDebug operator <<(QDebug os, const Coord &coord)
{
    return os << "(x =" << coord.x() << ", y =" << coord.y() << ")";
}
