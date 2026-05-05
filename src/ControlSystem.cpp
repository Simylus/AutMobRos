#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : E2("enc2"), quadB(21.2/2.0/M_PI), Sat1(0, 21), ratio(3441.0/104.0), motorConst(8.44e-3), M1("motor1"), 
      timedomain("Main time domain", dt, true)
{
    // Name all blocks
    E2.setName("Encoder 2");
    quadB.setName("AngularConv");
    Sat1.setName("Saturation Block");
    ratio.setName("ratio");
    motorConst.setName("Motor Constant");
    M1.setName("Motor 1 Speed");

    // Name all signals
    E2.getOut().getSignal().setName("q2[rad]");
    quadB.getOut().getSignal().setName("qd1[rad/s]");
    Sat1.getOut().getSignal().setName("qd1[rad/s]");
    ratio.getOut().getSignal().setName("om1[rad/s]");
    motorConst.getOut().getSignal().setName("U[V]");

    // Connect signals
    quadB.getIn().connect(E2.getOut());
    Sat1.getIn().connect(quadB.getOut());
    ratio.getIn().connect(Sat1.getOut());
    motorConst.getIn().connect(ratio.getOut());
    M1.getIn().connect(motorConst.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(E2);
    timedomain.addBlock(quadB);
    timedomain.addBlock(Sat1);
    timedomain.addBlock(ratio);
    timedomain.addBlock(motorConst);
    timedomain.addBlock(M1);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}