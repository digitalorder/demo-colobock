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

RockersMatrix::RockersMatrix(const RockersModel &model, const Settings &settings, QWidget *parent) : QGridLayout(parent)
{
    _size = settings.matrixSize();
    setSpacing(0);
    setContentsMargins(0, 0, 0, 0);
    generateRockers(model, settings);
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

Rocker * RockersMatrix::getRocker(const Coord &coord)
{
    int index = coord.x() * _size + coord.y();
    return _rockerMap[index];
}

void RockersMatrix::toggleRocker(const Coord &coord)
{
    qDebug() << "RockersMatrix: received a request to toggle " << coord;
    getRocker(coord)->toggleState();
}

Rocker::State RockersMatrix::rockerState(const Coord &coord)
{
    return getRocker(coord)->getState();
}

QSize RockersMatrix::sizeHint() const
{
    return QSize(_rockerMap.at(0)->width() * _size * 1.25, _rockerMap.at(0)->height() * _size);
}

void RockersMatrix::generateRockers(const RockersModel& model, const Settings &settings)
{
    for (int x = 0; x < settings.matrixSize(); x++)
    {
        for (int y = 0; y < settings.matrixSize(); y++)
        {
            Coord coord(x, y);
            Rocker * rocker = new Rocker(coord, model.read(coord), settings);
            addWidget(rocker, coord.x(), coord.y());
            _rockerMap.append(rocker);
            connect(rocker, &Rocker::clickedOverride, this, &RockersMatrix::rockerSwitchedInterimSlot);
        }
        setRowMinimumHeight(x, _rockerMap.at(0)->height());
        setColumnMinimumWidth(x, _rockerMap.at(0)->width());
    }
}

void RockersMatrix::rockerSwitchedInterimSlot(const Coord &coord)
{
    emit rockerToggled(coord, ActionSource::CONTROLLER);
}

