#ifndef I_HAND_HPP
#define I_HAND_HPP

#include <cstdint>

class IHand
{
public:
    // Make sure you have a virtual destructor in your interface
    virtual ~IHand() = default;

    // Provide the FingerType enum *inside* IHand if you want it scoped as IHand::FingerType
    enum FingerType
    {
        Thumb = 0,
        Index = 1,
        Middle = 2,
        Ring = 3,
        Pinky = 4
    };

    // Your interface methods
    virtual bool isInitialized() const = 0;
    virtual void OpenHand(uint32_t delayMs = 0) = 0;
    virtual void CloseHand(uint32_t delayMs = 0) = 0;
    virtual void OpenHandSequential(uint32_t delayBetweenFingersMs) = 0;
    virtual void CloseHandSequential(uint32_t delayBetweenFingersMs) = 0;
    virtual void OpenHandAllAtOnce(uint32_t finalDelayMs) = 0;
    virtual void CloseHandAllAtOnce(uint32_t finalDelayMs) = 0;
    virtual void MoveFinger(FingerType finger, uint8_t percentage, uint32_t delayMs = 0) = 0;
    virtual void OpenFinger(FingerType finger, uint32_t delayMs = 0) = 0;
    virtual void CloseFinger(FingerType finger, uint32_t delayMs = 0) = 0;
    virtual void Wiggle() = 0;
    virtual void WaveMotion(uint8_t delayTime, uint8_t openCloseStep, int cycles) = 0;
};

#endif // I_HAND_HPP
