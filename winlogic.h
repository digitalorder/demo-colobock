#ifndef WINLOGIC_H
#define WINLOGIC_H

#include <QObject>
#include "rockersmodel.h"
#include "locksstate.h"

class WinLogic : public QObject
{
    Q_OBJECT
public:
    explicit WinLogic(QObject *parent = 0);

signals:
    void win();

public slots:
    void newLocksStateSlot(LocksState state);
};

#endif // WINLOGIC_H
