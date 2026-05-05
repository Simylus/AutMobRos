#ifndef CONTROLSYSTEM_HPP_
#define CONTROLSYSTEM_HPP_

#include <eeros/control/TimeDomain.hpp>
#include <eeros/core/Executor.hpp>
#include <eeros/control/Constant.hpp>
#include <eeros/control/Gain.hpp>
#include <eeros/control/PeripheralInput.hpp>
#include <eeros/control/PeripheralOutput.hpp>
#include <eeros/control/Saturation.hpp>

using namespace eeros::control;

class ControlSystem
{
public:
    ControlSystem(double dt);

    // Define Blocks
    /*
    PeripheralInput<> E2;
    Gain<> quadB;
    Saturation<> Sat1;
    Gain<> ratio;
    Gain<> motorConst;
    PeripheralOutput<> M1;
    */

    PeripheralInput<> E2;
    Gain<> cont;
    Saturation<> QMax;
    Gain<> iInv;
    Gain<> kMInv;
    Gain<> R;
    PeripheralOutput<> M1;
    

    TimeDomain timedomain;
};

#endif // CONTROLSYSTEM_HPP