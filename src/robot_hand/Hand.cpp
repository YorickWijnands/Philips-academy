#include "Hand.hpp"
#include "Finger.hpp"
#include "Message.hpp"

Hand::Hand(IPca9685Controller* controller)
    : controller(controller)
{
    // Initially, no channel connected
    for (uint8_t i = 0; i < fingerCount; i++)
        isFingerConnected[i] = false;

    // Construct each Finger with minPos=0, maxPos=100
    // (already done by default constructor init in the array)
    // fingers[i] is already a fully-constructed Finger(0, 100) if we want
    // a different range, we can do that in the constructor's initializer.

    connectPwmChannels();
}

void Hand::connectPwmChannels()
{
    // Attempt to connect a channel for each finger
    for (uint8_t i = 0; i < fingerCount; i++)
    {
        if (!isFingerConnected[i])
        {
            auto channel = controller->ConnectChannel();
            if (channel != IPca9685Controller::Channels::Channel_none)
            {
                pwmChannel[i] = channel;
                isFingerConnected[i] = true;
            }
            else
            {
                // No more available channels
                break;
            }
        }
    }
}

bool Hand::isInitialized() const
{
    // Example: check if all 5 fingers are connected
    for (uint8_t i = 0; i < fingerCount; i++)
        if (!isFingerConnected[i])
            return false;

    return true;
}

void Hand::OpenHand(uint32_t delayMs)
{
    for (uint8_t i = 0; i < fingerCount; i++)
        OpenFinger(static_cast<FingerType>(i), delayMs);
}

void Hand::CloseHand(uint32_t delayMs)
{
    for (uint8_t i = 0; i < fingerCount; i++)
        CloseFinger(static_cast<FingerType>(i), delayMs);
}

void Hand::OpenHandSequential(uint32_t delayBetweenFingersMs)
{
    for (uint8_t i = 0; i < fingerCount; i++)
        OpenFinger(static_cast<FingerType>(i), delayBetweenFingersMs);
}

void Hand::CloseHandSequential(uint32_t delayBetweenFingersMs)
{
    for (uint8_t i = 0; i < fingerCount; i++)
        CloseFinger(static_cast<FingerType>(i), delayBetweenFingersMs);
}

void Hand::OpenHandAllAtOnce(uint32_t finalDelayMs)
{
    for (uint8_t i = 0; i < fingerCount; i++)
    {
        uint32_t d = (i == fingerCount - 1) ? finalDelayMs : 0;
        OpenFinger(static_cast<FingerType>(i), d);
    }
}

void Hand::CloseHandAllAtOnce(uint32_t finalDelayMs)
{
    for (uint8_t i = 0; i < fingerCount; i++)
    {
        uint32_t d = (i == fingerCount - 1) ? finalDelayMs : 0;
        CloseFinger(static_cast<FingerType>(i), d);
    }
}

void Hand::MoveFinger(FingerType finger, uint8_t percentage, uint32_t delayMs)
{
    if (finger < fingerCount)
    {
        // Just an example: invert percentage for Thumb
        uint8_t actualPercentage = (finger == Thumb) ? (100 - percentage) : (percentage);

        uint16_t offSteps = fingers[finger].Move(actualPercentage);
        SendFingerCommand(finger, offSteps, delayMs);
    }
}

void Hand::OpenFinger(FingerType finger, uint32_t delayMs)
{
    if (finger < fingerCount)
    {
        uint16_t offSteps = (finger == Thumb)
            ? fingers[finger].Close()   // invert for thumb
            : fingers[finger].Open();
        SendFingerCommand(finger, offSteps, delayMs);
    }
}

void Hand::CloseFinger(FingerType finger, uint32_t delayMs)
{
    if (finger < fingerCount)
    {
        uint16_t offSteps = (finger == Thumb)
            ? fingers[finger].Open()
            : fingers[finger].Close();
        SendFingerCommand(finger, offSteps, delayMs);
    }
}

void Hand::SendFingerCommand(FingerType finger, uint16_t offSteps, uint32_t delayMs)
{
    // Convert channel enum to register address
    auto channel = pwmChannel[finger];
    uint8_t regAddr = static_cast<uint8_t>(channel);

    uint8_t data[4] = {
        0x00,                               // ON_L
        0x00,                               // ON_H
        static_cast<uint8_t>(offSteps & 0xFF),       // OFF_L
        static_cast<uint8_t>((offSteps >> 8) & 0x0F)  // OFF_H (only lower 4 bits)
    };

    Message msg(controller->GetRawAddress(), regAddr, data, delayMs);
    controller->EnqueueMessage(msg);
}

void Hand::Wiggle()
{
    CloseHand(0);
    uint32_t moveDelay = 500;

    MoveFinger(Thumb,  100, moveDelay);
    MoveFinger(Index,  100, moveDelay);
    MoveFinger(Middle, 100, moveDelay);
    MoveFinger(Ring,   100, moveDelay);
    MoveFinger(Pinky,  100, moveDelay);

    MoveFinger(Pinky,  0, moveDelay);
    MoveFinger(Ring,   0, moveDelay);
    MoveFinger(Middle, 0, moveDelay);
    MoveFinger(Index,  0, moveDelay);
    MoveFinger(Thumb,  0, moveDelay);
}

void Hand::WaveMotion(uint8_t delayTime, uint8_t openCloseStep, int cycles)
{
    for (int cycle = 0; cycle < cycles; ++cycle)
    {
        for (int i = 0; i <= 100; i += openCloseStep)
        {
            MoveFinger(Thumb,  i, delayTime);
            MoveFinger(Index,  static_cast<uint8_t>((i > 10) ? i - 10 : 0), delayTime);
            MoveFinger(Middle, static_cast<uint8_t>((i > 20) ? i - 20 : 0), delayTime);
            MoveFinger(Ring,   static_cast<uint8_t>((i > 30) ? i - 30 : 0), delayTime);
            MoveFinger(Pinky,  static_cast<uint8_t>((i > 40) ? i - 40 : 0), delayTime);
        }
        for (int i = 100; i >= 0; i -= openCloseStep)
        {
            MoveFinger(Thumb,  i, delayTime);
            MoveFinger(Index,  static_cast<uint8_t>((i > 10) ? i - 10 : 0), delayTime);
            MoveFinger(Middle, static_cast<uint8_t>((i > 20) ? i - 20 : 0), delayTime);
            MoveFinger(Ring,   static_cast<uint8_t>((i > 30) ? i - 30 : 0), delayTime);
            MoveFinger(Pinky,  static_cast<uint8_t>((i > 40) ? i - 40 : 0), delayTime);
        }
    }
}
