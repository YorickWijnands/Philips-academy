#include "hal_st/instantiations/NucleoUi.hpp"
#include "hal_st/instantiations/StmEventInfrastructure.hpp"
#include "hal_st/stm32fxxx/DefaultClockNucleoF429ZI.hpp"
#include "RobotHand.hpp"
#include <cstdint>

unsigned int hse_value = 8'000'000;

static main_::NUCLEO ui;

int main() {
    HAL_Init();

    // Configure your clock hier
    ConfigureDefaultClockNucleoF429ZI();
    static main_::StmEventInfrastructure eventInfrastructure;

    // RobotHand initialiseren
    RobotHand robotHand;
    robotHand.Initialize();
    
    robotHand.MoveFinger(Finger::FINGER_1,100,  500);
    robotHand.MoveFinger(Finger::FINGER_2,100,  500);
    robotHand.MoveFinger(Finger::FINGER_3,100,  500);
    robotHand.MoveFinger(Finger::FINGER_4,100,  500);
    robotHand.MoveFinger(Finger::FINGER_5,100,   500);

    eventInfrastructure.Run();
    __builtin_unreachable();
}
