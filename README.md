# wisblock-rtc
Pico SDK C implementation of RV-3028 library for RAK12002 RTC. This will also work on a Raspberry Pi Pico.

The RV3028 interface code is based on the Melopero_RV3028 source. The original code works well for writing/reading time but does not work properly for reading/writing to user EEPROM. Changes are made to write a 0 to the EEPROM_COMMAN_ADDRESS prior to writing any other command (as per the data sheet) and putting in waits while the device it busy.


