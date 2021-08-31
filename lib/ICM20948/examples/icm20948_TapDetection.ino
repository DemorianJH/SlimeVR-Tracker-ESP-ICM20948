// Modified lib originally from https://github.com/isouriadakis/Arduino_ICM20948_DMP_Full-Function
// Uses a butterworth filter to detect an arbitrary number of taps from accel data

// ICM20948 implementation is missing the tap feature - example shows how to process taps from accel.

#include "Arduino-ICM20948.h"
#include <Wire.h>
#include "TapDetector.h"

#define I2C_SDA 21
#define I2C_SCL 22

ArduinoICM20948 icm20948;
ArduinoICM20948Settings icmSettings =
{
  .i2c_speed = 400000,                // i2c clock speed
  .i2c_address = 0x69,                // i2c address
  .is_SPI = false,                    // Enable SPI, if disable use i2c
  .cs_pin = 10,                       // SPI chip select pin
  .spi_speed = 7000000,               // SPI clock speed in Hz, max speed is 7MHz
  .mode = 1,                          // 0 = low power mode, 1 = high performance mode
  .enable_gyroscope = false,           // Enables gyroscope output
  .enable_accelerometer = true,       // Enables accelerometer output
  .enable_magnetometer = false,        // Enables magnetometer output // Enables quaternion output
  .enable_gravity = false,             // Enables gravity vector output
  .enable_linearAcceleration = false,  // Enables linear acceleration output
  .enable_quaternion6 = false,         // Enables quaternion 6DOF output
  .enable_quaternion9 = false,         // Enables quaternion 9DOF output
  .enable_har = false,                 // Enables activity recognition
  .enable_steps = false,               // Enables step counter
  .enable_step_detector = false,       // Enables step detector
  .gyroscope_frequency = 1,           // Max frequency = 225, min frequency = 1
  .accelerometer_frequency = 200,      // Max frequency = 225, min frequency = 1
  .magnetometer_frequency = 1,        // Max frequency = 70, min frequency = 1 
  .gravity_frequency = 1,             // Max frequency = 225, min frequency = 1
  .linearAcceleration_frequency = 1,  // Max frequency = 225, min frequency = 1
  .quaternion6_frequency = 150,        // Max frequency = 225, min frequency = 50
  .quaternion9_frequency = 150,        // Max frequency = 225, min frequency = 50
  .har_frequency = 50,                // Max frequency = 225, min frequency = 50  
  .steps_frequency = 50,              // Max frequency = 225, min frequency = 50
  .step_detector_frequency = 50
};

TapDetector tapDetector;

void tripple_tap_event() {
  Serial.println("TapTapTap!");
}

void setup() 
{
  Serial.begin(115200);

/* Values for TapDetector(
          int tap_count, // Number of sequential taps to listen for
          std::function<void()> tap_handler, // Callback used when [tap_count] number of taps is received (in timeframe)
          int prevent_event_ms = 25, // ms after an accelerometer event to prevent additional events for (debouncing)
          int event_repeat_ms = 400, // for multi-tap events, next tap must follow within this ms period
          float cutoff_threshold = 0.4f, // filtered value must be over this to register as a tap
          float cutoff_hz = 1.0f, // suppress accell data over this frequency
          float sampling_hz = 5.0f); // How fast to sample (should be at least double cutoff_hz) */
          
  tapDetector = TapDetector(3, &tripple_tap_event); // Tripple tap
  
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(icmSettings.i2c_speed);
 
  icm20948.init(icmSettings);
}

void loop() 
{
    icm20948.task();

    float x, y, z;
    if (icm20948.accelDataIsReady())
    {
        icm20948.readAccelData(&x, &y, &z);        
        tapDetector.update(z);
    }    
    
  delay(1);
}
