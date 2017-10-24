#include "rockersmatrix.h"
#include <QDebug>

void RockersMatrix::clicked(int x, int y)
{
    Q_ASSERT(x < _size);
    Q_ASSERT(y < _size);

    emit clickedSignal(x, y);
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
            int randomState = qrand() % 2;
            Rocker::State rockerState;
            if (randomState)
            {
                rockerState = Rocker::VERTICAL;
            }
            else
            {
                rockerState = Rocker::HORIZONTAL;
            }
            Rocker * rocker = new Rocker(x, y, rockerState);
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

