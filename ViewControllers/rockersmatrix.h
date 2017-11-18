#ifndef ROCKERMATRIX_H
#define ROCKERMATRIX_H

#include <QGridLayout>
#include <QVector>
#include "rocker.h"
#include "rockersmodel.h"
#include "primitivetypes.h"

class RockersMatrix : public QGridLayout, public Blockable
{
    Q_OBJECT

    int _size;
    QVector<Rocker *> _rockerMap;
    Rocker * getRocker(const Coord& coord);
    Rocker::State generateRockerState();
    void generateRockers(const RockersModel &m);

public:
    virtual QSize sizeHint() const;
    explicit RockersMatrix(const RockersModel &model, QWidget *parent = 0);

    int size() { return _size; }
    void toggleRocker(const Coord& coord);
    Rocker::State rockerState(const Coord& coord);
    virtual bool isBlocked();
    virtual void block();
    virtual void unblock();

signals:
    void rockerToggled(const Coord& coord, ActionSource source);


private slots:
    void rockerSwitchedInterimSlot(const Coord& coord);
};

#endif // ROCKERMATRIX_H
