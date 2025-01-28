#include "hal_st/instantiations/NucleoUi.hpp"
#include "hal_st/instantiations/StmEventInfrastructure.hpp"
#include "hal_st/stm32fxxx/GpioStm.hpp"
#include "hal_st/stm32fxxx/I2cStm.hpp"
#include "hal/interfaces/I2cRegisterAccess.hpp"
#include "stm32f4xx_hal.h"
#include <cstdint>

// ERROR CODES
#define PCA9685_OK                  0x00
#define PCA9685_ERROR               0xFF
#define PCA9685_ERR_CHANNEL         0xFE
#define PCA9685_ERR_MODE            0xFD
#define PCA9685_ERR_I2C             0xFC

//  get/setFrequency()
#define PCA9685_MIN_FREQ              24
#define PCA9685_MAX_FREQ            1526


//  REGISTERS CONFIGURATION - check datasheet for details
#define PCA9685_MODE1               0x00
#define PCA9685_MODE2               0x01

//  Configuration bits MODE1 register
#define PCA9685_MODE1_RESTART       0x80  //  0 = disable      1 = enable
#define PCA9685_MODE1_EXTCLK        0x40  //  0 = internal     1 = external (datasheet)
#define PCA9685_MODE1_AUTOINCR      0x20  //  0 = disable      1 = enable
#define PCA9685_MODE1_SLEEP         0x10  //  0 = normal       1 = sleep
#define PCA9685_MODE1_SUB1          0x08  //  0 = disable      1 = enable
#define PCA9685_MODE1_SUB2          0x04  //  0 = disable      1 = enable
#define PCA9685_MODE1_SUB3          0x02  //  0 = disable      1 = enable
#define PCA9685_MODE1_ALLCALL       0x01  //  0 = disable      1 = enable
#define PCA9685_MODE1_NONE          0x00

//  Configuration bits MODE2 register
#define PCA9685_MODE2_INVERT        0x10  //  0 = normal       1 = inverted
#define PCA9685_MODE2_ACK           0x08  //  0 = on STOP      1 = on ACK
#define PCA9685_MODE2_TOTEMPOLE     0x04  //  0 = open drain   1 = totem-pole
#define PCA9685_MODE2_OUTNE         0x03  //  datasheet
#define PCA9685_MODE2_NONE          0x00

//  (since 0.4.0)
#define PCA9685_SUBADR(x)           (0x01 + (x))  //  x = 1..3
#define PCA9685_ALLCALLADR          0x05

// REGISTERS - CHANNELS
//  0x06 + 4*channel is base per channel
#define PCA9685_CHANNEL_0           0x06
#define PCA9685_CHANNEL(x)          (0x06 + ((x) * 4))  //  x = 0..15


//  REGISTERS - ALL_ON ALL_OFF - partly implemented
#define PCA9685_ALL_ON_L            0xFA
#define PCA9685_ALL_ON_H            0xFB
#define PCA9685_ALL_OFF_L           0xFC
#define PCA9685_ALL_OFF_H           0xFD   //  used for allOFF()

// REGISTERS - FREQUENCY
#define PCA9685_PRE_SCALER          0xFE

//  NOT IMPLEMENTED
//  WARNING: DO NOT USE THIS REGISTER (see datasheet)
#define PCA9685_TESTMODE            0xFF   //  do not be use. see datasheet.

unsigned int hse_value = 8'000'000;

static main_::NUCLEO ui;
static hal::I2cMasterRegisterAccessByte* pca9685Ptr = nullptr;

void Stap10(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x09;
    uint8_t data = 0x01;
    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        ui.ledBlue.Set(true);
    });
}

void Stap9(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x08;
    uint8_t data = 0xE8;
    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        Stap10(pca9685);
    });
}

void Stap8(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x07;
    uint8_t data = 0x00;
    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        Stap9(pca9685);
    });
}

void Stap7(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x06;
    uint8_t data = 0x00;
    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        Stap8(pca9685);
    });
}

void Stap6(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x05;
    uint8_t data = 0x20;
    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        Stap7(pca9685);
    });
}

void Stap5(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x04;
    uint8_t data = 0x80;
    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        Stap6(pca9685);
    });
}

void Stap4(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x03;
    uint8_t data = 0x00;
    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        Stap5(pca9685);
    });
}

void Stap3(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x00;
    uint8_t data = 0x00;
    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        Stap4(pca9685);
    });
}

void Stap2(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x00;
    uint8_t data[] = {0x00, 0x80};
    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        Stap3(pca9685);
    });
}

void Stap1(hal::I2cMasterRegisterAccessByte& pca9685) {
    uint8_t reg = 0x00;
    uint8_t data = 0xFF;

    pca9685.WriteRegister(reg, infra::MakeConstByteRange(data), [&pca9685]() {
        Stap2(pca9685);
    });
}

int main() {
    HAL_Init();

    static main_::StmEventInfrastructure eventInfrastructure;

    hal::GpioPinStm scl(hal::Port::B, 8, hal::Drive::Default, hal::Speed::Default, hal::WeakPull::Up);
    hal::GpioPinStm sda(hal::Port::B, 9, hal::Drive::Default, hal::Speed::Default, hal::WeakPull::Up);

    hal::I2cStm i2cMaster(1, scl, sda);
    hal::I2cAddress pca9685Address(0x40);

    hal::I2cMasterRegisterAccessByte pca9685(i2cMaster, pca9685Address);
    pca9685Ptr = &pca9685;
    
    Stap1(*pca9685Ptr);

    eventInfrastructure.Run();
    __builtin_unreachable();
}