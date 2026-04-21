#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : q1("quat1"), g(2.0), motVolt1(0.0), motVolt2(0.0), mot1("motor1"), mot2("motor2"),
      timedomain("Main time domain", dt, true)
{
    // Name all blocks
    q1.setName("q1");
    g.setName("g");
    motVolt1.setName("motorVoltage1");
    motVolt2.setName("motorVoltage2");
    mot1.setName("mot1");
    mot2.setName("mot2");

    // Name all signals
    q1.getOut().getSignal().setName("alpha/2");
    g.getOut().getSignal().setName("alpha");
    motVolt1.getOut().getSignal().setName("Motor voltage1 setpoint [V]");
    motVolt2.getOut().getSignal().setName("Motor voltage2 setpoint [V]");

    // Connect signals
    g.getIn().connect(q1.getOut());
    mot1.getIn().connect(motVolt1.getOut());
    mot2.getIn().connect(motVolt1.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(q1);
    timedomain.addBlock(g);
    timedomain.addBlock(motVolt1);
    timedomain.addBlock(motVolt2);
    timedomain.addBlock(mot1);
    timedomain.addBlock(mot2);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}