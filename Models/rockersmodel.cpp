#include "rockersmodel.h"
#include <QTime>

RockersModel::RockersModel(int size): _size(size), _is_blocked(false)
{
    _storage.resize(size);
    std::for_each(_storage.begin(), _storage.end(), [size](QVector<Rocker::State> &s) { s.resize(size); } );
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

bool RockersModel::allRockersAreHorizontal()
{
    for (int x = 0; x < _size; x++)
    {
        for (int y = 0; y < _size; y++)
        {
            if (_storage[x][y] != Rocker::State::HORIZONTAL)
            {
                return false;
            }
        }
    }

    return true;
}

void RockersModel::shuffle(int seed)
{
    qsrand(seed);
    do
    {
        for (int i = 0; i < _size * _size; i++)
        {
            int x = qrand() % _size;
            int y = qrand() % _size;
            toggleRocker(x, y);
            emit toggleRockerWithoutLogic(x, y);
            emit toggleRockerWithLogic(x, y, ActionSource::MODEL);
        }
    } while (allRockersAreHorizontal());
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
    qDebug() << "RockersModel: catched a toggle at (" << x << "," << y << ") from" << source;
    toggleRocker(x, y);
    switch (source) {
    case ActionSource::CONTROLLER:
        // todo
        break;
    case ActionSource::LOGIC:
        emit toggleRockerWithoutLogic(x, y);
        break;
    case ActionSource::MODEL:
        Q_ASSERT(false); // This should never happen
        break;
    case ActionSource::UNDO_REDO:
        emit toggleRockerWithoutLogic(x, y);
        emit toggleRockerWithLogic(x, y, source);
        break;
    default:
        break;
    }
}
