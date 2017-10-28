#ifndef SWITCHESSTATE_H
#define SWITCHESSTATE_H

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
    void toggleRocker(int x, int y);

public:
    RockersModel(int size);
    RockersModel(const RockersModel &obj);
    Rocker::State read(int x, int y) const;
    int size() const { return _size; }
    virtual bool isBlocked() { return _is_blocked; }
    virtual void block() { _is_blocked = true; }
    virtual void unblock() { _is_blocked = false; emit modelStateUpdated(RockersModel(*this)); }

signals:
    void modelStateUpdated(const RockersModel & m);
    void toggleRockerWithoutLogic(int x, int y);
    void toggleRockerWithLogic(int x, int y);

public slots:
    void rockerToggled(int x, int y, ActionSource source);
};

QDebug operator <<(QDebug stream, const RockersModel &model);

#endif // SWITCHESSTATE_H
