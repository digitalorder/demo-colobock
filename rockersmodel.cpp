#include "rockersmodel.h"
#include <QTime>

RockersModel::RockersModel(int size): _size(size), _is_blocked(false)
{
    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
    _storage.resize(size);
    for (int i = 0; i < size; i++)
    {
        _storage[i].resize(size);
    }
}

RockersModel::RockersModel(const RockersModel &obj)
{
    _storage = obj._storage;
    _size = obj._size;
}

Rocker::State RockersModel::read(int x, int y) const
{
    return _storage[x][y];
}

QDebug operator<<(QDebug stream, const RockersModel &model)
{
    stream << "RockersModel(" << endl;
    for (int x = 0; x < model.size(); x++)
    {
        for (int y = 0; y < model.size(); y++)
        {
            if (model.read(x, y) == Rocker::State::HORIZONTAL)
            {
                stream << "-";
            }
            else
            {
                stream << "|";
            }
        }
        stream << endl;
    }
    stream << ")";
    return stream;
}

void RockersModel::toggleRocker(int x, int y)
{
    if (_storage[x][y] == Rocker::State::HORIZONTAL)
    {
        _storage[x][y] = Rocker::State::VERTICAL;
    }
    else
    {
        _storage[x][y] = Rocker::State::HORIZONTAL;
    }
}

void RockersModel::rockerToggled(int x, int y, ActionSource source)
{
    qDebug() << "RockersModel: catched a toggle at (" << x << "," << y << ") from " << source;
    toggleRocker(x, y);
    if (source == ActionSource::LOGIC)
    {
        emit toggleRockerWithoutLogic(x, y);
    }
    if (source == ActionSource::UNDO_REDO)
    {
        emit toggleRockerWithoutLogic(x, y);
        emit toggleRockerWithLogic(x, y);
    }
}
