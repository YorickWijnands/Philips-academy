#ifndef PCA9685_CONTROLLER_IMPLEMENTATION_HPP
#define PCA9685_CONTROLLER_IMPLEMENTATION_HPP

#include "IPca9685Controller.hpp"
#include "IPca9685ControllerManager.hpp"

class Pca9685Controller : public IPca9685Controller
{
public:
    // We pass in the manager interface in the constructor
    Pca9685Controller(uint16_t addr, IPca9685ControllerManager& manager);

    void SetAddress(uint16_t newAddress) override;
    uint16_t GetRawAddress() const override;
    uint16_t GetAddress() const override;
    Channels ConnectChannel() override;
    bool IsInitialized() const override;
    Channels GetChannel(uint8_t index) override;
    void EnqueueMessage(const Message& message) override;
    void Configure() override;

private:
    static constexpr uint8_t maxFingers = 15;
    static constexpr uint8_t channelsCount = 16;
    static uint8_t connectedFingers; // shared among all controllers, if that’s your intent

    uint16_t address;
    bool isChannelAvailable[channelsCount];
    IPca9685ControllerManager& controlManager;

    Channels ChannelFromIndex(uint8_t index);
};

#endif // PCA9685_CONTROLLER_IMPLEMENTATION_HPP
