#ifndef I_FINGER_HPP
#define I_FINGER_HPP

#include <cstdint>

class IFinger
{
public:
    virtual ~IFinger() = default;

    virtual uint16_t Move(uint8_t percentage) = 0;
    virtual uint8_t GetPosition() const = 0;
    virtual uint16_t Open() = 0;
    virtual uint16_t Close() = 0;
    virtual uint16_t GetPwmFromPercentage(uint8_t percentage) const = 0;
};

#endif // I_FINGER_HPP
