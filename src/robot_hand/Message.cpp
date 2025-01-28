#include "Message.hpp"

Message::Message()
    : i2cAddress(0), registerAddress(0), updatedSingleData(0xff), hasData(false), hasSingleData(false), delayMs(0)
{
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
}

Message::Message(uint16_t i2cAddr, uint8_t regAddr, uint8_t singleData, uint32_t delay)
    : i2cAddress(uint16_t(i2cAddr)), registerAddress(regAddr), updatedSingleData(singleData),
      hasData(true), hasSingleData(true), delayMs(delay)
{
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
}

Message::Message(uint16_t i2cAddr, uint8_t regAddr, const uint8_t inputData[4], uint32_t delay)
    : i2cAddress(i2cAddr), registerAddress(regAddr),
      updatedSingleData(0xff), hasData(true), hasSingleData(false), delayMs(delay)
{
    data[0] = inputData[0];
    data[1] = inputData[1];
    data[2] = inputData[2];
    data[3] = inputData[3];
}

uint16_t Message::GetI2cAddress() const
{
    return i2cAddress;
}

uint8_t Message::GetRegisterAddress() const
{
    return registerAddress;
}

uint8_t Message::GetSingleData() const
{
    return updatedSingleData;
}

const uint8_t* Message::GetData() const
{
    return data;
}

bool Message::HasRegisterAndData() const
{
    return hasData;
}

bool Message::HasSingleData() const
{
    return hasSingleData;
}

uint32_t Message::GetDelayMs() const
{
    return delayMs;
}
