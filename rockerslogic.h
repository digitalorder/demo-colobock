#ifndef ROCKERSLOGIC_H
#define ROCKERSLOGIC_H

#include <QObject>
#include "logger.h"
#include "primitivetypes.h"
#include <QTimer>

class RockersLogic : public QObject
{
    Q_OBJECT
    int _size;
    QTimer * _delay_timer;
    void toggleRelatedRockers();
    int do_toggling();

public:
    explicit RockersLogic(int size);

signals:
    void blockControllers();
    void unblockControllers();
    void rockerSwitchedSignal(int x, int y, ActionSource source);

public slots:
    void rockerSwitchedSlot(int x, int y, ActionSource source);
    void toggleRocker(int x, int y, ActionSource source);

private slots:
    void rockerDelayTimeout();
};

#endif // ROCKERSLOGIC_H
