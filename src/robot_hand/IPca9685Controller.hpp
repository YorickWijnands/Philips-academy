#ifndef I_PCA9685_CONTROLLER_HPP
#define I_PCA9685_CONTROLLER_HPP

#include <cstdint>
#include "Message.hpp"


class IPca9685Controller
{
public:
    enum class Channels : uint8_t {
        Channel_0 = 0x06,
        Channel_1 = 0x0A,
        Channel_2 = 0x0E,
        Channel_3 = 0x12,
        Channel_4 = 0x16,
        Channel_5 = 0x1A,
        Channel_6 = 0x1E,
        Channel_7 = 0x22,
        Channel_8 = 0x26,
        Channel_9 = 0x2A,
        Channel_10 = 0x2E,
        Channel_11 = 0x32,
        Channel_12 = 0x36,
        Channel_13 = 0x3A,
        Channel_14 = 0x3E,
        Channel_15 = 0x42,
        Channel_none = 0xFF
    };

    virtual ~IPca9685Controller() = default;

    virtual void SetAddress(uint16_t newAddress) = 0;
    virtual uint16_t GetRawAddress() const = 0;
    virtual uint16_t GetAddress() const = 0;
    virtual Channels ConnectChannel() = 0;
    virtual bool IsInitialized() const = 0;
    virtual Channels GetChannel(uint8_t index) = 0;
    virtual void EnqueueMessage(const Message& message) = 0;
    virtual void Configure() = 0;
};

#endif // I_PCA9685_CONTROLLER_HPP
