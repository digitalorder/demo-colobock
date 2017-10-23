#include "rockermatrix.h"
#include <QDebug>

void RockerMatrix::clicked(int x, int y)
{
    Q_ASSERT(x < size);
    Q_ASSERT(y < size);
    qDebug() << "Assertion passed";

    emit clickedSignal(x, y);
}

RockerMatrix::RockerMatrix(int size, QWidget *parent) : QGridLayout(parent)
{
    this->size = size;
    setSpacing(0);
    for (int x = 0; x < size; x++)
    {
        setRowMinimumHeight(x, 32);
        setColumnMinimumWidth(x, 32);
        for (int y = 0; y < size; y++)
        {
            Rocker * rocker = new Rocker(x, y);
            addWidget(rocker, x, y);
            connect(rocker, &Rocker::clickedOverride, this, &RockerMatrix::clicked);
        }
    }
}

