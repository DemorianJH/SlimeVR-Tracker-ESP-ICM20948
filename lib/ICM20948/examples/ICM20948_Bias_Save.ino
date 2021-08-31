// Modified lib originally from https://github.com/isouriadakis/Arduino_ICM20948_DMP_Full-Function
// Added more functions for bias read/save/load, and step detector (not used here) 

// TODO: change mount matrix

// ************************ SAVING FOR ESP32 ONLY - REMOVE THAT FOR OTHER MCU ****************************

#include <Arduino.h>

#include <Arduino-ICM20948.h>
#include <Wire.h>
#include <Preferences.h> // Uses NVS api underneath so should be wear leveling. Not available for ESP8266? Increase NVS partition size to balance even more.
#include <arduino-timer.h> // Used for periodically saving bias

#define I2C_SDA 21
#define I2C_SCL 22

#define SAVE_BIAS 0 // Saves the calculated bias every "bias_save_periods[]"
#define LOAD_BIAS 0 // Loads the saved bias on start-up
#define JSON_OUTPUT 1 // Writes the imu results to serial as json
#define DEBUG_PRINT 1 // Show extra debug messages

// seconds after previous save (from start) when calibration (DMP Bias) data will be saved to NVS. Increments through the list then stops; to prevent unwelcome eeprom wear.
int bias_save_periods[] = { 120, 180, 300, 600, 600 }; // 2min + 3min + 5min + 10min + 10min (no more saves after 30min)
int bias_save_counter = 0;

ArduinoICM20948 icm20948;
ArduinoICM20948Settings icmSettings =
{
  .i2c_speed = 200000,                // i2c clock speed
  .i2c_address = 0x69,                // Usually 0x69 or 0x68
  .is_SPI = false,                    // Enable SPI, if disable use i2c
  .cs_pin = 10,                       // SPI chip select pin
  .spi_speed = 7000000,               // SPI clock speed in Hz, max speed is 7MHz
  .mode = 1,                          // 0 = low power mode, 1 = high performance mode
  .enable_gyroscope = false,           // Enables gyroscope output
  .enable_accelerometer = false,       // Enables accelerometer output
  .enable_magnetometer = false,        // Enables magnetometer output // Enables quaternion output
  .enable_gravity = false,             // Enables gravity vector output
  .enable_linearAcceleration = false,  // Enables linear acceleration output
  .enable_quaternion6 = false,         // Enables quaternion 6DOF output
  .enable_quaternion9 = true,         // Enables quaternion 9DOF output
  .enable_har = false,                 // Enables activity recognition
  .enable_steps = false,               // Enables step counter
  .enable_step_detector = false,       // Enables step detector
  .gyroscope_frequency = 1,           // Max frequency = 225, min frequency = 1
  .accelerometer_frequency = 1,       // Max frequency = 225, min frequency = 1
  .magnetometer_frequency = 1,        // Max frequency = 70, min frequency = 1 
  .gravity_frequency = 1,             // Max frequency = 225, min frequency = 1
  .linearAcceleration_frequency = 1,  // Max frequency = 225, min frequency = 1
  .quaternion6_frequency = 50,        // Max frequency = 225, min frequency = 50
  .quaternion9_frequency = 50,        // Max frequency = 225, min frequency = 50
  .har_frequency = 50,                // Max frequency = 225, min frequency = 50  
  .steps_frequency = 50,              // Max frequency = 225, min frequency = 50
  .step_detector_frequency = 50
};

const uint8_t number_i2c_addr = 2;
uint8_t poss_addresses[number_i2c_addr] = {0X69, 0X68};
uint8_t ICM_address;
bool ICM_found = false;

Preferences prefs;
auto timer = timer_create_default();

void i2c_scan() {
    uint8_t error;
    for(uint8_t add_int = 0; add_int < number_i2c_addr; add_int++ )
    {
        if (DEBUG_PRINT)
        {
          Serial.printf("Scanning 0x%02X for slave...", poss_addresses[add_int]);
        }
        Wire.beginTransmission(poss_addresses[add_int]);
        error = Wire.endTransmission();
        if (error == 0){
            if (DEBUG_PRINT)
            {
              Serial.println("found.");
            }
            if(poss_addresses[add_int] == 0x69 || poss_addresses[add_int] == 0x68){
                if (DEBUG_PRINT)
                {
                  Serial.println("\t- address is ICM.");
                }
                ICM_address = poss_addresses[add_int];
                ICM_found = true;
            }
        }
    }
}

void run_icm20948_quat6_controller(bool inEuler = false) {
    float quat_w, quat_x, quat_y, quat_z;
    float roll, pitch, yaw;
    char sensor_string_buff[128];
    if (inEuler)
    {
        if (icm20948.euler6DataIsReady())
        {
            icm20948.readEuler6Data(&roll, &pitch, &yaw);
            sprintf(sensor_string_buff, "Euler6 roll, pitch, yaw(deg): [%f,%f,%f]", roll, pitch, yaw);
            Serial.println(sensor_string_buff);
        }
    }
    else
    {
        if (icm20948.quat6DataIsReady())
        {
            icm20948.readQuat6Data(&quat_w, &quat_x, &quat_y, &quat_z);
            sprintf(sensor_string_buff, "Quat6 w, x, y, z (deg): [%f,%f,%f,%f]", quat_w, quat_x, quat_y, quat_z);
            Serial.println(sensor_string_buff);
        }
    }    
}

void run_icm20948_quat9_controller(bool inEuler = false) {
    float quat_w, quat_x, quat_y, quat_z;
    float roll, pitch, yaw;
    char sensor_string_buff[128];
    if (inEuler)
    {
        if (icm20948.euler9DataIsReady())
        {
            icm20948.readEuler9Data(&roll, &pitch, &yaw);
            sprintf(sensor_string_buff, "Euler9 roll, pitch, yaw(deg): [%f,%f,%f]", roll, pitch, yaw);
            Serial.println(sensor_string_buff);
        }
    }
    else
    {
        if (icm20948.quat9DataIsReady())
        {
            icm20948.readQuat9Data(&quat_w, &quat_x, &quat_y, &quat_z);
            //sprintf(sensor_string_buff, "Quat9 w, x, y, z (deg): [%f,%f,%f,%f]", quat_w, quat_x, quat_y, quat_z);
            //Serial.println(sensor_string_buff);

            // Output the Quaternion data in the format expected by ZaneL's Node.js Quaternion animation tool
            if (JSON_OUTPUT)
            {
              Serial.print(F("{\"quat_w\":"));
              Serial.print(quat_w, 3);
              Serial.print(F(", \"quat_x\":"));
              Serial.print(quat_x, 3);
              Serial.print(F(", \"quat_y\":"));
              Serial.print(quat_y, 3);
              Serial.print(F(", \"quat_z\":"));
              Serial.print(quat_z, 3);
              Serial.println(F("}"));
            }
        }
    }    
}

void run_icm20948_accel_controller() {
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.accelDataIsReady())
    {
        icm20948.readAccelData(&x, &y, &z);
        sprintf(sensor_string_buff, "Acceleration x, y, z (g): [%f,%f,%f]", x, y, z);
        Serial.println(sensor_string_buff);
    }    
}

void run_icm20948_gyro_controller() {
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.gyroDataIsReady())
    {
        icm20948.readGyroData(&x, &y, &z);
        sprintf(sensor_string_buff, "Gyroscope x, y, z (rad/s): [%f,%f,%f]", x, y, z);
        Serial.println(sensor_string_buff);
    }    
}

void run_icm20948_mag_controller() {
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.magDataIsReady())
    {
        icm20948.readMagData(&x, &y, &z);
        sprintf(sensor_string_buff, "Magnetometer x, y, z (mT): [%f,%f,%f]", x, y, z);
        Serial.println(sensor_string_buff);
    }    
}

void run_icm20948_linearAccel_controller() {
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.linearAccelDataIsReady())
    {
        icm20948.readLinearAccelData(&x, &y, &z);
        sprintf(sensor_string_buff, "Linear Acceleration x, y, z (g): [%f,%f,%f]", x, y, z);
        Serial.println(sensor_string_buff);
    }    
}

void run_icm20948_grav_controller() {
    float x, y, z;
    char sensor_string_buff[128];
    if (icm20948.gravDataIsReady())
    {
        icm20948.readGravData(&x, &y, &z);
        sprintf(sensor_string_buff, "Gravity Vector x, y, z (g): [%f,%f,%f]", x, y, z);
        Serial.println(sensor_string_buff);
    }    
}

// n = Nothing, d = Drive, w = Walk, r = Run, b = Bike, t = Tilt, s = Still
void run_icm20948_har_controller() {
    char activity;
    char sensor_string_buff[128];
    if (icm20948.harDataIsReady())
    {
        icm20948.readHarData(&activity);
        sprintf(sensor_string_buff, "Current Activity : %c", activity);
        Serial.println(sensor_string_buff);
    }    
}

void run_icm20948_steps_controller() {
    unsigned long steps;
    char sensor_string_buff[128];
    if (icm20948.stepsDataIsReady())
    {
        icm20948.readStepsData(&steps);
        sprintf(sensor_string_buff, "Steps Completed : %lu", steps);
        Serial.println(sensor_string_buff);
    }    
}

void run_icm20948_step_detector_controller() {   
    if (icm20948.stepTakenDataIsReady())
    {        
        icm20948.readStepTakenData();
        Serial.println("step");
    }    
}

bool timer_tick(void *argument) {
  if (SAVE_BIAS) {
    int bias_a[3], bias_g[3], bias_m[3];
    
    icm20948.getGyroBias(bias_g);
    icm20948.getMagBias(bias_m);
    icm20948.getAccelBias(bias_a);

    bool accel_set = bias_a[0] && bias_a[1] && bias_a[2];
    bool gyro_set = bias_g[0] && bias_g[1] && bias_g[2];
    bool mag_set = bias_m[0] && bias_m[1] && bias_m[2];
         
    if (DEBUG_PRINT)
    {
      Serial.println("bias gyro result:");
      Serial.println(bias_g[0]); 
      Serial.println(bias_g[1]);
      Serial.println(bias_g[2]);
      Serial.println("end gyro");  
    
      Serial.println("bias accel result:");  
      Serial.println(bias_a[0]); 
      Serial.println(bias_a[1]);
      Serial.println(bias_a[2]);
      Serial.println("end accel");   
    
      Serial.println("bias mag result:");
      Serial.println(bias_m[0]); 
      Serial.println(bias_m[1]);
      Serial.println(bias_m[2]);
      Serial.println("end mag"); 
    }
    
    if (accel_set)
    {
      // Save accel
      prefs.putInt("ba0", bias_a[0]);
      prefs.putInt("ba1", bias_a[1]);
      prefs.putInt("ba2", bias_a[2]);

      if (DEBUG_PRINT)
        Serial.println("Wrote Accel Bias");
    }
    
    if (gyro_set)
    {
      // Save gyro
      prefs.putInt("bg0", bias_g[0]);
      prefs.putInt("bg1", bias_g[1]);
      prefs.putInt("bg2", bias_g[2]);

      if (DEBUG_PRINT)
        Serial.println("Wrote Gyro Bias");
    }

    if (mag_set)
    {
      // Save mag
      prefs.putInt("bm0", bias_m[0]);
      prefs.putInt("bm1", bias_m[1]);
      prefs.putInt("bm2", bias_m[2]);

      if (DEBUG_PRINT)
        Serial.println("Wrote Mag Bias");
    }    
  }  

  bias_save_counter++;
  // Possible: Could make it repeate the final timer value if any of the biases are still 0. Save strategy could be improved.
  if (sizeof(bias_save_periods) != bias_save_counter)
  {
      timer.in(bias_save_periods[bias_save_counter] * 1000, timer_tick);
  }

  return false;
}

void setup() 
{
  Serial.begin(115200);
  prefs.begin("ICM20948", false);  

  Wire.begin();//);I2C_SDA, I2C_SCL
  Wire.setClock(icmSettings.i2c_speed);

  if (DEBUG_PRINT)
    Serial.println("Starting ICM");
  
  i2c_scan();

  if (ICM_found)
  {      
    icmSettings.i2c_address = ICM_address;
    icm20948.init(icmSettings);

    if (LOAD_BIAS)
    {    
      int32_t bias_a[3], bias_g[3], bias_m[3];

      bias_a[0] = prefs.getInt("ba0", 0);
      bias_a[1] = prefs.getInt("ba1", 0);
      bias_a[2] = prefs.getInt("ba2", 0);
      
      bias_g[0] = prefs.getInt("bg0", 0);
      bias_g[1] = prefs.getInt("bg1", 0);
      bias_g[2] = prefs.getInt("bg2", 0);
      
      bias_m[0] = prefs.getInt("bm0", 0);
      bias_m[1] = prefs.getInt("bm1", 0);
      bias_m[2] = prefs.getInt("bm2", 0);
      
      icm20948.setGyroBias(bias_g);
      icm20948.setMagBias(bias_m);
      icm20948.setAccelBias(bias_a);
      
      if (DEBUG_PRINT) {
        Serial.print("read accel ");
        Serial.print(bias_a[0]);
        Serial.print(" - ");
        Serial.print(bias_a[1]);
        Serial.print(" - ");
        Serial.println(bias_a[2]);
      
        Serial.print("read gyro ");
        Serial.print(bias_g[0]);
        Serial.print(" - ");
        Serial.print(bias_g[1]);
        Serial.print(" - ");
        Serial.println(bias_g[2]);
      
        Serial.print("read mag ");
        Serial.print(bias_m[0]);
        Serial.print(" - ");
        Serial.print(bias_m[1]);
        Serial.print(" - ");
        Serial.println(bias_m[2]);      
        
        Serial.println("Actual loaded biases: ");
        timer_tick(0); // test the values were written successfully
      }
    }
  }

  timer.in(bias_save_periods[0] * 1000, timer_tick);  
}

void loop() 
{
  if (ICM_found)
  {
    timer.tick();
    icm20948.task();
    //run_icm20948_accel_controller();
    //run_icm20948_gyro_controller();
    //run_icm20948_mag_controller();
    //run_icm20948_linearAccel_controller();
    //run_icm20948_grav_controller();
    //run_icm20948_quat6_controller(true);
    run_icm20948_quat9_controller(false);
    //run_icm20948_har_controller();
    //run_icm20948_steps_controller();
    //run_icm20948_step_detector_controller();
  }
  
  delay(1);
}
