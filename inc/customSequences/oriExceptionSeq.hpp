#ifndef ORIEXCEPTIONSEQ_HPP_
#define ORIEXCEPTIONSEQ_HPP_


#include <eeros/sequencer/Sequence.hpp>
#include <eeros/sequencer/Condition.hpp>

class CheckOrient : public eeros::sequencer::Condition
{
public:
    CheckOrient(double angle, ControlSystem &cs) : angle(angle), cs(cs) {}
    bool validate() {return abs(cs.g.getOut().getSignal().getValue()) > angle;}

private:
    ControlSystem &cs;
    double angle;
};

class OrientationExcept : public eeros::sequencer::Sequence
{
public:
    OrientationExcept(std::string name, eeros::sequencer::Sequence *caller,
                        ControlSystem &cs, CheckOrient checkOrientation)
        : cs(cs), checkOrientation(checkOrientation),
          eeros::sequencer::Sequence(name, caller, true)
    {
        log.info() << "Sequence created: " << name;
    }

    int action()
    {
        // do something
        log.warn() << "Orientation around x is outside of the allowed range!";
        log.warn() << "Stoping all motors!";
        cs.motVolt1.setValue(0);
        cs.motVolt2.setValue(0);
        return 0;
    }

    bool checkExitCondition()
    {
        return !checkOrientation.validate();
    }

private:
    // Define steps, sub-sequences, variables, conditions, monitors, exception sequences, ...
    ControlSystem &cs;
    CheckOrient checkOrientation;
};

#endif // ORIEXCEPTIONSEQ_HPP_
