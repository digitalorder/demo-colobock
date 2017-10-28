#include "locksmodel.h"

LocksModel::LocksModel(int size)
{
    _storage.resize(size);
}

void LocksModel::assign(int x, Lock::State value)
{
    _storage[x] = value;
}

Lock::State LocksModel::read(int x) const
{
    return _storage[x];
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
