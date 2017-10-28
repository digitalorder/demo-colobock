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
//    _storage.resize(obj.size());
//    for (int i = 0; i < obj.size(); i++)
//    {
//        _storage[i].resize(obj.size());
//    }
    _storage = obj._storage;
    _size = obj._size;
}

int RockersModel::getIndex(int x, int y)
{
    int result = x + y * _size;
    return result;
}

//void RockersModel::assign(int x, int y, Rocker::State value)
//{
//    _storage[x][y] = value;
//}

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
        emit rockerToggleRequest(x, y);
    }
    if (!this->isBlocked())
    {
        // todo
        emit modelStateUpdated(RockersModel(_size));
    }
}
