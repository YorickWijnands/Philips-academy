#ifndef PCA9685_CONTROLLER_MANAGER_IMPLEMENTATION_HPP
#define PCA9685_CONTROLLER_MANAGER_IMPLEMENTATION_HPP

#include <cstdint>
#include "IPca9685ControllerManager.hpp"
#include "Pca9685Controller.hpp"
#include "MessageQueue.hpp"
#include "hal_st/stm32fxxx/I2cStm.hpp"
#include "infra/util/Optional.hpp"
#include "infra/util/ByteRange.hpp"
#include "infra/timer/Timer.hpp"

struct I2CConfig
{
    uint8_t sclPin = 8;
    uint8_t sdaPin = 9;
    uint8_t i2cIndex = 1;
};

class Pca9685ControllerManager 
    : public IPca9685ControllerManager
{
public:
    static constexpr uint8_t maxControllers = 62;
    static constexpr size_t dataSize = 4;

    Pca9685ControllerManager();
    explicit Pca9685ControllerManager(I2CConfig config);

    // IPca9685ControllerManager overrides
    IPca9685Controller* AddController(uint8_t address) override;
    IPca9685Controller* GetController(uint8_t address) override;
    IMessageQueue& GetMessageQueue() override;

private:
    void Run();
    void WriteNextMessage();
    void WriteRegister();
    void OnWriteDone();

    I2CConfig config;
    // Using STM32 HAL as an example
    hal::GpioPinStm scl{ hal::Port::B, config.sclPin };
    hal::GpioPinStm sda{ hal::Port::B, config.sdaPin };
    hal::I2cStm i2cMaster{ config.i2cIndex, scl, sda };

    bool isI2cAvailable = true;
    Message currentMessage;
    uint8_t registerAddress = 0;
    uint8_t singleData = 0;
    uint8_t dataArray[dataSize] = {0};

    static MessageQueue messageQueue;

    infra::Optional<Pca9685Controller> controllers[maxControllers];
    infra::TimerSingleShot reEnableI2cTimer;
};

#endif // PCA9685_CONTROLLER_MANAGER_IMPLEMENTATION_HPP
