#include "rockersmatrix.h"
#include <QTime>

void RockersMatrix::clicked(int x, int y)
{
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
    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));
    setSpacing(0);
    reinit(size);
}

void RockersMatrix::disable()
{
    for (auto r = _rockerMap.begin(); r != _rockerMap.end(); ++r)
    {
        (*r)->setEnabled(false);
    }
}

void RockersMatrix::enable()
{
    for (auto r = _rockerMap.begin(); r != _rockerMap.end(); ++r)
    {
        (*r)->setEnabled(true);
    }
}

Rocker * RockersMatrix::getRocker(int x, int y)
{
    int index = x * _size + y;
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
    return QSize(_rockerMap.at(0)->width() * _size * 1.4, _rockerMap.at(0)->height() * _size * 1.5);
}

void RockersMatrix::reinit(int matrixSize)
{
    this->_size = matrixSize;
    for (int x = 0; x < matrixSize; x++)
    {
        for (int y = 0; y < matrixSize; y++)
        {
            Rocker * rocker = new Rocker(x, y, generateRockerState());
            addWidget(rocker, x, y);
            _rockerMap.append(rocker);
            connect(rocker, &Rocker::clickedOverride, this, &RockersMatrix::clicked);
        }
        setRowMinimumHeight(x, _rockerMap.at(0)->height());
        setRowMinimumHeight(x, _rockerMap.at(0)->width());
    }
    setSizeConstraint(QLayout::SetFixedSize);
}

