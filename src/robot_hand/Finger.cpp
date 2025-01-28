#include "Finger.hpp"

Finger::Finger(uint8_t minPos, uint8_t maxPos)
    : currentPosition(minPos)
    , minPosition(minPos)
    , maxPosition(maxPos)
{
}

uint16_t Finger::Move(uint8_t percentage)
{
    if (percentage < minPosition)
        percentage = minPosition;
    if (percentage > maxPosition)
        percentage = maxPosition;

    currentPosition = percentage;
    return GetPwmFromPercentage(currentPosition);
}

uint8_t Finger::GetPosition() const
{
    return currentPosition;
}

uint16_t Finger::Open()
{
    return Move(maxPosition);
}

uint16_t Finger::Close()
{
    return Move(minPosition);
}

uint16_t Finger::GetPwmFromPercentage(uint8_t percentage) const
{
    uint16_t minPulseWidth = 500;
    uint16_t maxPulseWidth = 2500;
    uint32_t pulseWidth =
        minPulseWidth + (static_cast<uint32_t>(percentage) * (maxPulseWidth - minPulseWidth) / 100);

    uint32_t steps = (pulseWidth * 4096UL) / 20000UL;
    if (steps > 4095)
        steps = 4095;

    return static_cast<uint16_t>(steps);
}
