#ifndef ROBOT_HAND_HPP
#define ROBOT_HAND_HPP

#include "hal_st/stm32fxxx/I2cStm.hpp"
#include "hal_st/stm32fxxx/GpioStm.hpp"
#include "hal/interfaces/I2cRegisterAccess.hpp"
#include "infra/util/CyclicBuffer.hpp"
#include "infra/util/ByteRange.hpp"
#include <cstdint>

enum class I2CPriority : uint8_t {
    HIGH = 0,
    LOW = 1
};

enum class Finger : uint8_t {
    FINGER_1 = 0x06,
    FINGER_2 = 0x0A,
    FINGER_3 = 0x0E,
    FINGER_4 = 0x12,
    FINGER_5 = 0x16
};

class RobotHand {
public:
    RobotHand();
    void Initialize();
    void MoveFinger(Finger finger, uint8_t percentageOpen, uint32_t delayMs);

private:
    struct I2CCommand {
        uint8_t registerAddress;
        infra::ConstByteRange data;
        uint32_t delayMs;
        I2CPriority priority;
    };

    void InitializePca9685();
    void ResetDevice();
    void QueueI2CMessage(uint8_t registerAddress, infra::ConstByteRange data, uint32_t delayMs, I2CPriority priority);
    void SendNextMessage();
    void OnMessageComplete();
    void AddRangeToQueue();
    void SortCommandQueue();

    // I2C-specific members
    hal::GpioPinStm scl;
    hal::GpioPinStm sda;
    hal::I2cStm i2cMaster;
    hal::I2cAddress pca9685Address;
    hal::I2cAddress resetPca9685Address;
    hal::I2cMasterRegisterAccessByte pca9685;

    // Buffer for I2C commands
    infra::CyclicBuffer<I2CCommand>::WithStorage<2048> commandQueue;

    uint8_t MoveFingerData[5][4];

    bool isTransmitting;
    bool Initialized;
};

#endif // ROBOT_HAND_HPP
