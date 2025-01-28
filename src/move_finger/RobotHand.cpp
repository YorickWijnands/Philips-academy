#include "RobotHand.hpp"
#include "Pca9685Constants.hpp"
#include <cstdint>

RobotHand::RobotHand()
    : scl(hal::Port::B, 8),
      sda(hal::Port::B, 9),
      i2cMaster(1, scl, sda),
      pca9685Address(0x40),
      resetPca9685Address(0x00),
      pca9685(i2cMaster, pca9685Address),
      commandQueue(infra::inPlace, std::array<I2CCommand, 2048>{}),
      isTransmitting(false),
      Initialized(false) {}

void RobotHand::Initialize() {
    ResetDevice();
}

void RobotHand::ResetDevice() {
    static const uint8_t resetData[] = {0x06};
    isTransmitting = true;
    i2cMaster.SendData(resetPca9685Address, infra::MakeConstByteRange(resetData), hal::Action::stop, [this](hal::Result result, uint32_t numberOfBytesSent) {
        isTransmitting = false;
        HAL_Delay(500);
        InitializePca9685();
        Initialized = true;
        SendNextMessage();
    });
}

void RobotHand::InitializePca9685() {
    static const uint8_t data1[] = {0x20};
    static const uint8_t data2[] = {0x04};
    static const uint8_t data3[] = {0x10};
    static const uint8_t data4[] = {0x79};

    QueueI2CMessage(0x00, infra::MakeConstByteRange(data1), 0, I2CPriority::HIGH);
    QueueI2CMessage(0x01, infra::MakeConstByteRange(data2), 0, I2CPriority::HIGH);
    QueueI2CMessage(0x00, infra::MakeConstByteRange(data3), 0, I2CPriority::HIGH);
    QueueI2CMessage(0xFE, infra::MakeConstByteRange(data4), 0, I2CPriority::HIGH);
    QueueI2CMessage(0x00, infra::MakeConstByteRange(data1), 500, I2CPriority::HIGH);
}

void RobotHand::QueueI2CMessage(uint8_t registerAddress, infra::ConstByteRange data, uint32_t delayMs, I2CPriority priority) {
    commandQueue.Push({registerAddress, data, delayMs, priority});
    
    SortCommandQueue();

    if (!isTransmitting && Initialized) {
        SendNextMessage();
    }
}


void RobotHand::SendNextMessage() {
    if (commandQueue.Empty() || isTransmitting) {
        return;
    }
    isTransmitting = true;
    auto& command = commandQueue.ContiguousRange()[0];

    pca9685.WriteRegister(command.registerAddress, command.data, [this, delayMs = command.delayMs]() {
        HAL_Delay(delayMs);
        OnMessageComplete();
    });
}

void RobotHand::OnMessageComplete() {
    commandQueue.Pop(1);
    isTransmitting = false;
    SendNextMessage();
}

void RobotHand::MoveFinger(Finger Finger, uint8_t percentageOpen, uint32_t delayMs) {
    uint8_t registerAddress = static_cast<uint8_t>(Finger);

    int fingerIndex = static_cast<int>(Finger);

    if (Finger == Finger::FINGER_1) {
        percentageOpen = 100 - percentageOpen;
    }
    uint8_t pwmValue = static_cast<uint8_t>(percentageOpen * 255 / 100);
    MoveFingerData[fingerIndex][0] = 0x00;
    MoveFingerData[fingerIndex][1] = 0x00;
    MoveFingerData[fingerIndex][2] = pwmValue;
    MoveFingerData[fingerIndex][3] = 0x01;

    // Gebruik de array van de specifieke vinger
    QueueI2CMessage(registerAddress, infra::MakeConstByteRange(MoveFingerData[fingerIndex]), delayMs, I2CPriority::LOW);
}

void RobotHand::SortCommandQueue() {
    std::array<I2CCommand, 2048> tempArray;
    size_t queueSize = commandQueue.Size();
    
    for (size_t i = 0; i < queueSize; ++i) {
        tempArray[i] = commandQueue.ContiguousRange()[i];
    }
    
    std::sort(tempArray.begin(), tempArray.begin() + queueSize, [](const I2CCommand& a, const I2CCommand& b) {
        return a.priority < b.priority;
    });
    
    for (size_t i = 0; i < queueSize; ++i) {
        commandQueue.Pop(1);
        commandQueue.Push(tempArray[i]);
    }
}
