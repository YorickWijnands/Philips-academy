#ifndef HAND_HPP
#define HAND_HPP

#include "IHand.hpp"
#include "Finger.hpp" 
#include "IPca9685Controller.hpp"
#include <cstdint>

class Hand : public IHand
{
public:
    static constexpr uint8_t fingerCount = 5;

    Hand(IPca9685Controller* controller);

    // Override from IHand
    bool isInitialized() const override;
    void OpenHand(uint32_t delayMs = 0) override;
    void CloseHand(uint32_t delayMs = 0) override;
    void OpenHandSequential(uint32_t delayBetweenFingersMs) override;
    void CloseHandSequential(uint32_t delayBetweenFingersMs) override;
    void OpenHandAllAtOnce(uint32_t finalDelayMs) override;
    void CloseHandAllAtOnce(uint32_t finalDelayMs) override;
    void MoveFinger(FingerType finger, uint8_t percentage, uint32_t delayMs = 0) override;
    void OpenFinger(FingerType finger, uint32_t delayMs = 0) override;
    void CloseFinger(FingerType finger, uint32_t delayMs = 0) override;
    void Wiggle() override;
    void WaveMotion(uint8_t delayTime, uint8_t openCloseStep, int cycles) override;

private:
    void connectPwmChannels();
    void SendFingerCommand(FingerType finger, uint16_t offSteps, uint32_t delayMs);

private:
    IPca9685Controller* controller;
    Finger fingers[fingerCount];

    bool isFingerConnected[fingerCount];
    IPca9685Controller::Channels pwmChannel[fingerCount];
};

#endif // HAND_HPP
