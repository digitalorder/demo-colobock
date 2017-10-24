#include "rockersmatrix.h"
#include <QDebug>

void RockersMatrix::clicked(int x, int y)
{
    Q_ASSERT(x < _size);
    Q_ASSERT(y < _size);

    emit clickedSignal(x, y);
}

Rocker::State RockersMatrix::generateRockerState()
{
    int randomState = qrand() % 2;
    if (randomState)
    {
        return Rocker::VERTICAL;
    }
    else
    {
        return Rocker::HORIZONTAL;
    }
}

RockersMatrix::RockersMatrix(int size, QWidget *parent) : QGridLayout(parent)
{
    this->_size = size;
    setSpacing(0);
    for (int x = 0; x < size; x++)
    {
        setRowMinimumHeight(x, 32);
        setColumnMinimumWidth(x, 32);
        for (int y = 0; y < size; y++)
        {
            Rocker * rocker = new Rocker(x, y, generateRockerState());
            addWidget(rocker, x, y);
            _rockerMap.append(rocker);
            connect(rocker, &Rocker::clickedOverride, this, &RockersMatrix::clicked);
        }
    }
}

Rocker * RockersMatrix::getRocker(int x, int y)
{
    int index = x * _size + y;
    Q_ASSERT(index < _rockerMap.size());
    return _rockerMap[index];
}

void RockersMatrix::toggleRocker(int x, int y)
{
    getRocker(x, y)->toggleState();
}

Rocker::State RockersMatrix::rockerState(int x, int y)
{
    return getRocker(x, y)->getState();
}

void RockersMatrix::shuffle()
{
    for (auto r = _rockerMap.begin(); r != _rockerMap.end(); ++r)
    {
        (*r)->setState(generateRockerState());
    }
}

