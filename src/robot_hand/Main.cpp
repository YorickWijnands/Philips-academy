#include "Hand.hpp"
#include "Pca9685ControllerManager.hpp"
#include "hal_st/instantiations/StmEventInfrastructure.hpp"
#include "hal_st/stm32fxxx/DefaultClockNucleoF429ZI.hpp"

unsigned int hse_value = 8'000'000;

int main() {
    HAL_Init();
    ConfigureDefaultClockNucleoF429ZI();

    static main_::StmEventInfrastructure eventInfrastructure;

    static Pca9685ControllerManager manager;

    manager.AddController(0x40);

    Hand hand(manager.GetController(0x40));
    hand.OpenHandAllAtOnce(500);
    hand.CloseHandAllAtOnce(500);
    hand.OpenHandAllAtOnce(500);
    hand.CloseHandAllAtOnce(500);
    hand.OpenHandAllAtOnce(500);
    hand.CloseHandAllAtOnce(500);
    hand.OpenHandAllAtOnce(500);
    hand.CloseHandAllAtOnce(500);


    hand.OpenHandSequential(100);
    hand.CloseHandSequential(200);
    hand.OpenHandAllAtOnce(500);
    hand.CloseHandAllAtOnce(1000);
    hand.Wiggle();
    hand.WaveMotion(25, 10, 2);
    hand.CloseHandAllAtOnce(100);
    eventInfrastructure.Run();
    __builtin_unreachable();
}
