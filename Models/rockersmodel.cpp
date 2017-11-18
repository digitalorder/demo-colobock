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

Rocker::State RockersModel::read(const Coord &coord) const
{
    return _storage[coord.x()][coord.y()];
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
            Coord coord(qrand() % _size, qrand() % _size);
            toggleRocker(coord);
            emit toggleRockerWithoutLogic(coord);
            emit toggleRockerWithLogic(coord, ActionSource::MODEL);
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
            if (model.read(Coord(x, y)) == Rocker::State::HORIZONTAL)
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

void RockersModel::toggleRocker(const Coord &coord)
{
    if (_storage[coord.x()][coord.y()] == Rocker::State::HORIZONTAL)
    {
        _storage[coord.x()][coord.y()] = Rocker::State::VERTICAL;
    }
    else
    {
        _storage[coord.x()][coord.y()] = Rocker::State::HORIZONTAL;
    }
}

void RockersModel::rockerToggled(const Coord &coord, ActionSource source)
{
    qDebug() << "RockersModel: catched a toggle at " << coord << "from" << source;
    toggleRocker(coord);
    switch (source) {
    case ActionSource::CONTROLLER:
        // todo
        break;
    case ActionSource::LOGIC:
        emit toggleRockerWithoutLogic(coord);
        break;
    case ActionSource::MODEL:
        Q_ASSERT(false); // This should never happen
        break;
    case ActionSource::UNDO_REDO:
        emit toggleRockerWithoutLogic(coord);
        emit toggleRockerWithLogic(coord, source);
        break;
    default:
        break;
    }
}
