#include "rockersmatrix.h"
#include "rockerslogic.h"
#include <QTime>

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

RockersMatrix::RockersMatrix(const RockersModel &model, QWidget *parent) : QGridLayout(parent)
{
    _size = model.size();
    setSpacing(0);
    generateRockers(model);
}

void RockersMatrix::block()
{
    std::for_each(_rockerMap.begin(), _rockerMap.end(), [](Rocker * r){ r->setEnabled(false); });
}

void RockersMatrix::unblock()
{
    std::for_each(_rockerMap.begin(), _rockerMap.end(), [](Rocker * r){ r->setEnabled(true); });
}

bool RockersMatrix::isBlocked()
{
    // todo
    return false;
}

Rocker * RockersMatrix::getRocker(int x, int y)
{
    int index = x * _size + y;
    return _rockerMap[index];
}

void RockersMatrix::toggleRocker(int x, int y)
{
    qDebug() << "RockersMatrix: received a request to toggle (" << x << "," << y << ")";
    getRocker(x, y)->toggleState();
}

Rocker::State RockersMatrix::rockerState(int x, int y)
{
    return getRocker(x, y)->getState();
}

QSize RockersMatrix::sizeHint() const
{
    return QSize(_rockerMap.at(0)->width() * _size * 1.4, _rockerMap.at(0)->height() * _size * 1.5);
}

void RockersMatrix::generateRockers(const RockersModel & m)
{
    for (int x = 0; x < _size; x++)
    {
        for (int y = 0; y < _size; y++)
        {
            Rocker * rocker = new Rocker(x, y, m.read(x, y));
            addWidget(rocker, x, y);
            _rockerMap.append(rocker);
            connect(rocker, &Rocker::clickedOverride, this, &RockersMatrix::rockerSwitchedInterimSlot);
        }
        setRowMinimumHeight(x, _rockerMap.at(0)->height());
        setColumnMinimumWidth(x, _rockerMap.at(0)->width());
    }
}

void RockersMatrix::rockerSwitchedInterimSlot(int x, int y)
{
    emit rockerToggled(x, y, ActionSource::CONTROLLER);
}

