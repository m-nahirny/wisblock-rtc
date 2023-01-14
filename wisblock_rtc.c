/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "RV3028.h"

#define LED_GREEN 23
#define LED_BLUE 24

#define IO1 6
#define IO2 22

#define UART1TX 4
#define UART1Rx 5

const uint I2C0SDA = 20;
const uint I2C0SCL = 21;
const uint I2C1SDA = 2;
const uint I2C1SCL = 3;

void printTime(){
    char print_buf[200];
    sprintf(print_buf, "%d-%d-%d %d:%d:%d\r\n", getYear(), getMonth(), getDate(), getHour(), getMinute(), getSecond());
    uart_puts(uart1, print_buf);
}

int main() {
    stdio_init_all();

    gpio_set_function(I2C1SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C1SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C1SDA);
    gpio_pull_up(I2C1SCL);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(IO1);
    gpio_set_dir(IO1, GPIO_OUT);

    gpio_init(IO2);
    gpio_set_dir(IO2, GPIO_OUT);

    uart_init(uart1, 115200);
    gpio_set_function(UART1TX, GPIO_FUNC_UART);
    gpio_set_function(UART1Rx, GPIO_FUNC_UART);

    sleep_ms(1000);

    uart_puts(uart1, "\r\nInitializing I2C\r\n");
    uint res = i2c_init(i2c_rak, 400 * 1000);

    char print_buf[200];
    sprintf(print_buf, "I2C rate is %d\r\n", res);
    uart_puts(uart1, print_buf);

    set24HourMode();
    // Set the date and time:
    setTime(2023, 1, 7, 7, 15, 20, 0);
    // year, month, weekday, date, hour, minute, second
    // Note: time is always set in 24h format
    // Note: month value ranges from 1 (Jan) to 12 (Dec)
    // Note: date value ranges from 1 to 31


    uint8_t val2 = 0;
    uart_puts(uart1, "Read values from EEPROM: ");
    val2 = readEEPROMRegister(1);
    sprintf(print_buf, "%02x", val2);
    uart_puts(uart1, print_buf);
    val2 = readEEPROMRegister(2);
    sprintf(print_buf, "%02x", val2);
    uart_puts(uart1, print_buf);
    val2 = readEEPROMRegister(3);
    sprintf(print_buf, "%02x", val2);
    uart_puts(uart1, print_buf);
    val2 = readEEPROMRegister(4);
    sprintf(print_buf, "%02x", val2);
    uart_puts(uart1, print_buf);
    val2 = readEEPROMRegister(5);
    sprintf(print_buf, "%02x", val2);
    uart_puts(uart1, print_buf);
    val2 = readEEPROMRegister(6);
    sprintf(print_buf, "%02x", val2);
    uart_puts(uart1, print_buf);
    uart_puts(uart1, "\r\n");

    uart_puts(uart1, "Writing to EEPROM\r\n");
    writeEEPROMRegister(1, 0x12);
    writeEEPROMRegister(2, 0x34);
    writeEEPROMRegister(3, 0x56);
    writeEEPROMRegister(4, 0xAB);
    writeEEPROMRegister(5, 0xCD);
    writeEEPROMRegister(6, 0xEF);

    while (1) {
        gpio_put(LED_GREEN, 1);
        gpio_put(IO1, 1);
        gpio_put(IO2, 1);
        sleep_ms(250);
        gpio_put(LED_GREEN, 0);
        gpio_put(IO1, 0);
        gpio_put(IO2, 0);
        sleep_ms(750);
          
        // print datetime every second
        printTime();
    }
}
