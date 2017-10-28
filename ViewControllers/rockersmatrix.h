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
    Rocker * getRocker(int x, int y);
    Rocker::State generateRockerState();
    void generateRockers(const RockersModel &m);

public:
    virtual QSize sizeHint() const;
    explicit RockersMatrix(const RockersModel &model, QWidget *parent = 0);

    int size() { return _size; }
    void toggleRocker(int x, int y);
    Rocker::State rockerState(int x, int y);
    virtual bool isBlocked();
    virtual void block();
    virtual void unblock();

signals:
    void rockerToggled(int x, int y, ActionSource source);


private slots:
    void rockerSwitchedInterimSlot(int x, int y);
};

#endif // ROCKERMATRIX_H
