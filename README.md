
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

* Should be roughly equal BNO080, but cheaper. Not tested thoroughly, please report your results on Discord if you're willing to try.

* MPU-9250

* Using Mahony sensor fusion of Gyroscope, Magnetometer and Accelerometer, requires good magnetic environment.

* NOTE: Currently can't be calibrated due to lack of proper commands from the server. Work in progress. Can be ran as MPU-6050 below w/o magnetometer.

* MPU-6500 & MPU-6050

* Using internal DMP to fuse Gyroscope and Accelerometer, can be used with MPU-9250 to use it without accelerometer, can drift substantially.

* NOTE: Currently the MPU will auto calibrate when powered on. You *must* place it on the ground and *DO NOT* move it until calibration is complete (for a few seconds). **LED on the ESP will blink 5 times after calibration is over.**

  

Firmware can work with both ESP8266 and ESP32. Please edit defines.h and set your pinout properly according to how you connected the IMU.

  <br  /><br  />  

# ICM 20948 *** Extension tracker supported ***


### Hardware  

Tested on a ESP32-Wrover with 18650 module using generic 20948 breakout boards from aliexpress with additional 1.8v regulator and a 4 way I2C bi-directional level shifter (SDA, SCL, INT)  

Note: The 18650 module has a 5v boost chip which appears to be completely redundant for this and wastes a fair bit of power. Consider modding it out.

https://www.youtube.com/watch?v=joAkJ9QA2bw

Unlike BNO, AD0 pin needs pulling HIGH for address select and runs at 1.8v logic.

Links are for hardware reference, not seller endorsement.

* [ESP32 with 18650 Battery Shield ](https://www.aliexpress.com/item/32951730747.html)
* [Logic Level Shifter](https://www.aliexpress.com/item/1736297058.html?spm=a2g0o.productlist.0.0.56585939a9rGKH&algo_pvid=809a80b6-0946-4ba6-ad04-e67f409ab424&algo_exp_id=809a80b6-0946-4ba6-ad04-e67f409ab424-3)
* [1.8v Voltage Regulator](https://www.aliexpress.com/item/1005002063250660.html?spm=a2g0o.productlist.0.0.32c43e7dQ0HHwc&algo_pvid=b027eefb-c58e-4004-a2da-a06cf0e1c766&algo_exp_id=b027eefb-c58e-4004-a2da-a06cf0e1c766-29)
* [ICM-20948 IMU](https://www.aliexpress.com/item/1005001994630895.html?spm=a2g0o.productlist.0.0.426a1732taJbR1&algo_pvid=14184931-ac89-4578-bde3-3f7c15944b19&algo_exp_id=14184931-ac89-4578-bde3-3f7c15944b19-1)

### Firmware  

Uses additional libraries: Arduino-timer (time trigger for save event) and a modified version of https://github.com/isouriadakis/Arduino_ICM20948_DMP_Full-Function

Modification includes an extra sensor stream to subscribe to, support for more than one connected IMU (only i2c tested but spi should be ok) and accessor methods for the calibration bias registors.

The 20948 auto calibrates but doesn't store calibration for start-up next boot, so it's being saved and loaded to the NVS partition here. Would be nice to use the same config locations (EEPROM blob) as main repo but the online calibration / more frequent write cycles makes me use preferences.h (ESP32 only) with the NVS wear leveling for peace of mind  

### TODO:

* Make ESP8266 save bias values (a library for NVS saving that is compatible with both ESP8266 && ESP32 is definitely a problem, may be other compatibility issues (untested))
* Use the tap detection for an input button, or reset
* Improve battery usage using no motion detection to improve low power states (wifi/cpu cores/delays etc)
* Support > 1 extension tracker through i2c multiplexor
