#include "rockerslogic.h"
#include <QDebug>

class ToggleContext
{
public:
    ToggleContext(Coord coord, ActionSource source, SwitchingTiming timing):
        coord(coord), distance(1), action_source(source), timing(timing)
    {
    }

    Coord coord;
    int distance;
    ActionSource action_source;
    SwitchingTiming timing;

    friend QDebug operator <<(QDebug os, const ToggleContext & obj);
};

QDebug operator <<(QDebug os, const ToggleContext & obj)
{
    return os << "ToggleContext(Coord =" << obj.coord << ", distance =" << obj.distance << ", source =" << obj.action_source << ", timing =" << obj.timing << ")";
}


ToggleContext _toggle_context(Coord(), ActionSource::MODEL, SwitchingTiming::INSTANT);

RockersLogic::RockersLogic(int size) : _size(size)
{
    _delay_timer = new QTimer(this);
    _delay_timer->setInterval(500 / size);
    _delay_timer->setSingleShot(true);

    connect(_delay_timer, &QTimer::timeout, this, &RockersLogic::rockerDelayTimeout);
}

int RockersLogic::do_toggling()
{
    qDebug() << "RockersLogic: doing toggling for context " << _toggle_context;
    int toggled_count = 0;
    if (_toggle_context.coord.x() - _toggle_context.distance >= 0)
    {
        emit rockerSwitchedSignal(Coord(_toggle_context.coord.x() - _toggle_context.distance, _toggle_context.coord.y()), ActionSource::LOGIC);
        toggled_count++;
    }
    if (_toggle_context.coord.x() + _toggle_context.distance < _size)
    {
        emit rockerSwitchedSignal(Coord(_toggle_context.coord.x() + _toggle_context.distance, _toggle_context.coord.y()), ActionSource::LOGIC);
        toggled_count++;
    }
    if (_toggle_context.coord.y() - _toggle_context.distance >= 0)
    {
        emit rockerSwitchedSignal(Coord(_toggle_context.coord.x(), _toggle_context.coord.y() - _toggle_context.distance), ActionSource::LOGIC);
        toggled_count++;
    }
    if (_toggle_context.coord.y() + _toggle_context.distance < _size)
    {
        emit rockerSwitchedSignal(Coord(_toggle_context.coord.x(), _toggle_context.coord.y() + _toggle_context.distance), ActionSource::LOGIC);
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

void RockersLogic::rockerSwitchedSlot(const Coord &coord, ActionSource source)
{
    qDebug() << "RockersLogic: catched a toggle at " << coord << " from" << source;
    SwitchingTiming timing = source == ActionSource::MODEL ? SwitchingTiming::INSTANT : SwitchingTiming::DELAYED;
    _toggle_context = ToggleContext(coord, source, timing);
    emit blockControllers();
    if (source == ActionSource::CONTROLLER)
    {
        emit rockerSwitchedSignal(_toggle_context.coord, source);
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

void RockersLogic::toggleRocker(const Coord &coord, ActionSource source)
{
    rockerSwitchedSlot(coord, source);
}
