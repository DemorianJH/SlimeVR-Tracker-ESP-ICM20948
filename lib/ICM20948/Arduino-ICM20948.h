#ifndef __Arduino_ICM20948_H__
#define __Arduino_ICM20948_H__

#include <stdint.h> 

/*************************************************************************
  Defines
*************************************************************************/

typedef struct {
  int i2c_speed;
  uint8_t i2c_address;
  bool is_SPI;
  int cs_pin;
  int spi_speed;
  int mode;
  bool enable_gyroscope;
  bool enable_accelerometer;
  bool enable_magnetometer;
  bool enable_gravity;
  bool enable_linearAcceleration;
  bool enable_quaternion6;
  bool enable_quaternion9;
  bool enable_har;
  bool enable_steps;
  bool enable_step_detector;
  int gyroscope_frequency;
  int accelerometer_frequency;
  int magnetometer_frequency;
  int gravity_frequency;
  int linearAcceleration_frequency;
  int quaternion6_frequency;
  int quaternion9_frequency;
  int har_frequency;
  int steps_frequency;
  int step_detector_frequency;

} ArduinoICM20948Settings;

/*************************************************************************
  Class
*************************************************************************/

class ArduinoICM20948
{
  public:

    ArduinoICM20948();

    //void init(TwoWire *theWire = &Wire, JTICM20948Settings settings);
    int init(ArduinoICM20948Settings settings);
    int task();

    bool gyroDataIsReady();
    bool accelDataIsReady();
    bool magDataIsReady();
    bool gravDataIsReady();
    bool linearAccelDataIsReady();
    bool quat6DataIsReady();
    bool euler6DataIsReady();
    bool quat9DataIsReady();
    bool euler9DataIsReady();
    bool harDataIsReady();
    bool stepsDataIsReady();
    bool stepTakenDataIsReady();

    void readGyroData(float *x, float *y, float *z);
    void readAccelData(float *x, float *y, float *z);
    void readMagData(float *x, float *y, float *z);
    void readGravData(float* x, float* y, float* z);
    void readLinearAccelData(float* x, float* y, float* z);
    void readQuat6Data(float *w, float *x, float *y, float *z);
    void readQuat6Data(double *w, double *x, double *y, double *z);
    void readEuler6Data(float *roll, float *pitch, float *yaw);
    void readQuat9Data(float* w, float* x, float* y, float* z);
    void readQuat9Data(double* w, double* x, double* y, double* z);
    void readEuler9Data(float* roll, float* pitch, float* yaw);
    void readHarData(char* activity);
    void readStepsData(unsigned long* steps_count);
	void readStepTakenData();

	int getGyroBias(int * bias);
	int getAccelBias(int * bias);
	int getMagBias(int * bias);
	int setGyroBias(int * bias);
	int setAccelBias(int * bias);
	int setMagBias(int * bias);
};


#endif