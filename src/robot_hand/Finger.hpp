#ifndef FINGER_HPP
#define FINGER_HPP

#include "IFinger.hpp"

class Finger : public IFinger
{
public:
    // Provide a constructor if needed
    Finger(uint8_t minPos = 0, uint8_t maxPos = 100);
    
    // IFinger overrides
    uint16_t Move(uint8_t percentage) override;
    uint8_t GetPosition() const override;
    uint16_t Open() override;
    uint16_t Close() override;
    uint16_t GetPwmFromPercentage(uint8_t percentage) const override;

private:
    uint8_t currentPosition;
    uint8_t minPosition;
    uint8_t maxPosition;
};

#endif // FINGER_HPP
