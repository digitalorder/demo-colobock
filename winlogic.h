#ifndef WINLOGIC_H
#define WINLOGIC_H

#include <QObject>
#include "rockersmodel.h"
#include "locksmodel.h"

class WinLogic : public QObject
{
    Q_OBJECT
public:
    explicit WinLogic(QObject *parent = 0);

signals:
    void win();

public slots:
    void newLocksStateSlot(LocksModel state);
};

#endif // WINLOGIC_H
