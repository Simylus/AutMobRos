#ifndef MAINSEQUENCE_HPP_
#define MAINSEQUENCE_HPP_

#include <eeros/sequencer/Sequencer.hpp>
#include <eeros/sequencer/Sequence.hpp>
#include <eeros/safety/SafetySystem.hpp>
#include "MyRobotSafetyProperties.hpp"
#include "ControlSystem.hpp"
#include <eeros/sequencer/Wait.hpp>
#include <customSteps/setVoltage.hpp>
#include <customSequences/oriExceptionSeq.hpp>
#include <eeros/sequencer/Monitor.hpp>

class MainSequence : public eeros::sequencer::Sequence
{
public:
    MainSequence(std::string name, eeros::sequencer::Sequencer &seq,
                 eeros::safety::SafetySystem &ss,
                 MyRobotSafetyProperties &sp, ControlSystem &cs)
        : eeros::sequencer::Sequence(name, seq),
          ss(ss),
          sp(sp),
          cs(cs),

          sleep("Sleep", this),
          setVoltage("motVolt", this, cs),

          checkOrientation(0.1, cs), 
          orientationException("Orientation Exception", this, cs, checkOrientation),
          orientMonitor("Orientation Monitor", this, checkOrientation, eeros::sequencer::SequenceProp::resume, &orientationException)   

    {
        addMonitor(&orientMonitor);
        log.info() << "Sequence created: " << name;
    }

    int action()
    {
        while (eeros::sequencer::Sequencer::running)
        {
            //sleep(1.0);
            //log.info() << cs.myGain.getOut().getSignal();
            setVoltage(0.7);
            sleep(1.5);
            setVoltage(-0.7);
            sleep(1.5);
        }
        return 0;
    }

private:
    eeros::safety::SafetySystem &ss;
    ControlSystem &cs;
    MyRobotSafetyProperties &sp;

    eeros::sequencer::Wait sleep;
    SetVoltage setVoltage;
    CheckOrient checkOrientation;
    OrientationExcept orientationException;
    eeros::sequencer::Monitor orientMonitor;
};

#endif // MAINSEQUENCE_HPP_