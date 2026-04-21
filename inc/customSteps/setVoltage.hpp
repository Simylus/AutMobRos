#ifndef SETVOLTAGE_HPP_
#define SETVOLTAGE_HPP_

#include <eeros/sequencer/Step.hpp>
#include <ControlSystem.hpp>

class SetVoltage : public eeros::sequencer::Step
{
public:
    SetVoltage(std::string name, eeros::sequencer::Sequence *caller, ControlSystem &cs)
        : cs(cs), eeros::sequencer::Step(name, caller)
    {
        log.info() << "Step created: " << name;
    }

    int operator() (double motorVoltageSetpoint)
    {
        this->motorVoltageSetpoint1 = motorVoltageSetpoint;
        this->motorVoltageSetpoint2 = (-1) * motorVoltageSetpoint;
        return start();
    }

    int action()
    {
        // do something
        log.info() << "Setting voltage to " << motorVoltageSetpoint1 << " volts.";
        cs.motVolt1.setValue(motorVoltageSetpoint1);
        cs.motVolt2.setValue(motorVoltageSetpoint2);
        return 0;
    }

private:
    // Define variables, conditions, monitors, exception sequences, ...
    ControlSystem &cs;
    double motorVoltageSetpoint1;
    double motorVoltageSetpoint2;
};

#endif // SETVOLTAGE_HPP_
