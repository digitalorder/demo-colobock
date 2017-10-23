#include "rockermatrix.h"
#include <QDebug>

void RockerMatrix::clicked(int x, int y)
{
    Q_ASSERT(x < _size);
    Q_ASSERT(y < _size);

    emit clickedSignal(x, y);
}

RockerMatrix::RockerMatrix(int size, QWidget *parent) : QGridLayout(parent)
{
    this->_size = size;
    setSpacing(0);
    for (int x = 0; x < size; x++)
    {
        setRowMinimumHeight(x, 32);
        setColumnMinimumWidth(x, 32);
        for (int y = 0; y < size; y++)
        {
            Rocker * rocker = new Rocker(x, y);
            addWidget(rocker, x, y);
            _rockerMap.append(rocker);
            connect(rocker, &Rocker::clickedOverride, this, &RockerMatrix::clicked);
        }
    }
}

void RockerMatrix::toggleRocker(int x, int y)
{
    qDebug() << "Toggling rocker (" << x << "," << y << ")";
    int index = x + y * _size;
    Rocker * r = _rockerMap[index];
    r->toggle();
}

