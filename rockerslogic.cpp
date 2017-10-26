#include "rockerslogic.h"

class ToggleContext
{
public:
    ToggleContext(): x(0), y(0), revertAction(false) {}

    ToggleContext(int x, int y, bool revertAction): x(x), y(y), revertAction(revertAction), distance(1)
    {
    }

    int x;
    int y;
    bool revertAction;
    int distance;
};

ToggleContext _toggle_context;

RockersLogic::RockersLogic(RockersMatrix *matrix, QWidget *parent) : QObject(parent)
{
    _matrix = matrix;
    emitNewRockersStateSignal();
    _delay_timer = new QTimer(this);
    _delay_timer->setInterval(300);
    _delay_timer->setSingleShot(true);

    connect(_delay_timer, &QTimer::timeout, this, &RockersLogic::rockerDelayTimeout);
}

void RockersLogic::emitNewRockersStateSignal()
{
    RockersModel s = getState();
    emit newRockersStateSignal(s);
}

RockersModel RockersLogic::getState()
{
    RockersModel state(_matrix->size());
    for (int x = 0; x < _matrix->size(); x++)
    {
        for (int y = 0; y < _matrix->size(); y++)
        {
            state.assign(x, y, _matrix->rockerState(y, x));
        }
    }

    return state;
}

void RockersLogic::toggleRelatedRockers(int x, int y)
{
    int toggled_count = 0;
    if (x - _toggle_context.distance >= 0)
    {
        _matrix->toggleRocker(x - _toggle_context.distance, y);
        toggled_count++;
    }
    if (x + _toggle_context.distance < _matrix->size())
    {
        _matrix->toggleRocker(x + _toggle_context.distance, y);
        toggled_count++;
    }
    if (y - _toggle_context.distance >= 0)
    {
        _matrix->toggleRocker(x, y - _toggle_context.distance);
        toggled_count++;
    }
    if (y + _toggle_context.distance < _matrix->size())
    {
        _matrix->toggleRocker(x, y + _toggle_context.distance);
        toggled_count++;
    }
    _toggle_context.distance++;
    if (toggled_count)
    {
        _delay_timer->start();
    }
    else
    {
        emit switchingComplete();
        if (!_toggle_context.revertAction)
        {
            emit rockerSwitchedSignal(x, y);
        }
        emitNewRockersStateSignal();
    }
}

void RockersLogic::startSwitching(int x, int y, bool reverseAction)
{
    _toggle_context = ToggleContext(x, y, reverseAction);
    emit switchingStarted();
    _delay_timer->start();
}

void RockersLogic::rockerSwitchedSlot(int x, int y)
{
    startSwitching(x, y, false);
}

void RockersLogic::rockerDelayTimeout()
{
    toggleRelatedRockers(_toggle_context.x, _toggle_context.y);
}

void RockersLogic::revertAction(int x, int y)
{
    _matrix->toggleRocker(x, y);
    startSwitching(x, y, true);
}

//void RockersLogic::generateBoard()
//{
//    RockersState s;

//}
