#include "Pca9685ControllerManager.hpp"
#include <chrono>

// Static
MessageQueue 
    Pca9685ControllerManager::messageQueue;

Pca9685ControllerManager::Pca9685ControllerManager()
{
    Run();
}

Pca9685ControllerManager::Pca9685ControllerManager(
    I2CConfig config)
    : config(config)
    , scl(hal::Port::B, config.sclPin)
    , sda(hal::Port::B, config.sdaPin)
    , i2cMaster(config.i2cIndex, scl, sda)
{
    Run();
}

IPca9685Controller* 
Pca9685ControllerManager::AddController(uint8_t address)
{
    for (auto& controllerOpt : controllers)
    {
        if (!controllerOpt) // empty
        {
            controllerOpt.Emplace(address, *this); // create new
            return &(*controllerOpt);
        }
    }
    return nullptr;
}

IPca9685Controller* 
Pca9685ControllerManager::GetController(uint8_t address)
{
    for (auto& controllerOpt : controllers)
    {
        if (controllerOpt && controllerOpt->GetRawAddress() == address)
            return &(*controllerOpt);
    }
    return nullptr;
}

IMessageQueue& 
Pca9685ControllerManager::GetMessageQueue()
{
    return messageQueue;
}

void Pca9685ControllerManager::Run()
{
    // Repeatedly check if we can send next message
    static infra::TimerRepeating timerRepeating{
        std::chrono::microseconds{1}, [this]
        {
            if (isI2cAvailable)
                WriteNextMessage();
        }
    };
}

void Pca9685ControllerManager::WriteNextMessage()
{
    if (messageQueue.IsEmpty())
        return;

    isI2cAvailable = false;
    currentMessage = messageQueue.Dequeue();
    registerAddress = currentMessage.GetRegisterAddress();
    singleData      = currentMessage.GetSingleData();

    // Copy data
    for (size_t i = 0; i < dataSize; ++i)
        dataArray[i] = currentMessage.GetData()[i];

    WriteRegister();
}

void Pca9685ControllerManager::WriteRegister()
{
    auto registerRange = infra::MakeByteRange(registerAddress);

    i2cMaster.SendData(
        hal::I2cAddress{currentMessage.GetI2cAddress()},
        registerRange,
        currentMessage.HasRegisterAndData() ? hal::Action::continueSession : hal::Action::stop,
        [this](hal::Result result, size_t /*bytesSent*/)
        {
            if (result == hal::Result::complete && currentMessage.HasRegisterAndData())
            {
                auto dataRange = currentMessage.HasSingleData()
                    ? infra::MakeByteRange(singleData)
                    : infra::MakeByteRange(dataArray);

                i2cMaster.SendData(
                    hal::I2cAddress{currentMessage.GetI2cAddress()},
                    dataRange,
                    hal::Action::stop,
                    [this](hal::Result resultData, size_t /*bytesSent*/)
                    {
                        if (resultData == hal::Result::complete)
                        {
                            OnWriteDone();
                        }
                        else
                        {
                            // Handle error if needed
                        }
                    });
            }
            else
            {
                OnWriteDone();
            }
        });
}


void Pca9685ControllerManager::OnWriteDone()
{
    uint32_t delay = currentMessage.GetDelayMs();
    if (delay > 0)
    {
        reEnableI2cTimer.Start(std::chrono::milliseconds(delay), [&]()
        {
            isI2cAvailable = true;
        });
    }
    else
    {
        isI2cAvailable = true;
    }
}
