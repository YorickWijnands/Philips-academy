#ifndef I_PCA9685_CONTROLLER_MANAGER_HPP
#define I_PCA9685_CONTROLLER_MANAGER_HPP

#include <cstdint>
#include "IPca9685Controller.hpp"
#include "IMessageQueue.hpp"

class IPca9685ControllerManager
{
public:
    virtual ~IPca9685ControllerManager() = default;

    virtual IPca9685Controller* AddController(uint8_t address) = 0;
    virtual IPca9685Controller* GetController(uint8_t address) = 0;
    virtual IMessageQueue& GetMessageQueue() = 0;
};

#endif // I_PCA9685_CONTROLLER_MANAGER_HPP
