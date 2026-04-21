#ifndef CONTROLSYSTEM_HPP_
#define CONTROLSYSTEM_HPP_

#include <eeros/control/TimeDomain.hpp>
#include <eeros/core/Executor.hpp>
#include <eeros/control/PeripheralInput.hpp>
#include <eeros/control/SignalChecker.hpp>
#include <eeros/control/Constant.hpp>
#include <eeros/control/Gain.hpp>
#include <eeros/control/PeripheralOutput.hpp>

using namespace eeros::control;

class ControlSystem
{
public:
    ControlSystem(double dt);

    // Define Blocks
    Constant<> myConstant;
    Gain<> myGain;

    PeripheralInput<> q1;
    Gain<> g;
    Constant<> motVolt1;
    Constant<> motVolt2;
    PeripheralOutput<> mot1;
    PeripheralOutput<> mot2;

    TimeDomain timedomain;
};

#endif // CONTROLSYSTEM_HPP