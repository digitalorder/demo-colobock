#ifndef ROCKERMATRIX_H
#define ROCKERMATRIX_H

#include <QGridLayout>
#include <QVector>
#include "rocker.h"

class RockerMatrix : public QGridLayout
{
    Q_OBJECT

    int size;
    QVector<Rocker *> rockerMap;

private slots:
    void clicked(int x, int y);

public:
    explicit RockerMatrix(int size = 2, QWidget *parent = 0);

signals:
    void clickedSignal(int x, int y);

public slots:
};

#endif // ROCKERMATRIX_H
