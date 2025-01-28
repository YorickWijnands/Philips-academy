#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdint>

class Message
{
public:
    Message();
    Message(uint16_t i2cAddr, uint8_t regAddr, uint8_t singleData, uint32_t delay = 0);
    Message(uint16_t i2cAddr, uint8_t regAddr, const uint8_t inputData[4], uint32_t delay = 0);
    uint16_t GetI2cAddress() const;
    uint8_t GetRegisterAddress() const;
    uint8_t GetSingleData() const;
    const uint8_t* GetData() const;
    bool HasRegisterAndData() const;
    bool HasSingleData() const;
    uint32_t GetDelayMs() const;

private:
    uint16_t i2cAddress;
    uint8_t registerAddress;
    uint8_t updatedSingleData;
    uint8_t data[4];
    bool hasData;
    bool hasSingleData;
    uint32_t delayMs;
};

#endif
