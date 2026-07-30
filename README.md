# PhaseLab-System-Display-i2c
PhaseLab System Display C++ / Arduino firmware for monitoring dual-channel temperatures (LM35) and signal levels with I2C LCD display, moving average filtering, and EEPROM state persistence.


## PREVIEW
[![VIKODK67](https://thumbs.wokwi.com/projects/470877345133871105/social/1785322480223.png)](https://wokwi.com/projects/470877345133871105)
## Features command serial monitor

- CAL_CA=VALUE (500 - 1023)
- CAL_CB=VALUE (500 - 1023)
- NAME=PHASELAB CUY (Change watermark intro)
- RESET (Reset default configuration EEPROM)
- SHOW (Show value CAL_CA CAL_CB)

## List component standalone
- ATMEGA328P
```C++
// ==== PIN ====
const int pinTA = A0; // pin 23 pada atmega328p Temperature A
const int pinTB = A1; // pin 24 pada atmega328p Temperature B
const int pinCA = A2; // pin 25 pada atmega328p Channel A
const int pinCB = A3; // pin 26 pada atmega328p Channel B
```
![VIKODK67](https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEh0TVoILaP9KEIKJdl5hCCFq3vecXyEv8tIxx31YUGUs4VQIvozm1D2lGwIlZHWhVbyAXLZb38v-BPN7oFjmdmzHN21dYkuyYFNLvNHUDoi4fWKcIitqAXffh-v7USWwZEA6skzaZ1u2bQ/s1600/51aYnf8cw7L.jpg)
- OSCILATOR 16MHZ XTAL
- Capacitor non-polar (22pf) & (100nf - coupling Analog)
- Resistor 1K (For Reset button)
- LM7805/ams1117 5v (Stepdown 12V to 5V)
- Diode (Protector)
- Liquid Crystal LCD 16x2 I2C
- Potentiometer 10/50K
- Capacitor polar (1000uF 6.3V)
- Push button
- LM35 (Sensor Temperature)
- PCB board double-layer
