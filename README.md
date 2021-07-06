# SlimeVR Tracker firmware for ESP

Firmware for ESP8266 / ESP32 microcontrollers and different IMU sensors to use them as a vive-like trackers in VR.

Requires [SlimeVR Server](https://github.com/SlimeVR/SlimeVR-Server) to work with SteamVR and resolve pose. Should be compatible with [owoTrack](https://github.com/abb128/owo-track-driver), but is not guaranteed.

## Compatibility

Compatible and tested with these IMUs (select during compilation):
* BNO085, BNO086
  * Using any fusion in internal DMP. Best results with ARVR Stabilized Game Rotation Vector or ARVR Stabilized Rotation Vector if in good magnetic environment
* BNO080
  * Using any fusion in internal DMP. Doesn't have BNO085's ARVR stabilization, but still gives good results.
* BNO055
  * Work in progress. Should be roughly equal BNO080, but cheaper
* MPU-9250
  * Using Mahony sensor fusion of Gyroscope, Magnetometer and Accelerometer, requires good magnetic environment
* MPU-6500
  * Using internal DMP to fuse Gyroscope and Accelerometer, can be used with MPU-9250, can drift substantially
* MPU-6050
  * Same as MPU-6500

Firmware can work with both ESP8266 and ESP32. Please edit defines.h and set your pinout properly according to how you connected the IMU.

<br /><br /><br />

# ICM 20948 *** BREAKS 8266 COMPATIBILITY | NO SECONDARY TRACKER SUPPORT ***

### Hardware 

Tested on a ESP32-Wrover with 18650 module using generic 20948 breakout boards from aliexpress with additional 1.8v regulator and a 4 way I2C bi-directional level shifter (SDA, SCL, INT)

Note: The 18650 module has a 5v boost chip which appears to be completely redundant for this and wastes a fair bit of power. Consider modding it out.
https://www.youtube.com/watch?v=joAkJ9QA2bw

Links are for hardware reference, not seller endorsement.
* https://www.aliexpress.com/item/32951730747.html
* https://www.aliexpress.com/item/1736297058.html?spm=a2g0o.productlist.0.0.56585939a9rGKH&algo_pvid=809a80b6-0946-4ba6-ad04-e67f409ab424&algo_exp_id=809a80b6-0946-4ba6-ad04-e67f409ab424-3
* 1.8v https://www.aliexpress.com/item/1005002063250660.html?spm=a2g0o.productlist.0.0.32c43e7dQ0HHwc&algo_pvid=b027eefb-c58e-4004-a2da-a06cf0e1c766&algo_exp_id=b027eefb-c58e-4004-a2da-a06cf0e1c766-29

<br />

### Firmware

Uses additional libraries: Arduino-timer (time trigger for save event) and a modified version of https://github.com/isouriadakis/Arduino_ICM20948_DMP_Full-Function \
Modification includes an extra sensor stream to subscribe to, and accessor methods for the calibration bias registors

The 20948 auto calibrates but doesn't store calibration for start-up next boot, so it's being saved and loaded to the NVS partition here. Would be nice to use the same config locations (EEPROM blob) as main repo but the online calibration / more frequent write cycles makes me use preferences.h (ESP32 only) with the NVS wear leveling for peace of mind


### TODO:

* Bring back ESP8266 compatibility (a library for NVS saving that is compatible with both ESP8266 && ESP32 is definitely a problem, may be other issues (uses more memory?))
* Add a tap detection as an input button
* Make setup of imu mounting matrix more obvious (example can be seen with default matrix in library file Arduino-ICM20948.cpp)
* Improve battery usage using no motion detection to improve low power states (wifi/cpu cores/delays etc)
* Explicitly correct for 20948 multi-tracker support (at least one extra extension although intending to use i2c multiplexor)
