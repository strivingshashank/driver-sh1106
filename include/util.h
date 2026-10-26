#ifndef UTIL_H
#define UTIL_H

#define MICRO_TO_MILLI(x) (x / 1000)
#define KILO(x) (x * 1000)
#define MEGA(x) (KILO(x) * 1000)

#define I2C_PORT i2c0
#define DISPLAY_ADDR 0x3C
#define BAUD_RATE MEGA(1)
#define SDA_PIN 4
#define SCL_PIN 5

#endif
