#include "Pca9685Controller.hpp"

// Define the static member
uint8_t Pca9685Controller::connectedFingers = 0;

Pca9685Controller::Pca9685Controller(
    uint16_t addr, 
    IPca9685ControllerManager& manager
)
    : address(addr)
    , controlManager(manager)
{
    // Mark all channels available
    for (uint8_t i = 0; i < channelsCount; ++i)
        isChannelAvailable[i] = true;

    Configure();
}

void Pca9685Controller::SetAddress(uint16_t newAddress)
{
    address = newAddress;
}

uint16_t Pca9685Controller::GetRawAddress() const
{
    return address;
}

uint16_t Pca9685Controller::GetAddress() const
{
    return address;
}

IPca9685Controller::Channels Pca9685Controller::ConnectChannel()
{
    if (connectedFingers >= maxFingers)
        return Channels::Channel_none;

    for (uint8_t i = 0; i < channelsCount; ++i)
    {
        if (isChannelAvailable[i])
        {
            isChannelAvailable[i] = false;
            connectedFingers++;
            return ChannelFromIndex(i);
        }
    }
    return Channels::Channel_none;
}

IPca9685Controller::Channels 
Pca9685Controller::ChannelFromIndex(uint8_t index)
{
    switch (index)
    {
    case 0:  return Channels::Channel_0;
    case 1:  return Channels::Channel_1;
    case 2:  return Channels::Channel_2;
    case 3:  return Channels::Channel_3;
    case 4:  return Channels::Channel_4;
    case 5:  return Channels::Channel_5;
    case 6:  return Channels::Channel_6;
    case 7:  return Channels::Channel_7;
    case 8:  return Channels::Channel_8;
    case 9:  return Channels::Channel_9;
    case 10: return Channels::Channel_10;
    case 11: return Channels::Channel_11;
    case 12: return Channels::Channel_12;
    case 13: return Channels::Channel_13;
    case 14: return Channels::Channel_14;
    case 15: return Channels::Channel_15;
    default: return Channels::Channel_none;
    }
}

bool Pca9685Controller::IsInitialized() const
{
    // For example, check if connectedFingers is multiple of 5
    return (connectedFingers % 5 == 0 && connectedFingers != 0);
}

IPca9685Controller::Channels 
Pca9685Controller::GetChannel(uint8_t index)
{
    return ChannelFromIndex(index);
}

void Pca9685Controller::EnqueueMessage(const Message& message)
{
    controlManager.GetMessageQueue().Enqueue(message);
}

void Pca9685Controller::Configure()
{
    // Sample initialization
    uint8_t Mode1Restart = 0x20;
    uint8_t Mode2TotemPole = 0x04;
    uint8_t Mode1Sleep = 0x10;
    uint8_t PreScaleValue = 0x79;

    // Send messages to queue
    EnqueueMessage(Message(address, 0x00, Mode1Restart));
    EnqueueMessage(Message(address, 0x01, Mode2TotemPole));
    EnqueueMessage(Message(address, 0x00, Mode1Sleep));
    EnqueueMessage(Message(address, 0xFE, PreScaleValue));
    EnqueueMessage(Message(address, 0x00, Mode1Restart, 500));
}
