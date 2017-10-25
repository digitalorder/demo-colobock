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
    setSpacing(0);
    reinit(size);

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

QSize RockersMatrix::sizeHint() const
{
    return QSize(40 * _size, 48 * _size);
}

void RockersMatrix::reinit(int matrixSize)
{
    this->_size = matrixSize;
    for (auto rocker = _rockerMap.begin(); rocker != _rockerMap.end(); ++rocker)
    {
        removeWidget(*rocker);
        delete *rocker;
    }

    _rockerMap.clear();
    for (int x = 0; x < matrixSize; x++)
    {
        setRowMinimumHeight(x, 32);
        setColumnMinimumWidth(x, 32);
        for (int y = 0; y < matrixSize; y++)
        {
            Rocker * rocker = new Rocker(x, y, generateRockerState());
            addWidget(rocker, x, y);
            _rockerMap.append(rocker);
            connect(rocker, &Rocker::clickedOverride, this, &RockersMatrix::clicked);
        }
    }
    setSizeConstraint(QLayout::SetFixedSize);
    QRect r(0, 0, 48 * _size, 48 * _size);
    this->setGeometry(r);
}

