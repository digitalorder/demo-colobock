#ifndef ROCKERMATRIX_H
#define ROCKERMATRIX_H

#include <QGridLayout>
#include <QVector>
#include "rocker.h"

class RockersMatrix : public QGridLayout
{
    Q_OBJECT

    int _size;
    QVector<Rocker *> _rockerMap;
    Rocker * getRocker(int x, int y);

private slots:
    void clicked(int x, int y);

public:
    explicit RockersMatrix(int _size = 2, QWidget *parent = 0);

    int size() { return _size; }
    void toggleRocker(int x, int y);
    Rocker::State rockerState(int x, int y);

signals:
    void clickedSignal(int x, int y);

public slots:
};

#endif // ROCKERMATRIX_H
