# PhaseLab-System-Display-i2c
PhaseLab System Display C++ / Arduino firmware for monitoring dual-channel temperatures (LM35) and signal levels with I2C LCD display, moving average filtering, and EEPROM state persistence.

<div align="left">
  <a href="https://wokwi.com/projects/470877345133871105">
  <img src="https://thumbs.wokwi.com/projects/470877345133871105/social/1785322480223.png" width="400px" alt="Preview demo">
  <h3>Simulated on Wokwi</h3>
  </a>
</div>

## Component Standalone
- Potensio 10K/50K
- Crystal 16MHZ Xtal
- Capacitor non-polar 22pf
- Resistor 10K (For Pin Reset)
- IC LM35 (input 5-30V Volt DC)
- Modul I2C (SDA SCL)
- LCD Liquid Crystal Display (16x2)
- Diode
- LED diode (For Power & RX TX)
- IC 7805 (stepdown 12v - 5v)
- Capacitor polar (6.3v 1000uF LOW ESR (RECOMENDED))
- perfboard double layer
<div align="left">
  <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSE-YhYBIs_LQMz-zw7nJloBMXKLaZadkGcZVDA4e1nkegPGGZvhbqNlKCY&s=10" width="300px" alt="Preview demo">
</div>

## Change Name display Watermark
#### - Bautrate 9600
## Command (SET WATERMARK)
```bash
NAME=HALLO DUNIA
```
## Command (DELETE WATERMARK (DEFAULT))
```bash
RESET
```
