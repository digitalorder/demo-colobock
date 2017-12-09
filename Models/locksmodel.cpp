#include "locksmodel.h"

LocksModel::LocksModel(const Settings &settings, QObject *parent): QObject(parent)
{
    _storage.resize(settings.matrixSize());
}

LocksModel::LocksModel(const LocksModel &obj)
{
    _storage = obj._storage;
}

Lock::State LocksModel::read(int x) const
{
    return _storage[x];
}

void LocksModel::lockStateChangedSlot(int x, Lock::State state)
{
    qDebug() << "LocksModel: catched update to lock " << x << " to " << state;
    _storage[x] = state;
}

QDebug operator <<(QDebug stream, const LocksModel &model)
{
    stream << "LocksModel(";
    for (int x = 0; x < model.size(); x++)
    {
         if (model.read(x) == Lock::State::LOCKED)
        {
            stream << "L";
        }
        else
        {
            stream << "U";
        }
    }
    stream << ")";
    return stream;
}
