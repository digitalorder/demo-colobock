#ifndef ROCKERSMODEL_H
#define ROCKERSMODEL_H

#include <QVector>
#include <QDebug>
#include "rocker.h"
#include "primitivetypes.h"

class RockersModel: public QObject, public Blockable
{
    Q_OBJECT
    int _size;
    bool _is_blocked;
    QVector<QVector<Rocker::State>> _storage;
    void toggleRocker(const Coord &coord);
    bool allRockersAreHorizontal();

public:
    RockersModel(int size);
    RockersModel(const RockersModel &obj);
    Rocker::State read(const Coord &coord) const;
    int size() const { return _size; }
    virtual bool isBlocked() { return _is_blocked; }
    virtual void block() { _is_blocked = true; }
    virtual void unblock() { _is_blocked = false; emit modelStateUpdated(RockersModel(*this)); }
    void shuffle(int seed);

signals:
    void modelStateUpdated(const RockersModel & m);
    void toggleRockerWithoutLogic(const Coord &coord);
    void toggleRockerWithLogic(const Coord &coord, ActionSource source);

public slots:
    void rockerToggled(const Coord &coord, ActionSource source);
};

QDebug operator <<(QDebug stream, const RockersModel &model);

#endif // ROCKERSMODEL_H
