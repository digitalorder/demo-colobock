#include "rockerslogic.h"
#include <QDebug>

class ToggleContext
{
public:
    ToggleContext(int x, int y, ActionSource source, SwitchingTiming timing):
        x(x), y(y), distance(1), action_source(source), timing(timing)
    {
    }

    int x;
    int y;
    int distance;
    ActionSource action_source;
    SwitchingTiming timing;

    friend QDebug operator <<(QDebug os, const ToggleContext & obj);
};

QDebug operator <<(QDebug os, const ToggleContext & obj)
{
    os << "ToggleContext(x =" << obj.x << ", y =" << obj.y << ", distance =" << obj.distance << ", source =" << obj.action_source << ", timing =" << obj.timing << ")";
    return os;
}


ToggleContext _toggle_context(0, 0, ActionSource::MODEL, SwitchingTiming::INSTANT);

RockersLogic::RockersLogic(int size) : _size(size)
{
    _delay_timer = new QTimer(this);
    _delay_timer->setInterval(300);
    _delay_timer->setSingleShot(true);

    connect(_delay_timer, &QTimer::timeout, this, &RockersLogic::rockerDelayTimeout);
}

int RockersLogic::do_toggling()
{
    qDebug() << "RockersLogic: doing toggling for context " << _toggle_context;
    int toggled_count = 0;
    if (_toggle_context.x - _toggle_context.distance >= 0)
    {
        emit rockerSwitchedSignal(_toggle_context.x - _toggle_context.distance, _toggle_context.y, ActionSource::LOGIC);
        toggled_count++;
    }
    if (_toggle_context.x + _toggle_context.distance < _size)
    {
        emit rockerSwitchedSignal(_toggle_context.x + _toggle_context.distance, _toggle_context.y, ActionSource::LOGIC);
        toggled_count++;
    }
    if (_toggle_context.y - _toggle_context.distance >= 0)
    {
        emit rockerSwitchedSignal(_toggle_context.x, _toggle_context.y - _toggle_context.distance, ActionSource::LOGIC);
        toggled_count++;
    }
    if (_toggle_context.y + _toggle_context.distance < _size)
    {
        emit rockerSwitchedSignal(_toggle_context.x, _toggle_context.y + _toggle_context.distance, ActionSource::LOGIC);
        toggled_count++;
    }
    _toggle_context.distance++;
    return toggled_count;
}

void RockersLogic::toggleRelatedRockers()
{
    int toggled_count = 0;
    do
    {
        toggled_count = do_toggling();
    } while (toggled_count && _toggle_context.timing == SwitchingTiming::INSTANT);

    if (toggled_count)
    {
        _delay_timer->start();
    }
    else
    {
        emit unblockControllers();
    }
}

void RockersLogic::rockerSwitchedSlot(int x, int y, ActionSource source)
{
    qDebug() << "RockersLogic: catched a toggle at (" << x << "," << y << ") from" << source;
    SwitchingTiming timing = source == ActionSource::MODEL ? SwitchingTiming::INSTANT : SwitchingTiming::DELAYED;
    _toggle_context = ToggleContext(x, y, source, timing);
    emit blockControllers();
    if (source != ActionSource::UNDO_REDO)
    {
        emit rockerSwitchedSignal(_toggle_context.x, _toggle_context.y, source);
    }
    if (timing == SwitchingTiming::INSTANT)
    {
        toggleRelatedRockers();
    }
    else
    {
        _delay_timer->start();
    }
}

void RockersLogic::rockerDelayTimeout()
{
    toggleRelatedRockers();
}

void RockersLogic::toggleRocker(int x, int y)
{
    rockerSwitchedSlot(x, y, ActionSource::UNDO_REDO);
}
