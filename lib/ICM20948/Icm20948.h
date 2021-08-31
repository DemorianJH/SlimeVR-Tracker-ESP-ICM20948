/*
 * ________________________________________________________________________________________________________
 * Copyright (c) 2015-2015 InvenSense Inc. All rights reserved.
 *
 * This software, related documentation and any modifications thereto (collectively “Software”) is subject
 * to InvenSense and its licensors' intellectual property rights under U.S. and international copyright
 * and other intellectual property rights laws.
 *
 * InvenSense and its licensors retain all intellectual property and proprietary rights in and to the Software
 * and any use, reproduction, disclosure or distribution of the Software without an express license agreement
 * from InvenSense is strictly prohibited.
 *
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, THE SOFTWARE IS
 * PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * EXCEPT AS OTHERWISE PROVIDED IN A LICENSE AGREEMENT BETWEEN THE PARTIES, IN NO EVENT SHALL
 * INVENSENSE BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 * ________________________________________________________________________________________________________
 */

/** @defgroup DriverIcm20948 Icm20948 driver
 *  @brief    Low-level driver for ICM20948 devices
 *  @ingroup  Drivers
 *  @{
 */

#ifndef _INV_ICM20948_MAIN_H_
#define _INV_ICM20948_MAIN_H_

#include <assert.h>
#include <cstdio>
#include <functional>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
	#if !defined(INV_EXPORT) && defined(INV_DO_DLL_EXPORT)
		#define INV_EXPORT __declspec(dllexport)
	#elif !defined(INV_EXPORT) && defined(INV_DO_DLL_IMPORT)
		#define INV_EXPORT __declspec(dllimport)
	#endif
#endif

#if !defined(INV_EXPORT)
	#define INV_EXPORT
#endif

/** @brief Hook for low-level system sleep() function to be implemented by upper layer
 *  @param[in] ms number of millisecond the calling thread should sleep
 */
void inv_icm20948_sleep_us(int us);

/** @brief Hook for low-level system time() function to be implemented by upper layer
 *  @return monotonic timestamp in us
 */
uint64_t inv_icm20948_get_time_us(void);

/** @brief Sensor identifier for control function
 */
enum inv_icm20948_sensor {
	INV_ICM20948_SENSOR_ACCELEROMETER,
	INV_ICM20948_SENSOR_GYROSCOPE,
	INV_ICM20948_SENSOR_RAW_ACCELEROMETER,
	INV_ICM20948_SENSOR_RAW_GYROSCOPE,
	INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED,
	INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED,
	INV_ICM20948_SENSOR_ACTIVITY_CLASSIFICATON,
	INV_ICM20948_SENSOR_STEP_DETECTOR,
	INV_ICM20948_SENSOR_STEP_COUNTER,
	INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR,
	INV_ICM20948_SENSOR_ROTATION_VECTOR,
	INV_ICM20948_SENSOR_GEOMAGNETIC_ROTATION_VECTOR,
	INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD,
	INV_ICM20948_SENSOR_WAKEUP_SIGNIFICANT_MOTION,
	INV_ICM20948_SENSOR_FLIP_PICKUP,
	INV_ICM20948_SENSOR_WAKEUP_TILT_DETECTOR,
	INV_ICM20948_SENSOR_GRAVITY,
	INV_ICM20948_SENSOR_LINEAR_ACCELERATION,
	INV_ICM20948_SENSOR_ORIENTATION,
	INV_ICM20948_SENSOR_B2S,        
	INV_ICM20948_SENSOR_MAX,
};

/** @brief Sensor type identifier definition
	 */
	enum inv_sensor_type {
		INV_SENSOR_TYPE_RESERVED                     = 0 ,  /**< Reserved ID: do not use */
		INV_SENSOR_TYPE_ACCELEROMETER                = 1 ,  /**< Accelerometer */
		INV_SENSOR_TYPE_MAGNETOMETER                 = 2 ,  /**< Magnetic field */
		INV_SENSOR_TYPE_ORIENTATION                  = 3 ,  /**< Deprecated orientation */
		INV_SENSOR_TYPE_GYROSCOPE                    = 4 ,  /**< Gyroscope */
		INV_SENSOR_TYPE_LIGHT                        = 5 ,  /**< Ambient light sensor */
		INV_SENSOR_TYPE_PRESSURE                     = 6 ,  /**< Barometer */
		INV_SENSOR_TYPE_TEMPERATURE                  = 7 ,  /**< Temperature */
		INV_SENSOR_TYPE_PROXIMITY                    = 8 ,  /**< Proximity */
		INV_SENSOR_TYPE_GRAVITY                      = 9 ,  /**< Gravity */
		INV_SENSOR_TYPE_LINEAR_ACCELERATION          = 10,  /**< Linear acceleration */
		INV_SENSOR_TYPE_ROTATION_VECTOR              = 11,  /**< Rotation vector */
		INV_SENSOR_TYPE_HUMIDITY                     = 12,  /**< Relative humidity */
		INV_SENSOR_TYPE_AMBIENT_TEMPERATURE          = 13,  /**< Ambient temperature */
		INV_SENSOR_TYPE_UNCAL_MAGNETOMETER           = 14,  /**< Uncalibrated magnetic field */
		INV_SENSOR_TYPE_GAME_ROTATION_VECTOR         = 15,  /**< Game rotation vector */
		INV_SENSOR_TYPE_UNCAL_GYROSCOPE              = 16,  /**< Uncalibrated gyroscope */
		INV_SENSOR_TYPE_SMD                          = 17,  /**< Significant motion detection */
		INV_SENSOR_TYPE_STEP_DETECTOR                = 18,  /**< Step detector */
		INV_SENSOR_TYPE_STEP_COUNTER                 = 19,  /**< Step counter */
		INV_SENSOR_TYPE_GEOMAG_ROTATION_VECTOR       = 20,  /**< Geomagnetic rotation vector */
		INV_SENSOR_TYPE_HEART_RATE                   = 21,  /**< Heart rate */
		INV_SENSOR_TYPE_TILT_DETECTOR                = 22,  /**< Tilt detector */
		INV_SENSOR_TYPE_WAKE_GESTURE                 = 23,  /**< Wake-up gesture  */
		INV_SENSOR_TYPE_GLANCE_GESTURE               = 24,  /**< Glance gesture  */
		INV_SENSOR_TYPE_PICK_UP_GESTURE              = 25,  /**< Pick-up gesture */
		INV_SENSOR_TYPE_BAC                          = 26,  /**< Basic Activity Classifier */
		INV_SENSOR_TYPE_PDR                          = 27,  /**< Pedestrian Dead Reckoning */
		INV_SENSOR_TYPE_B2S                          = 28,  /**< Bring to see */
		INV_SENSOR_TYPE_3AXIS                        = 29,  /**< 3 Axis sensor */
		INV_SENSOR_TYPE_EIS                          = 30,  /**< Electronic Image Stabilization */
		INV_SENSOR_TYPE_OIS_0                        = 31,  /**< Optical Image Stabilization */
		INV_SENSOR_TYPE_RAW_ACCELEROMETER            = 32,  /**< Raw accelerometer */
		INV_SENSOR_TYPE_RAW_GYROSCOPE                = 33,  /**< Raw gyroscope */
		INV_SENSOR_TYPE_RAW_MAGNETOMETER             = 34,  /**< Raw magnetometer */
		INV_SENSOR_TYPE_RAW_TEMPERATURE              = 35,  /**< Raw temperature */
		INV_SENSOR_TYPE_CUSTOM_PRESSURE              = 36,  /**< Custom Pressure Sensor */
		INV_SENSOR_TYPE_MIC                          = 37,  /**< Stream audio from microphone */
		INV_SENSOR_TYPE_TSIMU                        = 38,  /**< TS-IMU */
		INV_SENSOR_TYPE_RAW_PPG                      = 39,  /**< Raw Photoplethysmogram */
		INV_SENSOR_TYPE_HRV                          = 40,  /**< Heart rate variability */
		INV_SENSOR_TYPE_SLEEP_ANALYSIS               = 41,  /**< Sleep analysis */
		INV_SENSOR_TYPE_BAC_EXTENDED                 = 42,  /**< Basic Activity Classifier Extended */
		INV_SENSOR_TYPE_BAC_STATISTICS               = 43,  /**< Basic Activity Classifier Statistics */
		INV_SENSOR_TYPE_FLOOR_CLIMB_COUNTER          = 44,  /**< Floor Climbed Counter */
		INV_SENSOR_TYPE_ENERGY_EXPENDITURE           = 45,  /**< Energy Expenditure */
		INV_SENSOR_TYPE_DISTANCE                     = 46,  /**< Distance */
		INV_SENSOR_TYPE_SHAKE                        = 47,  /**< Shake Gesture */
		INV_SENSOR_TYPE_DOUBLE_TAP                   = 48,  /**< Double Tap */
		INV_SENSOR_TYPE_CUSTOM0,                            /**< Custom sensor ID 0 */
		INV_SENSOR_TYPE_CUSTOM1,                            /**< Custom sensor ID 1 */
		INV_SENSOR_TYPE_CUSTOM2,                            /**< Custom sensor ID 2 */
		INV_SENSOR_TYPE_CUSTOM3,                            /**< Custom sensor ID 3 */
		INV_SENSOR_TYPE_CUSTOM4,                            /**< Custom sensor ID 4 */
		INV_SENSOR_TYPE_CUSTOM5,                            /**< Custom sensor ID 5 */
		INV_SENSOR_TYPE_CUSTOM6,                            /**< Custom sensor ID 6 */
		INV_SENSOR_TYPE_CUSTOM7,                            /**< Custom sensor ID 7 */
		INV_SENSOR_TYPE_WOM,                                /**< Wake-up on motion */
		INV_SENSOR_TYPE_SEDENTARY_REMIND,                   /**< Sedentary Remind */
		INV_SENSOR_TYPE_DATA_ENCRYPTION,                    /**< Data Encryption */
		INV_SENSOR_TYPE_FSYNC_EVENT,                        /**< FSYNC event */
		INV_SENSOR_TYPE_HIGH_RATE_GYRO,                     /**< High Rate Gyro */
		INV_SENSOR_TYPE_CUSTOM_BSCD,                        /**< Custom BAC StepCounter Calorie counter and Distance counter */
		INV_SENSOR_TYPE_HRM_LOGGER,                         /**< HRM ouput for logger */
		/* Starting from there, the SensorID is coded with more than 6bits so check that communication protocol is adequate */
		INV_SENSOR_TYPE_PRED_QUAT_0,                        /**< Predictive Quaternion instance 0 */
		INV_SENSOR_TYPE_PRED_QUAT_1,                        /**< Predictive Quaternion instance 1 */
		INV_SENSOR_TYPE_OIS_1,                              /**< Optical Image Stabilization instance 1 */
		INV_SENSOR_TYPE_FIRMWARE,							/**< Messages from the firmware */

		INV_SENSOR_TYPE_MAX                                 /**< sentinel value for sensor type */
	};

typedef int inv_bool_t;

/** @brief States for the secondary device
	 */
	typedef enum inv_icm20948_compass_state
	{
		INV_ICM20948_COMPASS_RESET = 0,
		INV_ICM20948_COMPASS_INITED,
		INV_ICM20948_COMPASS_SETUP,
	}inv_icm20948_compass_state_t;

	/** @brief ICM20948 driver states definition
	 */
	typedef struct sensor_type_icm20948{
		uint64_t odr_applied_us;
		uint64_t odr_us;
	}sensor_type_icm20948_t;

	typedef enum {
		CHIP_LOW_NOISE_ICM20948,
		CHIP_LOW_POWER_ICM20948,
	}chip_lp_ln_mode_icm20948_t;

	/** @brief ICM20948 serial interface
	 */
	struct inv_icm20948_serif {
		void *     context;
		std::function<int(void * context, uint8_t reg, uint8_t *buf, uint32_t len)> read_reg;
		std::function<int(void * context, uint8_t reg, const uint8_t *buf, uint32_t len)> write_reg;
		//int      (*read_reg)(void * context, uint8_t reg, uint8_t * buf, uint32_t len);
		//int      (*write_reg)(void * context, uint8_t reg, const uint8_t * buf, uint32_t len);
		uint32_t   max_read;
		uint32_t   max_write;
		inv_bool_t is_spi;
	};

	typedef struct inv_icm20948 {
		struct inv_icm20948_serif serif;
		/** @brief struct for the base_driver : this contains the Mems information */
		struct base_driver_t
		{
			unsigned char wake_state;
			chip_lp_ln_mode_icm20948_t chip_lp_ln_mode;
			unsigned char pwr_mgmt_1;
			unsigned char pwr_mgmt_2;
			unsigned char user_ctrl;
			unsigned char gyro_div;
			unsigned short secondary_div;
			short accel_div;
			unsigned char gyro_averaging;
			unsigned char accel_averaging;
			uint8_t gyro_fullscale; 
			uint8_t accel_fullscale;
			uint8_t lp_en_support:1;
			uint8_t firmware_loaded:1;
			uint8_t serial_interface;
			uint8_t timebase_correction_pll;
		}base_state;
		/* secondary device support */
		struct inv_icm20948_secondary_states {
			struct inv_icm20948_secondary_reg {
				uint16_t addr;
				uint16_t reg;
				uint16_t ctrl;
				uint16_t d0;
			} slv_reg[4];
			unsigned char sSavedI2cOdr;
			/* compass support */
			uint8_t compass_sens[3];
			long final_matrix[9];
			const int16_t *st_upper;
			const int16_t *st_lower;
			int scale;
			uint8_t dmp_on;
			uint8_t secondary_resume_compass_state;
			uint8_t mode_reg_addr;
			int compass_chip_addr;
			int compass_slave_id;
			inv_icm20948_compass_state_t compass_state;
		} secondary_state;
		/* self test */
		uint8_t selftest_done;
		uint8_t offset_done;
		uint8_t gyro_st_data[3];
		uint8_t accel_st_data[3];
		/* mpu fifo control */
		struct fifo_info_t
		{
			int fifoError;
			unsigned char fifo_overflow;
		} fifo_info;
		/* interface mapping */
		unsigned long sStepCounterToBeSubtracted;
		unsigned long sOldSteps;
		/* data converter */
		long s_quat_chip_to_body[4];
		/* base driver */
		uint8_t sAllowLpEn;
		uint8_t s_compass_available;
		uint8_t s_proximity_available;
		/* base sensor ctrl*/
		unsigned short inv_dmp_odr_dividers[37];//INV_SENSOR_NUM_MAX /!\ if the size change 
		unsigned short inv_dmp_odr_delays[37];//INV_SENSOR_NUM_MAX /!\ if the size change
		unsigned short bac_on; // indicates if ANDROID_SENSOR_ACTIVITY_CLASSIFICATON is on
		unsigned short pickup;
		unsigned short bac_status;
		unsigned short b2s_status;
		unsigned short flip_pickup_status;
		unsigned short inv_sensor_control;
		unsigned short inv_sensor_control2;
		unsigned long inv_androidSensorsOn_mask[2] ;// Each bit corresponds to a sensor being on
		unsigned short inv_androidSensorsOdr_boundaries[51][2];//GENERAL_SENSORS_MAX /!\ if the size change 
		unsigned char sGmrvIsOn; // indicates if GMRV was requested to be ON by end-user. Once this variable is set, it is either GRV or GMRV which is enabled internally
		unsigned short lLastHwSmplrtDividerAcc;
		unsigned short lLastHwSmplrtDividerGyr;
		unsigned char sBatchMode;
		uint8_t header2_count;
		char mems_put_to_sleep;
		unsigned short smd_status;
		unsigned short ped_int_status;
		unsigned short bac_request;
		uint8_t go_back_lp_when_odr_low; // set to 1 when we forced a switch from LP to LN mode to be able to reach 1kHz ODR, so we will need to go back to LP mode ASAP
		unsigned short odr_acc_ms; // ODR in ms requested for ANDROID_SENSOR_ACCELEROMETER
		//unsigned short odr_acc_wom_ms; // ODR in ms requested for ANDROID_SENSOR_WOM when using ACC
		unsigned short odr_racc_ms; // ODR in ms requested for ANDROID_SENSOR_RAW_ACCELEROMETER
		unsigned short odr_gyr_ms; // ODR in ms requested for ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED
		unsigned short odr_rgyr_ms; // ODR in ms requested for ANDROID_SENSOR_RAW_GYROSCOPE
		int bias[9];// dmp bias [0-2]:acc,[3-5]:gyr,[6-8]:mag
		/* Icm20948Fifo usage */
		signed char mounting_matrix[9];
		signed char mounting_matrix_secondary_compass[9];
		long soft_iron_matrix[9];
		uint8_t skip_sample[inv_icm20948_sensor::INV_ICM20948_SENSOR_MAX+1];
		uint64_t timestamp[inv_icm20948_sensor::INV_ICM20948_SENSOR_MAX+1];
		uint8_t sFirstBatch[inv_icm20948_sensor::INV_ICM20948_SENSOR_MAX+1];
		sensor_type_icm20948_t sensorlist[inv_icm20948_sensor::INV_ICM20948_SENSOR_MAX+1];
		unsigned short saved_count;
		/* Icm20948Transport*/
		unsigned char reg;
		unsigned char lastBank;
		unsigned char lLastBankSelected;
		/* augmented sensors*/
		unsigned short sGravityOdrMs;
		unsigned short sGrvOdrMs;
		unsigned short sLinAccOdrMs;
		unsigned short sGravityWuOdrMs;
		unsigned short sGrvWuOdrMs;
		unsigned short sLinAccWuOdrMs;
		unsigned short sRvOdrMs;
		unsigned short sOriOdrMs;
		unsigned short sRvWuOdrMs;
		unsigned short sOriWuOdrMs;
		/* Icm20649Setup */
		short set_accuracy;
		int new_accuracy;
	} inv_icm20948_t;



	/** @brief Prototype for print routine function
	 */
	typedef void (*inv_msg_printer_t)(int level, const char * str, va_list ap);

	

class Icm20948 {
	public:

	Icm20948();

	/** @brief Struct for the fifo. this contains the sensor data */
	struct inv_fifo_decoded_t
	{
		long dmp_3e_6quat[3];
		long dmp_3e_9quat[3];
		int dmp_rv_accuracyQ29;
		long dmp_3e_geomagquat[3];
		int dmp_geomag_accuracyQ29;
		short accel_s[3];
		long accel[3];
		short gyro[3];
		short gyro_bias[3];
		long gyro_calibr[3];
		long compass[3];
		long cpass_calibr[3];
		long ped_step_det_ts;
		short cpass_raw_data[3];
		short accel_accuracy;
		short gyro_accuracy;
		short cpass_accuracy;
		long bac_ts;
		unsigned short bac_state;
		short flip_pickup;
		unsigned char cpass_calibr_12chars[12];
		unsigned char cpass_calibr_6chars[6];
		unsigned short header;
		unsigned short header2;
		unsigned short footer;
		int new_data;
	};

	/** @brief ICM20948 driver states singleton declaration
	 *  Because of Low-level driver limitation only one insance of the driver is allowed
	 */
	struct inv_icm20948 * icm20948_instance;

	int msg_level;
	inv_msg_printer_t msg_printer;

	struct inv_fifo_decoded_t fd;
	/** Software FIFO, mirror of DMP HW FIFO, hence of max HARDWARE_FIFO_SIZE */

	#define HARDWARE_FIFO_SIZE       1024
	unsigned char fifo_data[HARDWARE_FIFO_SIZE];

	unsigned char data_output_control_reg2[2] = {0};
	uint8_t lIsInited = 0;
	unsigned char data;
	long lLastGyroSf = 0;

	uint8_t check_reg_access_lp_disable(struct inv_icm20948 * s, unsigned short reg);
	int inv_set_bank(struct inv_icm20948 * s, unsigned char bank);

	enum SMARTSENSOR_SERIAL_INTERFACE {
		SERIAL_INTERFACE_I2C = 1,
		SERIAL_INTERFACE_SPI,
		SERIAL_INTERFACE_INVALID
	};

	/** @brief Reset and initialize driver states
	 *  @param[in] s             handle to driver states structure
	 */
	inline void inv_icm20948_reset_states(struct inv_icm20948 * s,
			const struct inv_icm20948_serif * serif)
	{
		//assert(icm20948_instance == 0);

		memset(s, 0, sizeof(*s));
		s->serif = *serif;
		icm20948_instance = s;
	}

	#define CPASS_MTX_00            (23 * 16)
	#define CPASS_MTX_01            (23 * 16 + 4)
	#define CPASS_MTX_02            (23 * 16 + 8)
	#define CPASS_MTX_10            (23 * 16 + 12)
	#define CPASS_MTX_11            (24 * 16)
	#define CPASS_MTX_12            (24 * 16 + 4)
	#define CPASS_MTX_20            (24 * 16 + 8)
	#define CPASS_MTX_21            (24 * 16 + 12)
	#define CPASS_MTX_22            (25 * 16)

	/** @brief Supported auxiliary compass identifer
	 */
	enum inv_icm20948_compass_id {
		INV_ICM20948_COMPASS_ID_NONE = 0, /**< no compass */
		INV_ICM20948_COMPASS_ID_AK09911,  /**< AKM AK09911 */
		INV_ICM20948_COMPASS_ID_AK09912,  /**< AKM AK09912 */
		INV_ICM20948_COMPASS_ID_AK09916,  /**< AKM AK09916 */
		INV_ICM20948_COMPASS_ID_AK08963,  /**< AKM AK08963 */
	};

	/** @brief I2C from secondary device can stand on up to 4 channels. To perform automatic read and feed DMP :
	- channel 0 is reserved for compass reading data
	- channel 1 is reserved for compass writing one-shot acquisition register
	- channel 2 is reserved for als reading data */
	#define COMPASS_I2C_SLV_READ		0
	#define COMPASS_I2C_SLV_WRITE		1
	#define ALS_I2C_SLV					2


	/** @brief Define the Hardware engine*/
	enum INV_HW_ENGINE {
		HW_ENGINE_GYRO = 0,
		HW_ENGINE_ACCEL,
		HW_ENGINE_CPASS,
		HW_ENGINE_PRESSURE,
		HW_ENGINE_LIGHT,
		HW_ENGINE_TEMPERATURE,
		HW_ENGINE_HUMIDITY,
		HW_ENGINE_NUM_MAX,
	};

	#define INV_ODR_MIN_DELAY   200     // Limited by 8-bit HW Gyro rate divider register "GYRO_SMPLRT_DIV"
	#define INV_ODR_DEFAULT_BAC   18    // Default odr for sensor related to BAC algorithm which should run to 56Hz
	#define INV_ODR_DEFAULT_B2S   18    // Default odr for sensor related to B2S algorithm which should run to 56Hz

	#define INV_MIN_ODR         5
	#define INV_MAX_ODR         1000
	#define INV_MIN_ODR_CPASS   14
	#define INV_MAX_ODR_CPASS   1000
	#define INV_MIN_ODR_GRV     5
	#define INV_MAX_ODR_GRV     20

	// Determines which base sensor needs to be on based upon inv_androidSensorsOn_mask[0]
	#define INV_NEEDS_ACCEL_MASK	((1L<<1)|        (1L<<3)|        (1L<<9)|(1L<<10)|(1L<<11)|         (1L<<15)|         (1L<<17)|(1L<<18)|(1L<<19)|(1L<<20)|(1<<23)|       (1<<25)|        (1<<29)|(1<<30)|(1<<31))
	#define INV_NEEDS_GYRO_MASK		(                (1L<<3)|(1L<<4)|(1L<<9)|(1L<<10)|(1L<<11)|         (1L<<15)|(1L<<16)|                                                   (1<<25)|(1<<26)|(1<<29)|(1<<30)|(1<<31))
	#define INV_NEEDS_COMPASS_MASK	(        (1L<<2)|(1L<<3)|                         (1L<<11)|(1L<<14)|                                             (1L<<20)|       (1<<24)|(1<<25)|                        (1<<31))
	#define INV_NEEDS_PRESSURE		((1L<<6)|(1<<28))

	// Determines which base sensor needs to be on based upon inv_androidSensorsOn_mask[1]
	#define INV_NEEDS_ACCEL_MASK1	(       (1<<3)|      (1<<5)|(1<<6)|(1<<7)|(1<<9)|(1<<10))
	#define INV_NEEDS_GYRO_MASK1	(       (1<<3)|(1<<4)                                  |(1<<11))
	#define INV_NEEDS_COMPASS_MASK1	((1<<2)|                           (1<<7))

	#define GYRO_AVAILABLE		0x1
	#define ACCEL_AVAILABLE		0x2
	#define SECONDARY_COMPASS_AVAILABLE	0x8

	// data output control reg 1
	#define ACCEL_SET		0x8000
	#define GYRO_SET		0x4000
	#define CPASS_SET		0x2000
	#define ALS_SET			0x1000
	#define QUAT6_SET		0x0800
	#define QUAT9_SET		0x0400
	#define PQUAT6_SET		0x0200
	#define GEOMAG_SET		0x0100
	#define PRESSURE_SET	0x0080
	#define GYRO_CALIBR_SET	0x0040
	#define CPASS_CALIBR_SET 0x0020
	#define PED_STEPDET_SET	0x0010
	#define HEADER2_SET		0x0008
	#define PED_STEPIND_SET 0x0007

	// data output control reg 2
	#define ACCEL_ACCURACY_SET		0x4000
	#define GYRO_ACCURACY_SET		0x2000
	#define CPASS_ACCURACY_SET		0x1000
	#define COMPASS_CAL_INPUT_SET	0x1000
	#define FLIP_PICKUP_SET			0x0400
	#define ACT_RECOG_SET			0x0080
	#define BATCH_MODE_EN			0x0100
	// motion event control reg
	#define INV_BAC_WEARABLE_EN		0x8000
	#define INV_PEDOMETER_EN		0x4000
	#define INV_PEDOMETER_INT_EN	0x2000
	#define INV_SMD_EN				0x0800
	#define INV_BTS_EN				0x0020
	#define FLIP_PICKUP_EN			0x0010
	#define GEOMAG_EN   			0x0008
	#define INV_ACCEL_CAL_EN		0x0200
	#define INV_GYRO_CAL_EN			0x0100
	#define INV_COMPASS_CAL_EN		0x0080
	#define INV_NINE_AXIS_EN        0x0040
	#define INV_BRING_AND_LOOK_T0_SEE_EN  0x0004  // Aded by ONn for 20648

	// data packet size reg 1
	#define HEADER_SZ		2
	#define ACCEL_DATA_SZ	6
	#define GYRO_DATA_SZ	6
	#define CPASS_DATA_SZ	6
	#define ALS_DATA_SZ		8
	#define QUAT6_DATA_SZ	12
	#define QUAT9_DATA_SZ	14
	#define PQUAT6_DATA_SZ	6
	#define GEOMAG_DATA_SZ	14
	#define PRESSURE_DATA_SZ		6
	#define GYRO_BIAS_DATA_SZ	6
	#define CPASS_CALIBR_DATA_SZ	12
	#define PED_STEPDET_TIMESTAMP_SZ	4
	#define FOOTER_SZ		2

	// data packet size reg 2
	#define HEADER2_SZ			2
	#define ACCEL_ACCURACY_SZ	2
	#define GYRO_ACCURACY_SZ	2
	#define CPASS_ACCURACY_SZ	2
	#define FSYNC_SZ			2
	#define FLIP_PICKUP_SZ      2
	#define ACT_RECOG_SZ        6
	#define ODR_CNT_GYRO_SZ	2



	/** @brief Enables / disables bring to see
	* @param[in] enable	0=off, 1=on
	*/
	void INV_EXPORT inv_icm20948_ctrl_enable_b2s(unsigned char enable);	

	/** @brief Enumeration for the Type of ODR : Millisecondes / Microsecondes / Ticks */
	enum INV_ODR_TYPE {
		ODR_IN_Ms,
		ODR_IN_Us,
		ODR_IN_Ticks
	};

	/** @brief Determine if pressure could be successfully found and inited on board
	* @return	1 on success, 0 if not available.
	*/
	int INV_EXPORT inv_icm20948_get_pressure_availability(struct inv_icm20948 * s);

	#ifndef M_PI
	#define M_PI 3.14159265358979323846f
	#endif 
	#define INV_TWO_POWER_NEG_30 9.313225746154785e-010f
	#ifndef ABS
	#define ABS(x) (((x)>=0)?(x):-(x)) /*!< Computes the absolute value of its argument \a x. \ingroup invn_macro */
	#endif
	#ifndef MAX
	#define MAX(x,y) (((x)>(y))?(x):(y)) /*!< Computes the maximum of \a x and \a y. \ingroup invn_macro*/
	#endif
	#ifndef MIN
	#define MIN(x,y) (((x)<(y))?(x):(y)) /*!< Computes the minimum of \a x and \a y. \ingroup invn_macro */
	#endif

	//! \def INVN_FLT_TO_FXP
	//! Convert the \a value from float to QN value. \ingroup invn_macro 
	#define INVN_FLT_TO_FXP(value, shift)	( (int32_t)  ((float)(value)*(1ULL << (shift)) + ( (value>=0)-0.5f )) ) 
	//!	Macro to convert float values from an address into QN values, and copy them to another address. \ingroup invn_macro
	#define INVN_CONVERT_FLT_TO_FXP(fltptr, fixptr, length, shift)	{ int i; for(i=0; i<(length); ++i) (fixptr)[i] = INVN_FLT_TO_FXP((fltptr)[i], shift); }

	/** 
	* \brief Inverse function based on Newton-Raphson 1/sqrt(x) calculation
	\details Note that upshifting c (the result) by pow2 right away will overflow q30 if b<0.5 in q30 (=536870912). \n
	So if you are doing some multiplication later on (like a/b), then it might be better
	to do <code>q30_mult(a,c)</code> first and then shift it up by pow2: <code>q30_mult(a,c)<<pow2</code> \n
	The result might still overflow in some cases (large a, small b: a=1073741824, b=1
	but precise limits of the overflow are tbd).
	
	\brief Seventh order Chebychev polynomial approximation in Q15.
	\details Chebychev 7th order polynomial approximation : <br />
	\li in fixed point : \f$ constA7 = \text{int32}(2^{15}*[0.999133448222780 -0.320533292381664 0.144982490144465,-0.038254464970299]); \f$ <br />
	\li in float : \f$ A = \begin{bmatrix}[0.999133 & -0.320533 & 0.144982 &-0.0382544 \end{bmatrix}); \f$ <br />
	
	The related formula is : <br />
	\f$ \xi = \begin{cases} |y|/|x| &&  \text{in }(0, \pi/4] \\ |x|/|y| &&  \text{in } (\pi/4, \pi/2) \end{cases} , \quad
	Cheb = A(1)*\xi + A(2)*\xi^3 + A(3)*\xi^5 + A(4)*\xi^7 \f$ 

	7th Order Accuracy is +/-0.02 degrees (worst case) through entire range (accomplished with scaling). <br />
	This code depends on: \ref reciprocal_fun_q15 , \ref inverse_sqrt_q15 , \ref inv_q15_mult*/


	// compass chip list
	#define HW_AK8963 0x20
	#define HW_AK8975 0x21
	#define HW_AK8972 0x22
	#define HW_AK09911 0x23
	#define HW_AK09912 0x24
	#define HW_AK09916 0x25

	#define HW_ICM20648 0x01
	#define HW_ICM20948 0x02

	#define USE_ICM20948 1

	#if defined USE_ICM20648
	#define MEMS_CHIP  HW_ICM20648
	#endif

	#if defined USE_ICM20948
	#define MEMS_CHIP  HW_ICM20948
	#endif

	#if !defined(MEMS_CHIP)
		#error "MEMS_CHIP is not defined"
	#elif MEMS_CHIP != HW_ICM20648 \
			&& MEMS_CHIP != HW_ICM20948
		#error "Unknown value for MEMS_CHIP"
	#endif

	#define DMP_LOAD_START 0x90

	#define MPU_SUCCESS (0)
	#define MPU_COMPASS_NOT_FOUND (int)0x00ABCDEF

	#define MSEC_PER_SEC 1000
	#define NSEC_PER_MSEC 1000000
	#define NSEC_PER_SEC NSEC_PER_MSEC * MSEC_PER_SEC

	#define FIFO_DIVIDER 19

	#define REG_BANK_0 0x00
	#define REG_BANK_1 0x01

	#define DIAMOND_I2C_ADDRESS     0x68
	#define BANK_0                  (0 << 7)
	#define BANK_1                  (1 << 7)
	#define BANK_2                  (2 << 7)
	#define BANK_3                  (3 << 7)

	/*register and associated bit definition*/
	/* bank 0 register map */
	#define REG_WHO_AM_I            (BANK_0 | 0x00)
	#define REG_LPF                 (BANK_0 | 0x01)

	#define REG_USER_CTRL           (BANK_0 | 0x03)
	#define BIT_DMP_EN                      0x80
	#define BIT_FIFO_EN                     0x40
	#define BIT_I2C_MST_EN                  0x20
	#define BIT_I2C_IF_DIS                  0x10
	#define BIT_DMP_RST                     0x08
	#define BIT_DIAMOND_DMP_RST			    0x04

	#define REG_LP_CONFIG           (BANK_0 | 0x05)
	#define BIT_I2C_MST_CYCLE               0x40
	#define BIT_ACCEL_CYCLE                 0x20
	#define BIT_GYRO_CYCLE                  0x10

	#define REG_PWR_MGMT_1          (BANK_0 | 0x06)
	#define BIT_H_RESET                     0x80
	#define BIT_SLEEP                       0x40
	#define BIT_LP_EN                       0x20
	#define BIT_CLK_PLL                     0x01

	#define REG_PWR_MGMT_2          (BANK_0 | 0x07)
	#define BIT_PWR_PRESSURE_STBY           0x40
	#define BIT_PWR_ACCEL_STBY              0x38
	#define BIT_PWR_GYRO_STBY               0x07
	#define BIT_PWR_ALL_OFF                 0x7f

	#define REG_INT_PIN_CFG         (BANK_0 | 0x0F)
	#define BIT_INT_LATCH_EN                0x20
	#define BIT_BYPASS_EN                   0x02

	#define REG_INT_ENABLE          (BANK_0 | 0x10)
	#define BIT_DMP_INT_EN                  0x02

	#define REG_INT_ENABLE_1        (BANK_0 | 0x11)
	#define BIT_DATA_RDY_3_EN               0x08
	#define BIT_DATA_RDY_2_EN               0x04
	#define BIT_DATA_RDY_1_EN               0x02
	#define BIT_DATA_RDY_0_EN               0x01

	#define REG_INT_ENABLE_2        (BANK_0 | 0x12)
	#define BIT_FIFO_OVERFLOW_EN_0          0x1

	#define REG_INT_ENABLE_3        (BANK_0 | 0x13)

	#define REG_DMP_INT_STATUS      (BANK_0 | 0x18)
	#define BIT_WAKE_ON_MOTION_INT          0x08
	#define BIT_MSG_DMP_INT                 0x0002
	#define BIT_MSG_DMP_INT_0               0x0100  // CI Command

	#define BIT_MSG_DMP_INT_2               0x0200  // CIM Command - SMD
	#define BIT_MSG_DMP_INT_3               0x0400  // CIM Command - Pedometer

	#define BIT_MSG_DMP_INT_4               0x1000  // CIM Command - Pedometer binning
	#define BIT_MSG_DMP_INT_5               0x2000  // CIM Command - Bring To See Gesture
	#define BIT_MSG_DMP_INT_6               0x4000  // CIM Command - Look To See Gesture

	#define REG_INT_STATUS          (BANK_0 | 0x19)
	#define BIT_DMP_INT                     0x02 

	#define REG_INT_STATUS_1        (BANK_0 | 0x1A)
	#define REG_INT_STATUS_2        (BANK_0 | 0x1B)

	#define REG_SINGLE_FIFO_PRIORITY_SEL        (BANK_0 | 0x26)	

	#define REG_GYRO_XOUT_H_SH      (BANK_0 | 0x33)

	#define REG_TEMPERATURE         (BANK_0 | 0x39)
	#define REG_TEMP_CONFIG         (BANK_0 | 0x53)

	#define REG_EXT_SLV_SENS_DATA_00 (BANK_0 | 0x3B)
	#define REG_EXT_SLV_SENS_DATA_08 (BANK_0 | 0x43)
	#define REG_EXT_SLV_SENS_DATA_09 (BANK_0 | 0x44)
	#define REG_EXT_SLV_SENS_DATA_10 (BANK_0 | 0x45)

	#define REG_FIFO_EN             (BANK_0 | 0x66)
	#define BIT_SLV_0_FIFO_EN               0x01

	#define REG_FIFO_EN_2           (BANK_0 | 0x67)
	#define BIT_PRS_FIFO_EN                 0x20
	#define BIT_ACCEL_FIFO_EN               0x10
	#define BITS_GYRO_FIFO_EN               0x0E

	#define REG_FIFO_RST            (BANK_0 | 0x68)

	#define REG_FIFO_COUNT_H        (BANK_0 | 0x70)
	#define REG_FIFO_COUNT_L        (BANK_0 | 0x71)
	#define REG_FIFO_R_W            (BANK_0 | 0x72)

	#define REG_HW_FIX_DISABLE      (BANK_0 | 0x75)

	#define REG_FIFO_CFG            (BANK_0 | 0x76)
	#define BIT_MULTI_FIFO_CFG              0x01
	#define BIT_SINGLE_FIFO_CFG             0x00

	#define REG_ACCEL_XOUT_H_SH     (BANK_0 | 0x2D)
	#define REG_ACCEL_XOUT_L_SH     (BANK_0 | 0x2E)
	#define REG_ACCEL_YOUT_H_SH     (BANK_0 | 0x2F)
	#define REG_ACCEL_YOUT_L_SH     (BANK_0 | 0x30)
	#define REG_ACCEL_ZOUT_H_SH     (BANK_0 | 0x31)
	#define REG_ACCEL_ZOUT_L_SH     (BANK_0 | 0x32)

	#define REG_MEM_START_ADDR      (BANK_0 | 0x7C)
	#define REG_MEM_R_W             (BANK_0 | 0x7D)
	#define REG_MEM_BANK_SEL        (BANK_0 | 0x7E)

	/* bank 1 register map */
	#define REG_TIMEBASE_CORRECTION_PLL   (BANK_1 | 0x28)
	#define REG_TIMEBASE_CORRECTION_RCOSC (BANK_1 | 0x29)
	#define REG_SELF_TEST1                (BANK_1 | 0x02)
	#define REG_SELF_TEST2                (BANK_1 | 0x03)
	#define REG_SELF_TEST3                (BANK_1 | 0x04)
	#define REG_SELF_TEST4                (BANK_1 | 0x0E)
	#define REG_SELF_TEST5                (BANK_1 | 0x0F)
	#define REG_SELF_TEST6                (BANK_1 | 0x10)

	#define REG_XA_OFFS_H                 (BANK_1 | 0x14)
	#define REG_XA_OFFS_L                 (BANK_1 | 0x15)
	#define REG_YA_OFFS_H                 (BANK_1 | 0x17)
	#define REG_YA_OFFS_L                 (BANK_1 | 0x18)
	#define REG_ZA_OFFS_H                 (BANK_1 | 0x1A)
	#define REG_ZA_OFFS_L                 (BANK_1 | 0x1B)

	/* bank 2 register map */
	#define REG_GYRO_SMPLRT_DIV     (BANK_2 | 0x00)

	#define REG_GYRO_CONFIG_1       (BANK_2 | 0x01)
	#define SHIFT_GYRO_FS_SEL               1
	#define SHIFT_GYRO_DLPCFG               3

	#define REG_GYRO_CONFIG_2       (BANK_2 | 0x02)
	#define BIT_GYRO_CTEN                   0x38

	#define REG_XG_OFFS_USRH        (BANK_2 | 0x03)
	#define REG_XG_OFFS_USRL        (BANK_2 | 0x04)
	#define REG_YG_OFFS_USRH        (BANK_2 | 0x05)
	#define REG_YG_OFFS_USRL        (BANK_2 | 0x06)
	#define REG_ZG_OFFS_USRH        (BANK_2 | 0x07)
	#define REG_ZG_OFFS_USRL        (BANK_2 | 0x08)

	#define REG_ACCEL_SMPLRT_DIV_1  (BANK_2 | 0x10)
	#define REG_ACCEL_SMPLRT_DIV_2  (BANK_2 | 0x11)

	#define REG_ACCEL_CONFIG        (BANK_2 | 0x14)
	#define SHIFT_ACCEL_FS                  1

	#define REG_ACCEL_CONFIG_2      (BANK_2 | 0x15)
	#define BIT_ACCEL_CTEN                  0x1C

	#define REG_PRS_ODR_CONFIG      (BANK_2 | 0x20)
	#define REG_PRGM_START_ADDRH    (BANK_2 | 0x50)

	#define REG_MOD_CTRL_USR        (BANK_2 | 0x54)
	#define BIT_ODR_SYNC                    0x7

	/* bank 3 register map */
	#define REG_I2C_MST_ODR_CONFIG  (BANK_3 | 0x0)

	#define REG_I2C_MST_CTRL        (BANK_3 | 0x01)
	#define BIT_I2C_MST_P_NSR               0x10

	#define REG_I2C_MST_DELAY_CTRL  (BANK_3 | 0x02)
	#define BIT_SLV0_DLY_EN                 0x01
	#define BIT_SLV1_DLY_EN                 0x02
	#define BIT_SLV2_DLY_EN                 0x04
	#define BIT_SLV3_DLY_EN                 0x08

	#define REG_I2C_SLV0_ADDR       (BANK_3 | 0x03)
	#define REG_I2C_SLV0_REG        (BANK_3 | 0x04)
	#define REG_I2C_SLV0_CTRL       (BANK_3 | 0x05)
	#define REG_I2C_SLV0_DO         (BANK_3 | 0x06)

	#define REG_I2C_SLV1_ADDR       (BANK_3 | 0x07)
	#define REG_I2C_SLV1_REG        (BANK_3 | 0x08)
	#define REG_I2C_SLV1_CTRL       (BANK_3 | 0x09)
	#define REG_I2C_SLV1_DO         (BANK_3 | 0x0A)

	#define REG_I2C_SLV2_ADDR       (BANK_3 | 0x0B)
	#define REG_I2C_SLV2_REG        (BANK_3 | 0x0C)
	#define REG_I2C_SLV2_CTRL       (BANK_3 | 0x0D)
	#define REG_I2C_SLV2_DO         (BANK_3 | 0x0E)

	#define REG_I2C_SLV3_ADDR       (BANK_3 | 0x0F)
	#define REG_I2C_SLV3_REG        (BANK_3 | 0x10)
	#define REG_I2C_SLV3_CTRL       (BANK_3 | 0x11)
	#define REG_I2C_SLV3_DO         (BANK_3 | 0x12)

	#define REG_I2C_SLV4_CTRL       (BANK_3 | 0x15)

	#define INV_MPU_BIT_SLV_EN      0x80
	#define INV_MPU_BIT_BYTE_SW     0x40
	#define INV_MPU_BIT_REG_DIS     0x20
	#define INV_MPU_BIT_GRP         0x10
	#define INV_MPU_BIT_I2C_READ    0x80

	/* register for all banks */
	#define REG_BANK_SEL            0x7F
		
		/* data definitions */
	#define BYTES_PER_SENSOR         6
	#define FIFO_COUNT_BYTE          2

	#define FIFO_SIZE                (HARDWARE_FIFO_SIZE * 7 / 8)
	#define POWER_UP_TIME            100
	#define REG_UP_TIME_USEC         100
	#define DMP_RESET_TIME           20
	#define GYRO_ENGINE_UP_TIME      50
	#define MPU_MEM_BANK_SIZE        256
	#define IIO_BUFFER_BYTES         8
	#define HEADERED_NORMAL_BYTES    8
	#define HEADERED_Q_BYTES         16
	#define LEFT_OVER_BYTES          128
	#define BASE_SAMPLE_RATE         1125

	#ifdef FREQ_225
	#define MPU_DEFAULT_DMP_FREQ     225
	#define PEDOMETER_FREQ           (MPU_DEFAULT_DMP_FREQ >> 2)
	#define DEFAULT_ACCEL_GAIN       (33554432L * 5 / 11)
	#else
	#define MPU_DEFAULT_DMP_FREQ     102
	#define PEDOMETER_FREQ           (MPU_DEFAULT_DMP_FREQ >> 1)
	#define DEFAULT_ACCEL_GAIN       33554432L
	#endif
	#define PED_ACCEL_GAIN           67108864L
	#define ALPHA_FILL_PED           858993459
	#define A_FILL_PED               214748365

	#define MIN_MST_ODR_CONFIG       4
	#define THREE_AXES               3
	#define NINE_ELEM                (THREE_AXES * THREE_AXES)
	#define MPU_TEMP_SHIFT           16
	#define SOFT_IRON_MATRIX_SIZE    (4 * 9)
	#define DMP_DIVIDER              (BASE_SAMPLE_RATE / MPU_DEFAULT_DMP_FREQ)
	#define MAX_5_BIT_VALUE          0x1F
	#define BAD_COMPASS_DATA         0x7FFF
	#define DEFAULT_BATCH_RATE       400
	#define DEFAULT_BATCH_TIME    (MSEC_PER_SEC / DEFAULT_BATCH_RATE)
	#define MAX_COMPASS_RATE         115
	#define MAX_PRESSURE_RATE        30
	#define MAX_ALS_RATE             5
	#define DATA_AKM_99_BYTES_DMP  10
	#define DATA_AKM_89_BYTES_DMP  9
	#define DATA_ALS_BYTES_DMP     8
	#define APDS9900_AILTL_REG      0x04
	#define BMP280_DIG_T1_LSB_REG                0x88
	#define COVARIANCE_SIZE          14
	#define ACCEL_COVARIANCE_SIZE  (COVARIANCE_SIZE * sizeof(int))
	#define COMPASS_COVARIANCE_SIZE  (COVARIANCE_SIZE * sizeof(int))
	#define TEMPERATURE_SCALE  3340827L
	#define TEMPERATURE_OFFSET 1376256L
	#define SECONDARY_INIT_WAIT 60
	#define MPU_SOFT_UPDT_ADDR               0x86
	#define MPU_SOFT_UPTD_MASK               0x0F
	#define AK99XX_SHIFT                    23
	#define AK89XX_SHIFT                    22
	#define OPERATE_GYRO_IN_DUTY_CYCLED_MODE       (1<<4)
	#define OPERATE_ACCEL_IN_DUTY_CYCLED_MODE      (1<<5)
	#define OPERATE_I2C_MASTER_IN_DUTY_CYCLED_MODE (1<<6)

	/* this is derived from 1000 divided by 55, which is the pedometer
	running frequency */
	#define MS_PER_PED_TICKS         18

	/* data limit definitions */
	#define MIN_FIFO_RATE            4
	#define MAX_FIFO_RATE            MPU_DEFAULT_DMP_FREQ
	#define MAX_DMP_OUTPUT_RATE      MPU_DEFAULT_DMP_FREQ
	#define MAX_READ_SIZE            128
	#define MAX_MPU_MEM              8192
	#define MAX_PRS_RATE             281

	/* data header defines */
	#define PRESSURE_HDR             0x8000
	#define ACCEL_HDR                0x4000
	#define ACCEL_ACCURACY_HDR       0x4080
	#define GYRO_HDR                 0x2000
	#define GYRO_ACCURACY_HDR        0x2080
	#define COMPASS_HDR              0x1000
	#define COMPASS_HDR_2            0x1800
	#define CPASS_ACCURACY_HDR       0x1080
	#define ALS_HDR                  0x0800
	#define SIXQUAT_HDR              0x0400
	#define PEDQUAT_HDR              0x0200
	#define STEP_DETECTOR_HDR        0x0100

	#define COMPASS_CALIB_HDR        0x0080
	#define GYRO_CALIB_HDR           0x0040
	#define EMPTY_MARKER             0x0020
	#define END_MARKER               0x0010
	#define NINEQUAT_HDR             0x0008
	#define LPQ_HDR                  0x0004

	#define STEP_INDICATOR_MASK      0x000f

	/* init parameters */
	#define MPU_INIT_SMD_THLD        1500
	#define MPU_INIT_SENSOR_RATE     5                    
	#define MPU_INIT_GYRO_SCALE      3
	#define MPU_INIT_ACCEL_SCALE     0
	#define MPU_INIT_PED_INT_THRESH  2
	#define MPU_INIT_PED_STEP_THRESH 6
	#define COMPASS_SLAVEADDR_AKM_BASE      0x0C
	#define COMPASS_SLAVEADDR_AKM           0x0E
		
	#ifndef BIT
	#define BIT(x) ( 1 << x )              
	#endif

	#define ENABLE  1
	#define DISABLE 0
		
	// interrupt configurations related to HW register
	#define FSYNC_INT   BIT(7)
	#define MOTION_INT  BIT(3)
	#define PLL_INT     BIT(2)
	#define DMP_INT     BIT(1)
	#define I2C_INT     BIT(0)

	#define CHIP_AWAKE          (0x01)
	#define CHIP_LP_ENABLE      (0x02)

	//ACC_REQUESTED_FREQ 
	#define DMP_ALGO_FREQ_56 56
	#define DMP_ALGO_FREQ_112 112
	#define DMP_ALGO_FREQ_225 225
	#define DMP_ALGO_FREQ_450 450
	#define DMP_ALGO_FREQ_900 900

	

	enum mpu_accel_fs {
		MPU_FS_2G = 0,
		MPU_FS_4G,
		MPU_FS_8G,
		MPU_FS_16G,
		NUM_MPU_AFS
	};

	enum mpu_gyro_fs {
		MPU_FS_250dps = 0,
		MPU_FS_500dps,
		MPU_FS_1000dps,
		MPU_FS_2000dps,
		NUM_MPU_GFS
	};

	enum INV_ENGINE {
		ENGINE_GYRO = 0,
		ENGINE_ACCEL,
		ENGINE_I2C,
		ENGINE_NUM_MAX,
	};

	/* enum for android sensor*/
	enum ANDROID_SENSORS {
		ANDROID_SENSOR_META_DATA = 0,
		ANDROID_SENSOR_ACCELEROMETER,
		ANDROID_SENSOR_GEOMAGNETIC_FIELD,
		ANDROID_SENSOR_ORIENTATION,
		ANDROID_SENSOR_GYROSCOPE,
		ANDROID_SENSOR_LIGHT,
		ANDROID_SENSOR_PRESSURE,
		ANDROID_SENSOR_TEMPERATURE,
		ANDROID_SENSOR_WAKEUP_PROXIMITY,
		ANDROID_SENSOR_GRAVITY,
		ANDROID_SENSOR_LINEAR_ACCELERATION,
		ANDROID_SENSOR_ROTATION_VECTOR,
		ANDROID_SENSOR_HUMIDITY,
		ANDROID_SENSOR_AMBIENT_TEMPERATURE,
		ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED,
		ANDROID_SENSOR_GAME_ROTATION_VECTOR,
		ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED,
		ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION,
		ANDROID_SENSOR_STEP_DETECTOR,
		ANDROID_SENSOR_STEP_COUNTER,
		ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR,
		ANDROID_SENSOR_HEART_RATE,
		ANDROID_SENSOR_PROXIMITY,
		
		ANDROID_SENSOR_WAKEUP_ACCELEROMETER,
		ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD,
		ANDROID_SENSOR_WAKEUP_ORIENTATION,
		ANDROID_SENSOR_WAKEUP_GYROSCOPE,
		ANDROID_SENSOR_WAKEUP_LIGHT,
		ANDROID_SENSOR_WAKEUP_PRESSURE,
		ANDROID_SENSOR_WAKEUP_GRAVITY,
		ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION,
		ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR,
		ANDROID_SENSOR_WAKEUP_RELATIVE_HUMIDITY,
		ANDROID_SENSOR_WAKEUP_AMBIENT_TEMPERATURE,
		ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD_UNCALIBRATED,
		ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR,
		ANDROID_SENSOR_WAKEUP_GYROSCOPE_UNCALIBRATED,
		ANDROID_SENSOR_WAKEUP_STEP_DETECTOR,
		ANDROID_SENSOR_WAKEUP_STEP_COUNTER,
		ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR,
		ANDROID_SENSOR_WAKEUP_HEART_RATE,
		ANDROID_SENSOR_WAKEUP_TILT_DETECTOR,
		ANDROID_SENSOR_RAW_ACCELEROMETER,
		ANDROID_SENSOR_RAW_GYROSCOPE,
		ANDROID_SENSOR_NUM_MAX,

		ANDROID_SENSOR_B2S,
		ANDROID_SENSOR_FLIP_PICKUP,
		ANDROID_SENSOR_ACTIVITY_CLASSIFICATON,
		ANDROID_SENSOR_SCREEN_ROTATION,
		SELF_TEST,
		SETUP,
		GENERAL_SENSORS_MAX
	};


	enum SENSOR_ACCURACY {
		SENSOR_ACCEL_ACCURACY = 0,
		SENSOR_GYRO_ACCURACY,
		SENSOR_COMPASS_ACCURACY,
		SENSOR_ACCURACY_NUM_MAX,
	};
/*
	#ifndef max
	#define max(x,y)    (((x)>(y))?(x):(y))
	#endif*/

	/* enum for sensor
	The sequence is important.
	It represents the order of apperance from DMP */
	enum INV_SENSORS {
		INV_SENSOR_ACCEL = 0,
		INV_SENSOR_GYRO,        
		INV_SENSOR_LPQ,             // 20610:  we'll find out if it breaks 20628 being inserted here....       
		INV_SENSOR_COMPASS,
		INV_SENSOR_ALS,
		INV_SENSOR_SIXQ,
		INV_SENSOR_NINEQ,
		INV_SENSOR_GEOMAG,
	INV_SENSOR_PEDQ,
	INV_SENSOR_PRESSURE,
		INV_SENSOR_CALIB_GYRO,
		INV_SENSOR_CALIB_COMPASS,
		INV_SENSOR_STEP_COUNTER,
		INV_SENSOR_ACTIVITY_CLASSIFIER,
		INV_SENSOR_FLIP_PICKUP,
		INV_SENSOR_BRING_TO_SEE,

	INV_SENSOR_SIXQ_accel,
	INV_SENSOR_NINEQ_accel,
	INV_SENSOR_GEOMAG_cpass,
	INV_SENSOR_NINEQ_cpass,

		INV_SENSOR_WAKEUP_ACCEL,
		INV_SENSOR_WAKEUP_GYRO,        
	//INV_SENSOR_WAKEUP_LPQ,
		INV_SENSOR_WAKEUP_COMPASS,
		INV_SENSOR_WAKEUP_ALS,
		INV_SENSOR_WAKEUP_SIXQ,
		INV_SENSOR_WAKEUP_NINEQ,
		INV_SENSOR_WAKEUP_GEOMAG,
	INV_SENSOR_WAKEUP_PEDQ,
	INV_SENSOR_WAKEUP_PRESSURE,
		INV_SENSOR_WAKEUP_CALIB_GYRO,
		INV_SENSOR_WAKEUP_CALIB_COMPASS,
		INV_SENSOR_WAKEUP_STEP_COUNTER,
		INV_SENSOR_WAKEUP_TILT_DETECTOR,
	//INV_SENSOR_WAKEUP_ACTIVITY_CLASSIFIER,

	INV_SENSOR_WAKEUP_SIXQ_accel,
	INV_SENSOR_WAKEUP_NINEQ_accel,
	INV_SENSOR_WAKEUP_GEOMAG_cpass,
	INV_SENSOR_WAKEUP_NINEQ_cpass,

		INV_SENSOR_NUM_MAX,
		INV_SENSOR_INVALID,
	};


	enum accel_cal_params {
		ACCEL_CAL_ALPHA_VAR = 0,
		ACCEL_CAL_A_VAR,
		ACCEL_CAL_DIV,
		NUM_ACCEL_CAL_PARAMS
	};

	enum compass_cal_params {
		CPASS_CAL_TIME_BUFFER = 0,
		CPASS_CAL_RADIUS_3D_THRESH_ANOMALY,
		NUM_CPASS_CAL_PARAMS
	};

	
	#define INV_ICM20948_GYR_SELF_TEST_OK  (0x01 << 0)
	#define INV_ICM20948_ACC_SELF_TEST_OK  (0x01 << 1)
	#define INV_ICM20948_MAG_SELF_TEST_OK  (0x01 << 2)
	#define INV_ICM20948_SELF_TEST_OK      ( INV_ICM20948_GYR_SELF_TEST_OK | \
												INV_ICM20948_ACC_SELF_TEST_OK | \
												INV_ICM20948_MAG_SELF_TEST_OK )

	inline inv_bool_t inv_icm20948_serif_is_spi(struct inv_icm20948_serif * s)
	{
		assert(s);

		return s->is_spi;
	}

	inline uint32_t inv_icm20948_serif_max_read(struct inv_icm20948_serif * s)
	{
		assert(s);

		return s->max_read;
	}

	inline uint32_t inv_icm20948_serif_max_write(struct inv_icm20948_serif * s)
	{
		assert(s);

		return s->max_write;
	}

	inline int inv_icm20948_serif_read_reg(struct inv_icm20948_serif * s,
			uint8_t reg, uint8_t * buf, uint32_t len)
	{
		assert(s);

		if(len > s->max_read)
			return INV_ERROR_SIZE;

		if(s->read_reg(s->context, reg, buf, len) != 0)
			return INV_ERROR_TRANSPORT;

		return 0;
	}

	inline int inv_icm20948_serif_write_reg(struct inv_icm20948_serif * s,
			uint8_t reg, const uint8_t * buf, uint32_t len)
	{
		assert(s);

		if(len > s->max_write)
			return INV_ERROR_SIZE;

		if(s->write_reg(s->context, reg, buf, len) != 0)
			return INV_ERROR_TRANSPORT;

		return 0;
	}




	
	// int INV_EXPORT inv_icm20948_set_wom_threshold(struct inv_icm20948 * s, uint8_t threshold);


	/** @brief Max size that can be read across I2C or SPI data lines */
	#define INV_MAX_SERIAL_READ 16
	/** @brief Max size that can be written across I2C or SPI data lines */
	#define INV_MAX_SERIAL_WRITE 16

	void INV_EXPORT inv_icm20948_transport_init(struct inv_icm20948 * s);

	













	void INV_EXPORT inv_icm20948_sleep_100us(unsigned long nHowMany100MicroSecondsToSleep);

	long INV_EXPORT inv_icm20948_get_tick_count(void);

	int inv_icm20948_read_reg(struct inv_icm20948 * s, uint8_t reg,	uint8_t * buf, uint32_t len);
	int inv_icm20948_write_reg(struct inv_icm20948 * s, uint8_t reg, const uint8_t * buf, uint32_t len);


	inline int inv_icm20948_write_reg_one(struct inv_icm20948 * s, uint8_t reg, uint8_t reg_value)
	{
		return inv_icm20948_write_reg(s, reg, &reg_value, 1);
	}

	inline int inv_icm20948_read_reg_one(struct inv_icm20948 * s, uint8_t reg, uint8_t * reg_value)
	{
		return inv_icm20948_read_reg(s, reg, reg_value, 1);
	}

	inline int inv_icm20948_set_reg_bits(struct inv_icm20948 * s, uint8_t reg, uint8_t bits_mask)
	{
		int rc;
		uint8_t reg_value;

		if((rc = inv_icm20948_read_reg_one(s, reg, &reg_value)) != 0)
			return rc;

		reg_value |= bits_mask;

		if((rc = inv_icm20948_write_reg_one(s, reg, reg_value)) != 0)
			return rc;

		return 0;
	}

	inline int inv_icm20948_clear_reg_bits(struct inv_icm20948 * s, uint8_t reg, uint8_t bits_mask)
	{
		int rc;
		uint8_t reg_value;

		if((rc = inv_icm20948_read_reg_one(s, reg, &reg_value)) != 0)
			return rc;

		reg_value &= ~bits_mask;

		if((rc = inv_icm20948_write_reg_one(s, reg, reg_value)) != 0)
			return rc;

		return 0;
	}

	inline int inv_icm20948_get_reg_bits(struct inv_icm20948 * s, uint8_t reg,
			uint8_t bits_mask, uint8_t * bits_mask_state)
	{
		int rc;

		if((rc = inv_icm20948_read_reg_one(s, reg, bits_mask_state)) != 0)
			return rc;

		*bits_mask_state &= bits_mask;

		return 0;
	}

	/**
	*  @brief      Write data to a register on MEMs.
	*  @param[in]  Register address
	*  @param[in]  Length of data
	*  @param[in]  Data to be written
	*  @return     0 if successful.
	*/
	int INV_EXPORT inv_icm20948_write_mems_reg(struct inv_icm20948 * s, uint16_t reg, unsigned int length, const unsigned char *data);
	/**
	*  @brief      Write single byte of data to a register on MEMs.
	*  @param[in]  Register address
	*  @param[in]  Data to be written
	*  @return     0 if successful.
	*/
	int INV_EXPORT inv_icm20948_write_single_mems_reg(struct inv_icm20948 * s, uint16_t reg, const unsigned char data);
	/**
	*  @brief      Read data from a register on MEMs.
	*  @param[in]  Register address
	*  @param[in]  Length of data
	*  @param[in]  Data to be written
	*  @return     0 if successful.
	*/
	int INV_EXPORT inv_icm20948_read_mems_reg(struct inv_icm20948 * s, uint16_t reg, unsigned int length, unsigned char *data);
	/**
	*  @brief      Read data from a register in DMP memory 
	*  @param[in]  DMP memory address
	*  @param[in]  number of byte to be read
	*  @param[in]  input data from the register
	*  @return     0 if successful.
	*/
	int INV_EXPORT inv_icm20948_read_mems(struct inv_icm20948 * s, unsigned short reg, unsigned int length, unsigned char *data);
	/**
	*  @brief       Write data to a register in DMP memory 
	*  @param[in]   DMP memory address
	*  @param[in]   number of byte to be written
	*  @param[out]  output data from the register
	*  @return     0 if successful.
	*/
	int INV_EXPORT inv_icm20948_write_mems(struct inv_icm20948 * s, unsigned short reg, unsigned int length, const unsigned char *data);

	/**
	*  @brief      Write single byte of data to a register on MEMs with no power control
	*  @param[in]  Register address
	*  @param[in]  Data to be written
	*  @return     0 if successful.
	*/
	int inv_icm20948_write_single_mems_reg_core(struct inv_icm20948 * s, uint16_t reg, const uint8_t data)
	{
		int result = 0;
		unsigned char regOnly = (unsigned char)(reg & 0x7F);

		result |= inv_set_bank(s, reg >> 7);
		result |= inv_icm20948_write_reg(s, regOnly, &data, 1);

		return result;
	}

	/** @brief Common error code definition
	 */
	enum inv_error
	{
		INV_ERROR_SUCCESS      = 0,   /**< no error */
		INV_ERROR              = -1,  /**< unspecified error */
		INV_ERROR_NIMPL        = -2,  /**< function not implemented for given
										arguments */
		INV_ERROR_TRANSPORT    = -3,  /**< error occured at transport level */
		INV_ERROR_TIMEOUT      = -4,  /**< action did not complete in the expected
										time window */
		INV_ERROR_SIZE         = -5,  /**< size/length of given arguments is not
										suitable to complete requested action */
		INV_ERROR_OS           = -6,  /**< error related to OS */
		INV_ERROR_IO           = -7,  /**< error related to IO operation */
		INV_ERROR_MEM          = -9,  /**< not enough memory to complete requested
										action */
		INV_ERROR_HW           = -10, /**< error at HW level */
		INV_ERROR_BAD_ARG      = -11, /**< provided arguments are not good to
										perform requestion action */
		INV_ERROR_UNEXPECTED   = -12, /**< something unexpected happened */
		INV_ERROR_FILE         = -13, /**< cannot access file or unexpected format */
		INV_ERROR_PATH         = -14, /**< invalid file path */
		INV_ERROR_IMAGE_TYPE   = -15, /**< error when image type is not managed */
		INV_ERROR_WATCHDOG     = -16, /**< error when device doesn't respond 
										to ping */
		INV_ERROR_FIFO_OVERFLOW = -17, /**< FIFO overflow detected */
	};

	/** @brief For eMD target, disable log by default
	 *	If  compile switch is set for a compilation unit
	*	messages will be totally disabled by default
	*/
	#if !defined(__linux) && !defined(_WIN32) && !defined(ARDUINO)
		#define INV_MSG_DISABLE	1
	#endif


	/** @brief Allow to force enabling messaging using INV_MSG_ENABLE define  */
	#ifdef INV_MSG_ENABLE
		#undef INV_MSG_DISABLE
	#endif


	/** @brief Helper macro for calling inv_msg()
	 *	If INV_MSG_DISABLE compile switch is set for a compilation unit
	*	messages will be totally disabled
	*/
	#define INV_MSG(level, ...) 	      _INV_MSG(level, __VA_ARGS__)

	/** @brief Helper macro for calling inv_msg_setup()
	 *	If INV_MSG_DISABLE compile switch is set for a compilation unit
	*	messages will be totally disabled
	*/
	#define INV_MSG_SETUP(level, printer) _INV_MSG_SETUP(level, printer)

	/** @brief Helper macro for calling inv_msg_setup_level()
	 *	If INV_MSG_DISABLE compile switch is set for a compilation unit
	*	messages will be totally disabled
	*/
	#define INV_MSG_SETUP_LEVEL(level) 	  _INV_MSG_SETUP_LEVEL(level)

	/** @brief Helper macro for calling inv_msg_setup_default()
	 *	If INV_MSG_DISABLE compile switch is set for a compilation unit
	*	messages will be totally disabled
	*/
	#define INV_MSG_SETUP_DEFAULT()       _INV_MSG_SETUP_DEFAULT()

	/** @brief Return current level
	 *	@warning This macro may expand as a function call
	*/
	#define INV_MSG_LEVEL                 _INV_MSG_LEVEL

	#if defined(INV_MSG_DISABLE)
		#define _INV_MSG(level, ...)           (void)0
		#define _INV_MSG_SETUP(level, printer) (void)0
		#define _INV_MSG_SETUP_LEVEL(level)    (void)0
		#define _INV_MSG_LEVEL                 INV_MSG_LEVEL_OFF
	#else
		#define _INV_MSG(level, ...)           inv_msg(level, __VA_ARGS__)
		#define _INV_MSG_SETUP(level, printer) inv_msg_setup(level, printer)
		#define _INV_MSG_SETUP_LEVEL(level)    inv_msg_setup(level, inv_msg_printer_default)
		#define _INV_MSG_SETUP_DEFAULT()       inv_msg_setup_default()
		#define _INV_MSG_LEVEL                 inv_msg_get_level()
	#endif

	/** @brief message level definition
	 */
	enum inv_msg_level {
		INV_MSG_LEVEL_OFF     = 0,
		INV_MSG_LEVEL_ERROR,
		INV_MSG_LEVEL_WARNING,
		INV_MSG_LEVEL_INFO,
		INV_MSG_LEVEL_VERBOSE,
		INV_MSG_LEVEL_DEBUG,
		INV_MSG_LEVEL_MAX
	};

	/** @brief Set message level and printer function
	 *  @param[in] level   only message above level will be passed to printer function
	 *  @param[in] printer user provided function in charge printing message
	 *  @return none
	 */
	void INV_EXPORT inv_msg_setup(int level, inv_msg_printer_t printer);


	/** @brief Default printer function that display messages to stderr
	 *  Function uses stdio. Care must be taken on embeded platfrom.
	 *  Function does nothing with IAR compiler.
	 *  @return none
	 */
	static void inv_msg_printer_default(int level, const char * str, va_list ap);

	/** @brief Set message level
	 *  Default printer function will be used.
	 *  @param[in] level   only message above level will be passed to printer function
	 *  @return none
	 */
	inline void inv_msg_setup_level(int level)
	{
		inv_msg_setup(level, inv_msg_printer_default);
	}


	/** @brief Set default message level and printer
	 *  @return none
	 */
	inline void inv_msg_setup_default(void)
	{
		inv_msg_setup(INV_MSG_LEVEL_INFO, inv_msg_printer_default);
	}

	/** @brief Return current message level
	 *  @return current message level
	 */
	int INV_EXPORT inv_msg_get_level(void);

	/** @brief Display a message (through means of printer function)
	 *  @param[in] 	level for the message
	 *  @param[in] 	str   message string
	 *  @param[in] 	...   optional arguments
	 *  @return none
	 */
	void INV_EXPORT inv_msg(int level, const char * str, ...);

	

	#define INV_SENSOR_TYPE_CUSTOM_BASE    INV_SENSOR_TYPE_CUSTOM0
	#define INV_SENSOR_TYPE_CUSTOM_END     (INV_SENSOR_TYPE_CUSTOM7+1)

	#define INV_SENSOR_TYPE_META_DATA       INV_SENSOR_TYPE_RESERVED        /**< @deprecated */
	#define INV_SENSOR_TYPE_GYROMETER       INV_SENSOR_TYPE_GYROSCOPE       /**< @deprecated */
	#define INV_SENSOR_TYPE_UNCAL_GYROMETER INV_SENSOR_TYPE_UNCAL_GYROSCOPE /**< @deprecated */
	#define INV_SENSOR_TYPE_ENERGY_EXPANDITURE INV_SENSOR_TYPE_ENERGY_EXPENDITURE /**< @deprecated */
	#define INV_SENSOR_TYPE_OIS             INV_SENSOR_TYPE_OIS_0           /**< @deprecated */

	/** @brief Helper flag to indicate if sensor is a Wale-Up sensor
	 */
	#define INV_SENSOR_TYPE_WU_FLAG        (unsigned int)(0x80000000)

	/** @brief Sensor status definition
	 */
	enum inv_sensor_status
	{
		INV_SENSOR_STATUS_DATA_UPDATED      = 0,    /**< new sensor data */
		INV_SENSOR_STATUS_STATE_CHANGED     = 1,    /**< dummy sensor data indicating
														to a change in sensor state */
		INV_SENSOR_STATUS_FLUSH_COMPLETE    = 2,    /**< dummy sensor data indicating
														a end of batch after a manual flush */
		INV_SENSOR_STATUS_POLLED_DATA       = 3,    /**< sensor data value after manual request */
	};

	/** @brief Event definition for BAC sensor
	 */
	enum inv_sensor_bac_event {
		INV_SENSOR_BAC_EVENT_ACT_UNKNOWN             =  0,
		INV_SENSOR_BAC_EVENT_ACT_IN_VEHICLE_BEGIN    =  1,
		INV_SENSOR_BAC_EVENT_ACT_IN_VEHICLE_END      = -1,
		INV_SENSOR_BAC_EVENT_ACT_WALKING_BEGIN 	     =  2,
		INV_SENSOR_BAC_EVENT_ACT_WALKING_END         = -2,
		INV_SENSOR_BAC_EVENT_ACT_RUNNING_BEGIN       =  3,
		INV_SENSOR_BAC_EVENT_ACT_RUNNING_END         = -3,
		INV_SENSOR_BAC_EVENT_ACT_ON_BICYCLE_BEGIN    =  4,
		INV_SENSOR_BAC_EVENT_ACT_ON_BICYCLE_END      = -4,
		INV_SENSOR_BAC_EVENT_ACT_TILT_BEGIN          =  5,
		INV_SENSOR_BAC_EVENT_ACT_TILT_END            = -5,
		INV_SENSOR_BAC_EVENT_ACT_STILL_BEGIN         =  6,
		INV_SENSOR_BAC_EVENT_ACT_STILL_END           = -6,
	};

	/** @brief Event definition for BAC Ext sensor
	 */
	enum inv_sensor_bacext_event {
		INV_SENSOR_BACEXT_EVENT_ACT_UNKNOWN                 =  0,
		INV_SENSOR_BACEXT_EVENT_ACT_WALKING_START           =  1,
		INV_SENSOR_BACEXT_EVENT_ACT_WALKING_END             = -1,
		INV_SENSOR_BACEXT_EVENT_ACT_RUNNING_START           =  2,
		INV_SENSOR_BACEXT_EVENT_ACT_RUNNING_END             = -2,
		INV_SENSOR_BACEXT_EVENT_ACT_ON_BICYCLE_START        =  3,
		INV_SENSOR_BACEXT_EVENT_ACT_ON_BICYCLE_END          = -3,
		INV_SENSOR_BACEXT_EVENT_ACT_IN_VEHICLE_SIT_START    =  4,
		INV_SENSOR_BACEXT_EVENT_ACT_IN_VEHICLE_SIT_END      = -4,
		INV_SENSOR_BACEXT_EVENT_ACT_IN_VEHICLE_STAND_START  =  5,
		INV_SENSOR_BACEXT_EVENT_ACT_IN_VEHICLE_STAND_END    = -5,
		INV_SENSOR_BACEXT_EVENT_ACT_STILL_SIT_START         =  6,
		INV_SENSOR_BACEXT_EVENT_ACT_STILL_SIT_END           = -6,
		INV_SENSOR_BACEXT_EVENT_ACT_STILL_STAND_START       =  7,
		INV_SENSOR_BACEXT_EVENT_ACT_STILL_STAND_END         = -7
	};

	/** @brief Maximum size of an event data
	 */
	#define INV_SENSOR_EVENT_DATA_SIZE      64

	/** @brief For backward compatibility only - do not use
	 */
	#define IVN_SENSOR_EVENT_DATA_SIZE INV_SENSOR_EVENT_DATA_SIZE

	/** @brief Sensor event definition
	 */
	typedef struct inv_sensor_event
	{
		unsigned int         sensor;           /**< sensor type */
		int                  status;           /**< sensor data status as of
													enum inv_sensor_status */
		uint64_t             timestamp;        /**< sensor data timestamp in us */
		union {
			struct {
				float        vect[3];          /**< x,y,z vector data */
				float        bias[3];          /**< x,y,z bias vector data */
				uint8_t      accuracy_flag;    /**< accuracy flag */
			} acc;							   /**< 3d accelerometer data in g */
			struct {
				float        vect[3];          /**< x,y,z vector data */
				float        bias[3];          /**< x,y,z bias vector data */
				uint8_t      accuracy_flag;    /**< accuracy flag */
			} linAcc;                          /**< 3d linear accelerometer data in g */
			struct {
				float        vect[3];          /**< x,y,z vector data */
				float        bias[3];          /**< x,y,z bias vector data */
				uint8_t      accuracy_flag;    /**< accuracy flag */
			} grav;                            /**< 3d gravity vector data in g */
			struct {
				float        vect[3];          /**< x,y,z vector data */
				float        bias[3];          /**< x,y,z bias vector data (for uncal sensor variant) */
				uint8_t      accuracy_flag;    /**< accuracy flag */
			} mag;                             /**< 3d magnetometer data in uT */
			struct {
				float        vect[3];          /**< x,y,z vector data */
				float        bias[3];          /**< x,y,z bias vector data (for uncal sensor variant) */
				uint8_t      accuracy_flag;    /**< accuracy flag */
			} gyr;                             /**< 3d gyroscope data in deg/s */
			struct {
				float        quat[4];          /**< w,x,y,z quaternion data */
				float        accuracy;         /**< heading accuracy in deg */
				uint8_t      accuracy_flag;    /**< accuracy flag specific for GRV*/
			} quaternion6DOF;                  /**< quaternion 6DOF data */
			struct {
				float        quat[4];          /**< w,x,y,z quaternion data */
				float        accuracy;         /**< heading accuracy in deg */
				uint8_t      accuracy_flag;    /**< accuracy flag specific for GRV*/
			} quaternion9DOF;				   /**< quaternion 9DOF data */
			struct {
				float        x,y,z;            /**< x,y,z angles in deg as defined by Google Orientation sensor */
				uint8_t      accuracy_flag;    /**< heading accuracy in deg */
			} orientation;                     /**< orientation data */
			struct {
				float        bpm;              /**< beat per minute */
				uint8_t      confidence;       /**< confidence level */
				uint8_t      sqi;              /**< signal quality as seen by the the HRM engine */
			} hrm;                             /**< heart rate monitor data */                            /**< heart rate monitor data */
			struct {
				int32_t      acc[3];           /**< accel data used by hrm algorithm */
				int32_t      gyr[3];           /**< gyro data used by hrm algorithm */
				uint32_t     ppg_value;        /**< ppg value read from HRM sensor */
				float        ppm;              /**< beat per minute */
				uint8_t      confidence;       /**< confidence level */
				uint8_t      sqi;              /**< signal quality as seen by the the HRM engine */
				uint8_t      touch_status;     /**< touch status, detected or not by the PPG */
				uint8_t      gyrEnable;        /**< 1 gyro is enable else 0 */
			} hrmlogger;                       /**< heart rate monitor logger data */
			struct {
				uint8_t      rr_count;
				uint8_t      paddingDummy;   /**< dummy byte for padding */
				int16_t      rr_interval[4];   /**< beat-to-beat(RR) interval */
			} hrv;                             /**< heart rate variability data */
			struct {
				uint32_t     ppg_value;        /**< ppg value read from HRM sensor */
				uint8_t      touch_status;     /**< touch status, detected or not */
			} rawppg;                          /**< raw heart rate monitor data */
			struct {
				uint8_t      sleep_phase;      /**< state of sleep phases: 0 not defined, 1 restless sleep, 2 light sleep, 3 deep sleep */
				uint32_t     timestamp;        /**< time stamp of the sleep phase transition (seconds)*/
				int32_t      sleep_onset;      /**< time until first period of 20 min sleep without more than 1 min wake */
				int32_t      sleep_latency;    /**< time until first sleep phase */
				uint32_t     time_in_bed;      /**< time in bed (seconds) */
				uint32_t     total_sleep_time; /**< total sleep time (seconds) */
				uint8_t      sleep_efficiency; /**< ratio between total sleep time and time in bed */
			} sleepanalysis;                   /**< sleep analysis data */
			struct {
				int          event;            /**< BAC extended data begin/end event as of
													enum inv_sensor_bac_ext_event */
			} bacext;                          /**< activity classifier (BAC) extended data */
			struct {
				uint32_t     durationWalk;          /**< ms */
				uint32_t     durationRun;           /**< ms */
				uint32_t     durationTransportSit;  /**< ms */
				uint32_t     durationTransportStand;/**< ms */
				uint32_t     durationBiking;        /**< ms */
				uint32_t     durationStillSit;      /**< ms */
				uint32_t     durationStillStand;    /**< ms */
				uint32_t     durationTotalSit;      /**< Still-Sit + Transport-Sit + Biking (ms) */
				uint32_t     durationTotalStand;    /**< Still-Stand + Transport-Stand (ms) */
				uint32_t     stepWalk;              /**< walk step count */
				uint32_t     stepRun;               /**< run step count */
			} bacstat;                              /**< activity classifier (BAC) statistics data */
			struct {
				int32_t      floorsUp;         /**< number of floors climbed Up on foot by user. */
				int32_t      floorsDown;       /**< number of floors climbed Down on foot by user. */
			} floorclimb;                      /**< floor climbed data */
			struct {
				int32_t      instantEEkcal;    /**< energy expenditure in kilocalorie/min since last output. Format is q15: 2^15 = 1 kcal/min */
				int32_t      instantEEmets;    /**< energy expenditure in METs(Metabolic Equivalent of Task) since last output. Format is q15: 2^15 = 1 METs */
				int32_t      cumulativeEEkcal; /**< cumulative energy expenditure since the last reset in kilocalorie. Format is q0: 1 = 1 kcal */
				int32_t      cumulativeEEmets; /**< cumulative energy expenditure since the last reset in METs (Metabolic Equivalent of Task). Format is q0: 1 = 1 METs */
			} energyexp;                       /**< energy expenditure data */
			struct {
				int32_t      distanceWalk;     /**< distance in meters */
				int32_t      distanceRun;      /**< distance in meters */
			} distance;                        /**< distance data */
			struct {
				int32_t      table[7];         /**< data encrypted table */
			} dataencryption;  
			struct {
				float        tmp;              /**< temperature in deg celcius */
			} temperature;                     /**< temperature data */
			struct {
				float        percent;          /**< relative humidity in % */
			} humidity;                        /**< humidity data */
			struct {
				uint64_t     count;            /**< number of steps */
			} step;                            /**< step-counter data */
			struct {
				uint32_t     level;            /**< light level in lux */
			} light;                           /**< light data */
			struct {
				uint32_t     distance;         /**< distance in mm */
			} proximity;                       /**< proximity data */
			struct {
				uint32_t     pressure;         /**< pressure in Pa */
			} pressure;                        /**< pressure data */
			struct {
				int          event;            /**< BAC data begin/end event as of 
													enum inv_sensor_bac_event */
			} bac;                             /**< BAC data */
			struct {
				uint8_t      direction;        /**< 1: forward. 2: reverse. */
			} b2s;
			struct {
				uint32_t     fxdata[12];       /**< PDR data in fixpoint*/
			} pdr;                             /**< PDR data */
			struct {
				float        vect[3];          /**< x,y,z vector data */
				float        bias[3];          /**< x,y,z bias vector data (for uncal sensor variant) */
				int16_t      delta_ts;         /**< timestamp delta between standard gyro and EIS gyro */
			} eis;                             /**< EIS data
													@warning experimental: structure is likely to change in near future */
			struct {
				int32_t      vect[3];          /**< x,y,z vector data */
				uint32_t     fsr;              /**< full scale range */
			} raw3d;                           /**< 3d raw acc, mag or gyr*/
			struct {
				int32_t      raw;              /**< raw temperature value */
				uint32_t     sensitivity;      /**< raw temperature sensitivity */
			} rawtemp;                         /**< Raw temperature data*/
			struct {
				uint8_t      status[6];        /**< raw temperature value */
			} tsimu_status;                    /**< TSIMU status data*/
			inv_bool_t       event;            /**< event state for gesture-like sensor
													(SMD, B2S, Step-detector, Tilt-detector, Wake, Glance, Pick-Up, Shake, Double-tap, ...) */
			struct {
				int16_t delay_count;           /**< delay counter in us between FSYNC tag and previous gyro data */
			} fsync_event;                     /** < FSYNC tag (EIS sensor) */
			struct {
				unsigned     flags;             /** WOM status flags: non-zero value - motion detected
																	bit0 - motion detected around X axis
																	bit1 - motion detected around Y axis
																	bit2 - motion detected around Z axis
												*/
			} wom;                              /** Wake-up on motion data */
			struct {
				uint8_t *    buffer;           /**< pointer to buffer */
				uint32_t     size;             /**< current buffer size */
			} audio_buffer;                    /**< buffer of audio data */
			struct {
				struct {
					int        event;          /**< BAC data begin/end event as of  enum inv_sensor_bac_event */
				} bac;                         /**< BAC data */
				struct {
					uint64_t   count;          /**< number of steps */
				} step;                        /**< step-counter data */
				int32_t      cumulativeEEkcal; /**< cumulative energy expenditure since the last reset in kilocalorie. Format is q0: 1 = 1 kcal */
				int32_t      distance;         /**< sum of walk and run distance in meters */
			} bscd;                            /**< buffer of custom BSCD */
			struct {
				int32_t      raw_pressure;         /**< raw pressure */
				float        pressure;             /**< pressure in Pa */
				int32_t      raw_temperature;      /**< raw temperature */
				float        temperature;          /**< temperature in deg C */
			} custom_pressure;                        /**< pressure data */
			uint8_t          reserved[INV_SENSOR_EVENT_DATA_SIZE];     /**< reserved sensor data for future sensor */
		} data;                                /**< sensor data */
	} inv_sensor_event_t;

	/** @brief Sensor listener event callback definition
	 *  @param[in] event     reference to sensor event
	 *  @param[in] context   listener context
	 *  @return    none
	 */
	typedef void (*inv_sensor_listener_event_cb_t)(const inv_sensor_event_t * event,
			void * context);

	/** @brief Sensor event listener definition
	 */
	typedef struct inv_sensor_listener {
		inv_sensor_listener_event_cb_t event_cb; /**< sensor event callback */
		void *                         context;  /**< listener context */
	} inv_sensor_listener_t;

	/** @brief Helper to initialize a listener object
	 */
	static inline void inv_sensor_listener_init(inv_sensor_listener_t * listener,
		inv_sensor_listener_event_cb_t event_cb, void * context)
	{
		listener->event_cb = event_cb;
		listener->context  = context;
	}

	/** @brief Helper to notify a listener of a new sensor event
	 */
	static inline void inv_sensor_listener_notify(const inv_sensor_listener_t * listener,
			const inv_sensor_event_t * event)
	{
		if(listener) {
			listener->event_cb(event, listener->context);
		}
	}

	/** @brief Helper macro to retrieve sensor type (without wake-up flag) from a sensor id.
	 */
	#define INV_SENSOR_ID_TO_TYPE(sensor) \
		((unsigned int)(sensor) & ~INV_SENSOR_TYPE_WU_FLAG)

	/** @brief Helper macro that check if given sensor is of known type
	 */
	#define INV_SENSOR_IS_VALID(sensor) \
		(INV_SENSOR_ID_TO_TYPE(sensor) < INV_SENSOR_TYPE_MAX)

	/** @brief Helper macro that check if given sensor is a wake-up sensor
	 */
	#define INV_SENSOR_IS_WU(sensor) \
		(((int)(sensor) & INV_SENSOR_TYPE_WU_FLAG) != 0)

	/** @brief Utility function that returns a string from a sensor id
	 *  Empty string is returned if sensor is invalid
	 */
	const char INV_EXPORT * inv_sensor_str(int sensor);

	/** @brief Alias for inv_sensor_str
	 */
	#define inv_sensor_2str 	inv_sensor_str

	







/* full scale and LPF setting */
#define SELFTEST_GYRO_FS            ((0 << 3) | 1)
#define SELFTEST_ACCEL_FS           ((7 << 3) | 1)

/* register settings */
#define SELFTEST_GYRO_SMPLRT_DIV        10
#define SELFTEST_GYRO_AVGCFG        	3
#define SELFTEST_ACCEL_SMPLRT_DIV       10
#define SELFTEST_ACCEL_DEC3_CFG     	2

/* wait time in ms between 2 data collection */
#define WAIT_TIME_BTW_2_SAMPLESREAD     10
/* wait time in ms after sensor self-test enabling for oscillations to stabilize */
#define DEF_ST_STABLE_TIME              20 //ms
/* number of times self test reading should be done until abort */
#define DEF_ST_TRY_TIMES                2
/* number of samples to be read to be averaged */
#define DEF_ST_SAMPLES                  200

#define LOWER_BOUND_CHECK(value) ((value)>>1) // value * 0.5
#define UPPER_BOUND_CHECK(value) ((value) + ((value)>>1) ) // value * 1.5

struct recover_regs {
	// Bank#0
	uint8_t fifo_cfg;			// REG_FIFO_CFG
	uint8_t user_ctrl;			// REG_USER_CTRL
	uint8_t lp_config;			// REG_LP_CONFIG
	uint8_t int_enable;			// REG_INT_ENABLE
	uint8_t int_enable_1;		// REG_INT_ENABLE_1
	uint8_t int_enable_2;       // REG_INT_ENABLE_2
	uint8_t fifo_en;				// REG_FIFO_EN
	uint8_t fifo_en_2;			// REG_FIFO_EN_2
	uint8_t fifo_rst;			// REG_FIFO_RST

	// Bank#2
	uint8_t gyro_smplrt_div;		// REG_GYRO_SMPLRT_DIV
	uint8_t gyro_config_1;		// REG_GYRO_CONFIG_1
	uint8_t gyro_config_2;		// REG_GYRO_CONFIG_2
	uint8_t accel_smplrt_div_1;	// REG_ACCEL_SMPLRT_DIV_1
	uint8_t accel_smplrt_div_2;	// REG_ACCEL_SMPLRT_DIV_2
	uint8_t accel_config;		// REG_ACCEL_CONFIG
	uint8_t accel_config_2;		// REG_ACCEL_CONFIG_2
};

// Table for list of results for factory self-test value equation
// st_otp = 2620/2^FS * 1.01^(st_value - 1)
// for gyro and accel FS = 0 so 2620 * 1.01^(st_value - 1)
// st_value = 1 => 2620
// st_value = 2 => 2620 * 1.01 = 2646
// etc../
const uint16_t sSelfTestEquation[256] = {
	2620, 2646, 2672, 2699, 2726, 2753, 2781, 2808,
	2837, 2865, 2894, 2923, 2952, 2981, 3011, 3041,
	3072, 3102, 3133, 3165, 3196, 3228, 3261, 3293,
	3326, 3359, 3393, 3427, 3461, 3496, 3531, 3566,
	3602, 3638, 3674, 3711, 3748, 3786, 3823, 3862,
	3900, 3939, 3979, 4019, 4059, 4099, 4140, 4182,
	4224, 4266, 4308, 4352, 4395, 4439, 4483, 4528,
	4574, 4619, 4665, 4712, 4759, 4807, 4855, 4903,
	4953, 5002, 5052, 5103, 5154, 5205, 5257, 5310,
	5363, 5417, 5471, 5525, 5581, 5636, 5693, 5750,
	5807, 5865, 5924, 5983, 6043, 6104, 6165, 6226,
	6289, 6351, 6415, 6479, 6544, 6609, 6675, 6742,
	6810, 6878, 6946, 7016, 7086, 7157, 7229, 7301,
	7374, 7448, 7522, 7597, 7673, 7750, 7828, 7906,
	7985, 8065, 8145, 8227, 8309, 8392, 8476, 8561,
	8647, 8733, 8820, 8909, 8998, 9088, 9178, 9270,
	9363, 9457, 9551, 9647, 9743, 9841, 9939, 10038,
	10139, 10240, 10343, 10446, 10550, 10656, 10763, 10870,
	10979, 11089, 11200, 11312, 11425, 11539, 11654, 11771,
	11889, 12008, 12128, 12249, 12371, 12495, 12620, 12746,
	12874, 13002, 13132, 13264, 13396, 13530, 13666, 13802,
	13940, 14080, 14221, 14363, 14506, 14652, 14798, 14946,
	15096, 15247, 15399, 15553, 15709, 15866, 16024, 16184,
	16346, 16510, 16675, 16842, 17010, 17180, 17352, 17526,
	17701, 17878, 18057, 18237, 18420, 18604, 18790, 18978,
	19167, 19359, 19553, 19748, 19946, 20145, 20347, 20550,
	20756, 20963, 21173, 21385, 21598, 21814, 22033, 22253,
	22475, 22700, 22927, 23156, 23388, 23622, 23858, 24097,
	24338, 24581, 24827, 25075, 25326, 25579, 25835, 26093,
	26354, 26618, 26884, 27153, 27424, 27699, 27976, 28255,
	28538, 28823, 29112, 29403, 29697, 29994, 30294, 30597,
	30903, 31212, 31524, 31839, 32157, 32479, 32804
};

int inv_save_setting(struct inv_icm20948 * s, struct recover_regs * saved_regs)
{
	int result = 0;

	result |= inv_icm20948_read_mems_reg(s, REG_FIFO_CFG, 1, &saved_regs->fifo_cfg);

	result |= inv_icm20948_read_mems_reg(s, REG_USER_CTRL, 1, &saved_regs->user_ctrl);

	result = inv_icm20948_read_mems_reg(s, REG_LP_CONFIG, 1, &saved_regs->lp_config);

	result |= inv_icm20948_read_mems_reg(s, REG_INT_ENABLE, 1, &saved_regs->int_enable);

	result |= inv_icm20948_read_mems_reg(s, REG_INT_ENABLE_1, 1, &saved_regs->int_enable_1);

	result |= inv_icm20948_read_mems_reg(s, REG_INT_ENABLE_2, 1, &saved_regs->int_enable_2);

	result |= inv_icm20948_read_mems_reg(s, REG_FIFO_EN, 1, &saved_regs->fifo_en);

	result |= inv_icm20948_read_mems_reg(s, REG_FIFO_EN_2, 1, &saved_regs->fifo_en_2);

	result |= inv_icm20948_read_mems_reg(s, REG_FIFO_RST, 1, &saved_regs->fifo_rst);

	result |= inv_icm20948_read_mems_reg(s, REG_GYRO_SMPLRT_DIV, 1, &saved_regs->gyro_smplrt_div);

	result |= inv_icm20948_read_mems_reg(s, REG_GYRO_CONFIG_1, 1, &saved_regs->gyro_config_1);

	result |= inv_icm20948_read_mems_reg(s, REG_GYRO_CONFIG_2, 1, &saved_regs->gyro_config_2);

	result |= inv_icm20948_read_mems_reg(s, REG_ACCEL_SMPLRT_DIV_1, 1, &saved_regs->accel_smplrt_div_1);

	result |= inv_icm20948_read_mems_reg(s, REG_ACCEL_SMPLRT_DIV_2, 1, &saved_regs->accel_smplrt_div_2);

	result |= inv_icm20948_read_mems_reg(s, REG_ACCEL_CONFIG, 1, &saved_regs->accel_config);

	result |= inv_icm20948_read_mems_reg(s, REG_ACCEL_CONFIG_2, 1, &saved_regs->accel_config_2);

	return result;
}

int inv_recover_setting(struct inv_icm20948 * s, const struct recover_regs * saved_regs)
{
	int result = 0;

	// Stop sensors
	result |= inv_icm20948_write_single_mems_reg(s, REG_PWR_MGMT_2, 
		BIT_PWR_PRESSURE_STBY | BIT_PWR_ACCEL_STBY | BIT_PWR_GYRO_STBY);

	// Restore sensor configurations
	result |= inv_icm20948_write_single_mems_reg(s, REG_GYRO_SMPLRT_DIV, saved_regs->gyro_smplrt_div);

	result |= inv_icm20948_write_single_mems_reg(s, REG_GYRO_CONFIG_1, saved_regs->gyro_config_1);

	result |= inv_icm20948_write_single_mems_reg(s, REG_GYRO_CONFIG_2, saved_regs->gyro_config_2);

	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_SMPLRT_DIV_1, saved_regs->accel_smplrt_div_1);

	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_SMPLRT_DIV_2, saved_regs->accel_smplrt_div_2);

	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_CONFIG, saved_regs->accel_config);

	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_CONFIG_2, saved_regs->accel_config_2);

	// Restore FIFO configurations
	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_CFG, saved_regs->fifo_cfg);

	result |= inv_icm20948_write_single_mems_reg(s, REG_LP_CONFIG, saved_regs->lp_config);

	result |= inv_icm20948_write_single_mems_reg(s, REG_INT_ENABLE, saved_regs->int_enable);

	result |= inv_icm20948_write_single_mems_reg(s, REG_INT_ENABLE_1, saved_regs->int_enable_1);

	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_EN, saved_regs->fifo_en);

	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_EN_2, saved_regs->fifo_en_2);

	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_RST, MAX_5_BIT_VALUE);

	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_RST, saved_regs->fifo_rst);

	// Reset DMP
	result |= inv_icm20948_write_single_mems_reg(s, REG_USER_CTRL, 
		(saved_regs->user_ctrl & (~BIT_FIFO_EN)) | BIT_DMP_RST);
	inv_icm20948_sleep_us(DMP_RESET_TIME*1000);

	result |=inv_icm20948_set_dmp_address(s);
	result |=inv_icm20948_set_secondary(s);
	result |=inv_icm20948_setup_compass_akm(s);
	result |= inv_icm20948_sleep_mems(s);
	return result;
}

/**
*  @brief check accel or gyro self test
*  @param[in] sensorType type of sensor to be tested
*  @param[in] selfTestValuesReadFromReg self test written in register at production time.
*  @param[in] meanNormalTestValues average value of normal test.
*  @param[in] meanSelfTestValues   average value of self test
*  @return zero as success. A non-zero return value indicates failure in self test.
*/
int inv_check_accelgyro_self_test(enum INV_SENSORS sensorType, uint8_t * selfTestValuesReadFromReg, int *meanNormalTestValues, int *meanSelfTestValues) 
{
	int ret_val;
	int lIsStOtpReadZero = 0;
	int l_st_otp_read[3], lDiffNormalStValues[3], i;

	ret_val = 0;

	// Calculate factory Self-Test value (ST_OTP) based on the following equation:
	// The factory Self-Test value (ST_OTP) is calculated from the ST_Code (the SELF_TEST values read)
	// using the following equation, where �FS� is the full scale value code:
	// st_otp = 2620/2^FS * 1.01^(st_value - 1)
	// the result of the equation is in sSelfTestEquation array
	for (i = 0; i < 3; i++) {
		if (selfTestValuesReadFromReg[i] != 0) {
			l_st_otp_read[i] = sSelfTestEquation[selfTestValuesReadFromReg[i] - 1];
		} else {
			l_st_otp_read[i] = 0;
			lIsStOtpReadZero = 1;
		}
	}

	// Calculate the Self-Test response as follows:
	// - GXST = GX_ST_OS - GX_OS
	// - GYST = GY_ST_OS - GY_OS
	// - GZST = GZ_ST_OS - GZ_OS
	// - AXST = AX_ST_OS - AX_OS
	// - AYST = AY_ST_OS - AY_OS
	// - AZST = AZ_ST_OS - AZ_OS
	for (i = 0; i < 3; i++) {
		lDiffNormalStValues[i] = meanSelfTestValues[i] - meanNormalTestValues[i];

		// Ensure the factory Self-Test values ST_OTP are not 0
		if (!lIsStOtpReadZero) {
			// Compare the current Self-Test response (GXST, GYST, GZST, AXST, AYST and AZST) to the factory Self-Test values (ST_OTP)
			// and report Self-Test is passing if all the following criteria are fulfilled:
			// (GXST / GXST_OTP)  > 0.5
			if (lDiffNormalStValues[i] < LOWER_BOUND_CHECK(l_st_otp_read[i]) )
				ret_val = 1;
			if (sensorType != INV_SENSOR_GYRO)
				// (AXST / AXST_OTP)  < 1.5
				if (lDiffNormalStValues[i] > UPPER_BOUND_CHECK(l_st_otp_read[i]) )
					ret_val = 1;
		} else
			ret_val = 1;
	}

	return ret_val;
}

int inv_setup_selftest(struct inv_icm20948 * s, struct recover_regs * recover_regs)
{
	int result = 0;

	// reset static value
	memset(s->gyro_st_data, 0, sizeof(s->gyro_st_data));
	memset(s->accel_st_data, 0, sizeof(s->accel_st_data));

	// Save the current settings
	result |= inv_save_setting(s, recover_regs);

	// Wake up
	result |= inv_icm20948_write_single_mems_reg(s, REG_PWR_MGMT_1, BIT_CLK_PLL);

	// Stop sensors
	result |= inv_icm20948_write_single_mems_reg(s, REG_PWR_MGMT_2, BIT_PWR_ACCEL_STBY | BIT_PWR_GYRO_STBY);

	/*   Perform a soft-reset of the chip by setting the MSB of PWR_MGMT_1 register
	* This will clear any prior states in the chip
	*/
	result |= inv_icm20948_write_single_mems_reg(s, REG_PWR_MGMT_1, BIT_H_RESET);               
	inv_icm20948_sleep_us(100000); //100ms delay after soft reset--yd

	// Wake up
	result |= inv_icm20948_write_single_mems_reg(s, REG_PWR_MGMT_1, BIT_CLK_PLL);
	if (result)
		return result;

	// Set cycle mode
	result |= inv_icm20948_write_single_mems_reg(s, REG_LP_CONFIG, 
		BIT_I2C_MST_CYCLE | BIT_ACCEL_CYCLE | BIT_GYRO_CYCLE);

	// Configure FSR and DLPF for gyro
	result |= inv_icm20948_write_single_mems_reg(s, REG_GYRO_SMPLRT_DIV, SELFTEST_GYRO_SMPLRT_DIV);

	result |= inv_icm20948_write_single_mems_reg(s, REG_GYRO_CONFIG_1, SELFTEST_GYRO_FS);

	result |= inv_icm20948_write_single_mems_reg(s, REG_GYRO_CONFIG_2, SELFTEST_GYRO_AVGCFG);

	// Configure FSR and DLPF for accel
	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_SMPLRT_DIV_1, 0);

	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_SMPLRT_DIV_2, SELFTEST_ACCEL_SMPLRT_DIV);

	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_CONFIG, SELFTEST_ACCEL_FS);

	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_CONFIG_2, SELFTEST_ACCEL_DEC3_CFG);

	// Read selftest values
	// Retrieve factory Self-Test code (ST_Code) from SELF_TEST registers  (User Bank 1): 
	result |= inv_icm20948_read_mems_reg(s, REG_SELF_TEST1, 1, &s->gyro_st_data[0]);

	result |= inv_icm20948_read_mems_reg(s, REG_SELF_TEST2, 1, &s->gyro_st_data[1]);

	result |= inv_icm20948_read_mems_reg(s, REG_SELF_TEST3, 1, &s->gyro_st_data[2]);

	result |= inv_icm20948_read_mems_reg(s, REG_SELF_TEST4, 1, &s->accel_st_data[0]);

	result |= inv_icm20948_read_mems_reg(s, REG_SELF_TEST5, 1, &s->accel_st_data[1]);

	result |= inv_icm20948_read_mems_reg(s, REG_SELF_TEST6, 1, &s->accel_st_data[2]);

	// Restart sensors
	inv_icm20948_sleep_us(GYRO_ENGINE_UP_TIME*1000);

	return result;
}

int inv_selftest_read_samples(struct inv_icm20948 * self, enum INV_SENSORS type, int *sum_result, int *s)
{
	uint8_t w;
	int16_t vals[3];
	uint8_t d[BYTES_PER_SENSOR];
	int j;

	// Average 200 readings and save the averaged values as GX_OS, GY_OS, GZ_OS, AX_OS, AY_OS and AZ_OS. 
	// - GX_OS = Average (GYRO_XOUT_H | GYRO_XOUT_L)
	// - GY_OS = Average (GYRO_YOUT_H | GYRO_YOUT_L)
	// - GZ_OS = Average (GYRO_ZOUT_H | GYRO_ZOUT_L)
	// - AX_OS = Average (ACCEL_XOUT_H | ACCEL_XOUT_L)
	// - AY_OS = Average (ACCEL_YOUT_H | ACCEL_YOUT_L)
	// - AZ_OS = Average (ACCEL_ZOUT_H | ACCEL_ZOUT_L)

	if (INV_SENSOR_GYRO == type)
		w = REG_GYRO_XOUT_H_SH;
	else
		w = REG_ACCEL_XOUT_H_SH;

	while (*s < DEF_ST_SAMPLES) {

		if(inv_icm20948_read_mems_reg(self, w, BYTES_PER_SENSOR, d))
			return -1;

		for (j = 0; j < THREE_AXES; j++) {
			vals[j] = (d[(2*j)]<<8) | (d[(2*j)+ 1] & 0xff);
			sum_result[j] += vals[j];
		}

		(*s)++;

		inv_icm20948_sleep_us(WAIT_TIME_BTW_2_SAMPLESREAD*1000);
	}
	return 0;
}

/*
*  inv_do_test_accelgyro() - do the actual test of self testing
*/
int inv_do_test_accelgyro(struct inv_icm20948 * s, enum INV_SENSORS sensorType, int *meanValue, int *stMeanValue)
{
	int result, i, j;
	int lNbSamples = 0;

	// initialize output to be 0
	for (i = 0; i < THREE_AXES; i++) {
		meanValue[i] = 0;
		stMeanValue[i] = 0;
	}

	// read the accel/gyro output
	// the output values are 16 bits wide and in 2�s complement
	// Average 200 readings and save the averaged values
	result = inv_selftest_read_samples(s, sensorType, meanValue, &lNbSamples);
	if (result)
		return result;
	for (j = 0; j < THREE_AXES; j++) {
		meanValue[j] /= lNbSamples;
	}

	// Set Self-Test Bit
	if (sensorType == INV_SENSOR_GYRO)
	{
		// Enable gyroscope Self-Test by setting register User Bank 2, Register Address 02 (02h) Bit [5:3] to b111
		result = inv_icm20948_write_single_mems_reg(s, REG_GYRO_CONFIG_2, BIT_GYRO_CTEN | SELFTEST_GYRO_AVGCFG);
	} else
	{
		result = inv_icm20948_write_single_mems_reg(s, REG_ACCEL_CONFIG_2, BIT_ACCEL_CTEN | SELFTEST_ACCEL_DEC3_CFG);
	}
	if (result)
		return result;

	// Wait 20ms for oscillations to stabilize. 
	inv_icm20948_sleep_us(DEF_ST_STABLE_TIME*1000);

	// Read the accel/gyro output and average 200 readings
	// These readings are in units of LSBs
	lNbSamples = 0; 
	result = inv_selftest_read_samples(s, sensorType, stMeanValue, &lNbSamples);
	if (result)
		return result;
	for (j = 0; j < THREE_AXES; j++) {
		stMeanValue[j] /= lNbSamples;
	}

	return 0;
}

int inv_icm20948_run_selftest(struct inv_icm20948 * s, int gyro_bias_regular[], int accel_bias_regular[])
{
	int result;
	int gyro_bias_st[THREE_AXES];
	int accel_bias_st[THREE_AXES];
	int test_times;
	char accel_result, gyro_result, compass_result;
	struct recover_regs recover_regs;

	accel_result = 0;
	gyro_result = 0;
	compass_result = 0;

	// save original state of the chip, initialize registers, configure sensors and read ST values
	result = inv_setup_selftest(s, &recover_regs);
	if (result)
		goto test_fail;    
	// perform self test for gyro
	test_times = DEF_ST_TRY_TIMES;	
	while (test_times > 0) {
		result = inv_do_test_accelgyro(s, INV_SENSOR_GYRO, gyro_bias_regular, gyro_bias_st);
		if (result)
			test_times--;
		else
			break;
	}
	if (result)
		goto test_fail;    

	// perform self test for accel
	test_times = DEF_ST_TRY_TIMES;
	while (test_times > 0) {
		result = inv_do_test_accelgyro(s, INV_SENSOR_ACCEL, accel_bias_regular, accel_bias_st);
		if (result)
			test_times--;
		else
			break;
	}
	if (result)
		goto test_fail;

	// check values read at various steps
	accel_result = !inv_check_accelgyro_self_test(INV_SENSOR_ACCEL, s->accel_st_data, accel_bias_regular, accel_bias_st);
	gyro_result = !inv_check_accelgyro_self_test(INV_SENSOR_GYRO, s->gyro_st_data, gyro_bias_regular, gyro_bias_st);
	compass_result = !inv_icm20948_check_akm_self_test(s);

test_fail:
	// restore original state of the chips
	inv_recover_setting(s, &recover_regs);

	return (compass_result << 2) |
		(accel_result   << 1) |
		gyro_result;
}

void inv_icm20948_set_offset(struct inv_icm20948 * s, int raw_bias[])
{
#define ACCEL_OFFSET	3
	int16_t		offset[3];
	int16_t		delta_offset, old_offset, new_offset;
	uint8_t		data;
	int			ii;
	uint16_t	reg_addr = REG_XG_OFFS_USRH;
	
	// Set Gyro offset
	for (ii = 0; ii < 3; ii++) {
		offset[ii] = -1 * (raw_bias[ii] >> 2);	// Change to 2's complement and convert from 250dps to 1000dps (>>2)
		data = (offset[ii] & 0xFF00) >> 8;		// Get the high order byte
		inv_icm20948_write_mems_reg(s, reg_addr++, 1, &data);
		data = offset[ii] & 0x00FF;				// get the low order byte
		inv_icm20948_write_mems_reg(s, reg_addr++, 1, &data);
	}

	// Set Accel offset
	reg_addr = REG_XA_OFFS_H;
	for (ii = 0; ii < 3; ii++) {
		inv_icm20948_read_mems_reg(s, reg_addr, 1, &data);			// Get current offset value (16 bits in two registers)
		old_offset = data << 8;
		inv_icm20948_read_mems_reg(s, reg_addr + 1, 1, &data);
		old_offset += data;
		delta_offset = raw_bias[ACCEL_OFFSET + ii] >> 3;			// Convert from 2gto 16g (>>3)
		new_offset = old_offset - delta_offset;						// Store the delta of old value and self-test result
		data = (new_offset & 0xFF00) >> 8;							// Take high order byte
		inv_icm20948_write_mems_reg(s, reg_addr++, 1, &data);
		data = new_offset & 0x00FE;									// Only take the high order 7 bits
		inv_icm20948_write_mems_reg(s, reg_addr++, 1, &data);
		reg_addr++;													// Skip over unused register
	}
}


int inv_icm20948_firmware_load(struct inv_icm20948 * s, const unsigned char *data_start, unsigned short size_start, unsigned short load_addr)
{ 
    int write_size;
    int result;
    unsigned short memaddr;
    const unsigned char *data;
    unsigned short size;
    unsigned char data_cmp[INV_MAX_SERIAL_READ];
    int flag = 0;

	if(s->base_state.firmware_loaded)
		return 0;
		
    // Write DMP memory
    data = data_start;
    size = size_start;
    memaddr = load_addr;
    while (size > 0) {
        write_size = MIN(size, INV_MAX_SERIAL_WRITE);
        if ((memaddr & 0xff) + write_size > 0x100) {
            // Moved across a bank
            write_size = (memaddr & 0xff) + write_size - 0x100;
        }
        result = inv_icm20948_write_mems(s, memaddr, write_size, (unsigned char *)data); 
        if (result)  
            return result;
        data += write_size;
        size -= write_size;
        memaddr += write_size;
    }

    // Verify DMP memory

    data = data_start;
    size = size_start;
    memaddr = load_addr;
    while (size > 0) {
        write_size = MIN(size, INV_MAX_SERIAL_READ);
        if ((memaddr & 0xff) + write_size > 0x100) {
            // Moved across a bank
            write_size = (memaddr & 0xff) + write_size - 0x100;
        }
        result = inv_icm20948_read_mems(s, memaddr, write_size, data_cmp);
        if (result)
            flag++; // Error, DMP not written correctly
        if (memcmp(data_cmp, data, write_size))
            return -1;
        data += write_size;
        size -= write_size;
        memaddr += write_size;
    }

#if defined(WIN32)   
    //if(!flag)
      // inv_log("DMP Firmware was updated successfully..\r\n");
#endif

    return 0;
}

/* dmp3a.20x48-0.4.1 */

#define CFG_FIFO_SIZE                   (4222)

// data output control
#define DATA_OUT_CTL1			(4 * 16)
#define DATA_OUT_CTL2			(4 * 16 + 2)
#define DATA_INTR_CTL			(4 * 16 + 12)
#define FIFO_WATERMARK			(31 * 16 + 14)

// motion event control
#define MOTION_EVENT_CTL		(4 * 16 + 14)

// indicates to DMP which sensors are available
/*	1: gyro samples available
2: accel samples available
8: secondary samples available	*/
#define DATA_RDY_STATUS			(8 * 16 + 10)

// batch mode
#define BM_BATCH_CNTR			(27 * 16)
#define BM_BATCH_THLD			(19 * 16 + 12)
#define BM_BATCH_MASK			(21 * 16 + 14)

// sensor output data rate
#define ODR_ACCEL				(11 * 16 + 14)
#define ODR_GYRO				(11 * 16 + 10)
#define ODR_CPASS				(11 * 16 +  6)
#define ODR_ALS					(11 * 16 +  2)
#define ODR_QUAT6				(10 * 16 + 12)
#define ODR_QUAT9				(10 * 16 +  8)
#define ODR_PQUAT6				(10 * 16 +  4)
#define ODR_GEOMAG				(10 * 16 +  0)
#define ODR_PRESSURE			(11 * 16 + 12)
#define ODR_GYRO_CALIBR			(11 * 16 +  8)
#define ODR_CPASS_CALIBR		(11 * 16 +  4)

// sensor output data rate counter
#define ODR_CNTR_ACCEL			(9 * 16 + 14)
#define ODR_CNTR_GYRO			(9 * 16 + 10)
#define ODR_CNTR_CPASS			(9 * 16 +  6)
#define ODR_CNTR_ALS			(9 * 16 +  2)
#define ODR_CNTR_QUAT6			(8 * 16 + 12)
#define ODR_CNTR_QUAT9			(8 * 16 +  8)
#define ODR_CNTR_PQUAT6			(8 * 16 +  4)
#define ODR_CNTR_GEOMAG			(8 * 16 +  0)
#define ODR_CNTR_PRESSURE		(9 * 16 + 12)
#define ODR_CNTR_GYRO_CALIBR	(9 * 16 +  8)
#define ODR_CNTR_CPASS_CALIBR	(9 * 16 +  4)

// mounting matrix
#define CPASS_MTX_00            (23 * 16)
#define CPASS_MTX_01            (23 * 16 + 4)
#define CPASS_MTX_02            (23 * 16 + 8)
#define CPASS_MTX_10            (23 * 16 + 12)
#define CPASS_MTX_11            (24 * 16)
#define CPASS_MTX_12            (24 * 16 + 4)
#define CPASS_MTX_20            (24 * 16 + 8)
#define CPASS_MTX_21            (24 * 16 + 12)
#define CPASS_MTX_22            (25 * 16)

#define GYRO_SF					(19 * 16)
#define ACCEL_FB_GAIN			(34 * 16)
#define ACCEL_ONLY_GAIN			(16 * 16 + 12)

// bias calibration
#define GYRO_BIAS_X				(139 * 16 +  4)
#define GYRO_BIAS_Y				(139 * 16 +  8)
#define GYRO_BIAS_Z				(139 * 16 + 12)
#define GYRO_ACCURACY			(138 * 16 +  2)
#define GYRO_BIAS_SET			(138 * 16 +  6)
#define GYRO_LAST_TEMPR			(134 * 16)
#define GYRO_SLOPE_X			( 78 * 16 +  4)
#define GYRO_SLOPE_Y			( 78 * 16 +  8)
#define GYRO_SLOPE_Z			( 78 * 16 + 12)

#define ACCEL_BIAS_X            (110 * 16 +  4)
#define ACCEL_BIAS_Y            (110 * 16 +  8)
#define ACCEL_BIAS_Z            (110 * 16 + 12)
#define ACCEL_ACCURACY			(97 * 16)
#define ACCEL_CAL_RESET			(77 * 16)
#define ACCEL_VARIANCE_THRESH	(93 * 16)
#define ACCEL_CAL_RATE			(94 * 16 + 4)
#define ACCEL_PRE_SENSOR_DATA	(97 * 16 + 4)
#define ACCEL_COVARIANCE		(101 * 16 + 8)
#define ACCEL_ALPHA_VAR			(91 * 16)
#define ACCEL_A_VAR				(92 * 16)
#define ACCEL_CAL_INIT			(94 * 16 + 2)
#define ACCEL_CAL_SCALE_COVQ_IN_RANGE	(194 * 16)
#define ACCEL_CAL_SCALE_COVQ_OUT_RANGE	(195 * 16)
#define ACCEL_CAL_TEMPERATURE_SENSITIVITY	(194 * 16 + 4)
#define ACCEL_CAL_TEMPERATURE_OFFSET_TRIM	(194 * 16 + 12)

#define CPASS_BIAS_X            (126 * 16 +  4)
#define CPASS_BIAS_Y            (126 * 16 +  8)
#define CPASS_BIAS_Z            (126 * 16 + 12)
#define CPASS_ACCURACY			(37 * 16)
#define CPASS_BIAS_SET			(34 * 16 + 14)
#define MAR_MODE				(37 * 16 + 2)
#define CPASS_COVARIANCE		(115 * 16)
#define CPASS_COVARIANCE_CUR	(118 * 16 +  8)
#define CPASS_REF_MAG_3D		(122 * 16)
#define CPASS_CAL_INIT			(114 * 16)
#define CPASS_EST_FIRST_BIAS	(113 * 16)
#define MAG_DISTURB_STATE		(113 * 16 + 2)
#define CPASS_VAR_COUNT			(112 * 16 + 6)
#define CPASS_COUNT_7			( 87 * 16 + 2)
#define CPASS_MAX_INNO			(124 * 16)
#define CPASS_BIAS_OFFSET		(113 * 16 + 4)
#define CPASS_CUR_BIAS_OFFSET	(114 * 16 + 4)
#define CPASS_PRE_SENSOR_DATA	( 87 * 16 + 4)

// Compass Cal params to be adjusted according to sampling rate
#define CPASS_TIME_BUFFER		(112 * 16 + 14)
#define CPASS_RADIUS_3D_THRESH_ANOMALY	(112 * 16 + 8)

#define CPASS_STATUS_CHK		(25 * 16 + 12)

// 9-axis
#define MAGN_THR_9X				(80 * 16)
#define MAGN_LPF_THR_9X			(80 * 16 +  8)
#define QFB_THR_9X				(80 * 16 + 12)

// DMP running counter
#define DMPRATE_CNTR			(18 * 16 + 4)

// pedometer
#define PEDSTD_BP_B				(49 * 16 + 12)
#define PEDSTD_BP_A4			(52 * 16)
#define PEDSTD_BP_A3			(52 * 16 +  4)
#define PEDSTD_BP_A2			(52 * 16 +  8)
#define PEDSTD_BP_A1			(52 * 16 + 12)
#define PEDSTD_SB				(50 * 16 +  8)
#define PEDSTD_SB_TIME			(50 * 16 + 12)
#define PEDSTD_PEAKTHRSH		(57 * 16 +  8)
#define PEDSTD_TIML				(50 * 16 + 10)
#define PEDSTD_TIMH				(50 * 16 + 14)
#define PEDSTD_PEAK				(57 * 16 +  4)
#define PEDSTD_STEPCTR			(54 * 16)
#define PEDSTD_STEPCTR2			(58 * 16 +  8)
#define PEDSTD_TIMECTR			(60 * 16 +  4)
#define PEDSTD_DECI				(58 * 16)
#define PEDSTD_SB2				(60 * 16 + 14)
#define STPDET_TIMESTAMP		(18 * 16 +  8)
#define PEDSTEP_IND				(19 * 16 +  4)
#define PED_Y_RATIO				(17 * 16 +  0)

// SMD
#define SMD_VAR_TH              (141 * 16 + 12)
#define SMD_VAR_TH_DRIVE        (143 * 16 + 12)
#define SMD_DRIVE_TIMER_TH      (143 * 16 +  8)
#define SMD_TILT_ANGLE_TH       (179 * 16 + 12)
#define BAC_SMD_ST_TH           (179 * 16 +  8)
#define BAC_ST_ALPHA4           (180 * 16 + 12)
#define BAC_ST_ALPHA4A          (176 * 16 + 12)

// Wake on Motion
#define WOM_ENABLE              (64 * 16 + 14)
#define WOM_STATUS              (64 * 16 + 6)
#define WOM_THRESHOLD           (64 * 16)
#define WOM_CNTR_TH             (64 * 16 + 12)

// Activity Recognition
#define BAC_RATE                (48  * 16 + 10)
#define BAC_STATE               (179 * 16 +  0)
#define BAC_STATE_PREV          (179 * 16 +  4)
#define BAC_ACT_ON              (182 * 16 +  0)
#define BAC_ACT_OFF             (183 * 16 +  0)
#define BAC_STILL_S_F           (177 * 16 +  0)
#define BAC_RUN_S_F             (177 * 16 +  4)
#define BAC_DRIVE_S_F           (178 * 16 +  0)
#define BAC_WALK_S_F            (178 * 16 +  4)
#define BAC_SMD_S_F             (178 * 16 +  8)
#define BAC_BIKE_S_F            (178 * 16 + 12)
#define BAC_E1_SHORT            (146 * 16 +  0)
#define BAC_E2_SHORT            (146 * 16 +  4)
#define BAC_E3_SHORT            (146 * 16 +  8)
#define BAC_VAR_RUN             (148 * 16 + 12)
#define BAC_TILT_INIT           (181 * 16 +  0)
#define BAC_MAG_ON              (225 * 16 +  0)
#define BAC_PS_ON               (74  * 16 +  0)
#define BAC_BIKE_PREFERENCE     (173 * 16 +  8)
#define BAC_MAG_I2C_ADDR        (229 * 16 +  8)
#define BAC_PS_I2C_ADDR         (75  * 16 +  4)
#define BAC_DRIVE_CONFIDENCE    (144 * 16 +  0)
#define BAC_WALK_CONFIDENCE     (144 * 16 +  4)
#define BAC_SMD_CONFIDENCE      (144 * 16 +  8)
#define BAC_BIKE_CONFIDENCE     (144 * 16 + 12)
#define BAC_STILL_CONFIDENCE    (145 * 16 +  0)
#define BAC_RUN_CONFIDENCE      (145 * 16 +  4)
#define BAC_MODE_CNTR           (150 * 16)
#define BAC_STATE_T_PREV        (185 * 16 +  4)
#define BAC_ACT_T_ON            (184 * 16 +  0)
#define BAC_ACT_T_OFF           (184 * 16 +  4)
#define BAC_STATE_WRDBS_PREV    (185 * 16 +  8)
#define BAC_ACT_WRDBS_ON        (184 * 16 +  8)
#define BAC_ACT_WRDBS_OFF       (184 * 16 + 12)
#define BAC_ACT_ON_OFF          (190 * 16 +  2)
#define PREV_BAC_ACT_ON_OFF     (188 * 16 +  2)
#define BAC_CNTR                (48  * 16 +  2)

// Flip/Pick-up
#define FP_VAR_ALPHA            (245 * 16 +  8)
#define FP_STILL_TH             (246 * 16 +  4)
#define FP_MID_STILL_TH         (244 * 16 +  8)
#define FP_NOT_STILL_TH         (246 * 16 +  8)
#define FP_VIB_REJ_TH           (241 * 16 +  8)
#define FP_MAX_PICKUP_T_TH      (244 * 16 + 12)
#define FP_PICKUP_TIMEOUT_TH    (248 * 16 +  8)
#define FP_STILL_CONST_TH       (246 * 16 + 12)
#define FP_MOTION_CONST_TH      (240 * 16 +  8)
#define FP_VIB_COUNT_TH         (242 * 16 +  8)
#define FP_STEADY_TILT_TH       (247 * 16 +  8)
#define FP_STEADY_TILT_UP_TH    (242 * 16 + 12)
#define FP_Z_FLAT_TH_MINUS      (243 * 16 +  8)
#define FP_Z_FLAT_TH_PLUS       (243 * 16 + 12)
#define FP_DEV_IN_POCKET_TH     (76  * 16 + 12)
#define FP_PICKUP_CNTR          (247 * 16 +  4)
#define FP_RATE                 (240 * 16 + 12)

// Gyro FSR
#define GYRO_FULLSCALE          (72 * 16 + 12)

// Accel FSR
#define ACC_SCALE               (30 * 16 + 0)
#define ACC_SCALE2              (79 * 16 + 4)

// EIS authentication
#define EIS_AUTH_INPUT			(160 * 16 +   4)
#define EIS_AUTH_OUTPUT			(160 * 16 +   0)

// B2S
#define B2S_RATE                (48  * 16 +   8)
// mounting matrix
#define B2S_MTX_00              (208 * 16)
#define B2S_MTX_01              (208 * 16 + 4)
#define B2S_MTX_02              (208 * 16 + 8)
#define B2S_MTX_10              (208 * 16 + 12)
#define B2S_MTX_11              (209 * 16)
#define B2S_MTX_12              (209 * 16 + 4)
#define B2S_MTX_20              (209 * 16 + 8)
#define B2S_MTX_21              (209 * 16 + 12)
#define B2S_MTX_22              (210 * 16)

// Dmp3 orientation parameters (Q30) initialization
#define Q0_QUAT6				(33 * 16 + 0)
#define Q1_QUAT6				(33 * 16 + 4)
#define Q2_QUAT6				(33 * 16 + 8)
#define Q3_QUAT6				(33 * 16 + 12)

#define DMP_START_ADDRESS   ((unsigned short)0x1000)
#define DMP_MEM_BANK_SIZE   256
#define DMP_LOAD_START      0x90

#define DMP_CODE_SIZE 14301

/** Loads the dmp firmware for the icm20948 part.
* @param[in] dmp_image_sram Load DMP3 image from SRAM.
*/
int inv_icm20948_load_firmware(struct inv_icm20948 * s, const unsigned char *dmp3_image, unsigned int dmp3_image_size)
{
	return inv_icm20948_firmware_load(s, dmp3_image, dmp3_image_size, DMP_LOAD_START);
}

/** Loads the dmp firmware for the icm20948 part.
* @param[out] dmp_cnfg The config item
*/
void inv_icm20948_get_dmp_start_address(struct inv_icm20948 * s, unsigned short *dmp_cnfg)
{

	(void)s;

	*dmp_cnfg = DMP_START_ADDRESS;
}

/**
* Sets data output control register 1.
* @param[in] output_mask	Turns sensors on/off according to following bit definition,
*							bit set indicates on, bit clear indicates off.
*							DMP will also turn hw sensors on/off based on bits set in output_mask.
*
*	ACCEL_SET			0x8000 - calibrated accel if accel calibrated, raw accel otherwise
*	GYRO_SET			0x4000 - raw gyro
*	CPASS_SET			0x2000 - raw magnetic
*	ALS_SET				0x1000 - ALS/proximity
*	QUAT6_SET			0x0800 - game rotation vector
*	QUAT9_SET			0x0400 - rotation vector with heading accuracy
*	PQUAT6_SET			0x0200 - truncated game rotation vector for batching
*	GEOMAG_SET			0x0100 - geomag rotation vector with heading accuracy
*	PRESSURE_SET		0x0080 - pressure
*	GYRO_CALIBR_SET		0x0040 - calibrated gyro
*	CPASS_CALIBR_SET	0x0020 - calibrated magnetic
*	PED_STEPDET_SET		0x0010 - timestamp when each step is detected
*	HEADER2_SET			0x0008 - enable/disable data output in data output control register 2
*	PED_STEPIND_SET		0x0007 - number of steps detected will be attached to the 3 least significant bits of header
*/
int dmp_icm20948_set_data_output_control1(struct inv_icm20948 * s, int output_mask)
{

	int result;
	unsigned char data_output_control_reg1[2];

	data_output_control_reg1[0] = (unsigned char)(output_mask >> 8);
	data_output_control_reg1[1] = (unsigned char)(output_mask & 0xff);

	result = inv_icm20948_write_mems(s, DATA_OUT_CTL1, 2, data_output_control_reg1);

	return result;
}

/**
* Sets data output control register 2.
* @param[in] output_mask	Turns features on/off according to following bit definition,
*							bit set indicates on, bit clear indicates off.
*
*	ACCEL_ACCURACY_SET	0x4000 - accel accuracy when changes, HEADER2_SET also needs to be set in data output control regsiter 1
*	GYRO_ACCURACY_SET	0x2000 - gyro accuracy when changes, HEADER2_SET also needs to be set in data output control regsiter 1
*	CPASS_ACCURACY_SET	0x1000 - compass accuracy when changes, HEADER2_SET also needs to be set in data output control regsiter 1
*	BATCH_MODE_EN		0x0100 - enable batching
*/
int dmp_icm20948_set_data_output_control2(struct inv_icm20948 * s, int output_mask)
{
	int result;

	memset(data_output_control_reg2, 0, sizeof(data_output_control_reg2));

	data_output_control_reg2[0] = (unsigned char)(output_mask >> 8);
	data_output_control_reg2[1] = (unsigned char)(output_mask & 0xff);

	result = inv_icm20948_write_mems(s, DATA_OUT_CTL2, 2, data_output_control_reg2);

	return result;
}

/**
* Clears all output control registers:
*	data output control register 1, data output control register 2, data interrupt control register, motion event control regsiter, data ready status register
*/
int dmp_icm20948_reset_control_registers(struct inv_icm20948 * s)
{
	int result;
	unsigned char data[4]={0};

	//reset data output control registers
	result = inv_icm20948_write_mems(s, DATA_OUT_CTL1, 2, &data[0]);
	result += inv_icm20948_write_mems(s, DATA_OUT_CTL2, 2, &data[0]);

	//reset data interrupt control register
	result += inv_icm20948_write_mems(s, DATA_INTR_CTL, 2, &data[0]);

	//reset motion event control register
	result += inv_icm20948_write_mems(s, MOTION_EVENT_CTL, 2, &data[0]);

	//reset data ready status register
	result += inv_icm20948_write_mems(s, DATA_RDY_STATUS, 2, &data[0]);
	//result += inv_icm20948_write_mems(s, DATA_RDY_STATUS, 2, inv_icm20948_convert_int16_to_big8(3, data)); //fixme

	if (result) 
		return result;

	return 0;
}

/**
* Sets data interrupt control register.
* @param[in] interrupt_ctl	Determines which sensors can generate interrupt according to following bit definition,
*							bit set indicates interrupt, bit clear indicates no interrupt.
*
*	ACCEL_SET			0x8000 - calibrated accel if accel calibrated, raw accel otherwise
*	GYRO_SET			0x4000 - raw gyro
*	CPASS_SET			0x2000 - raw magnetic
*	ALS_SET				0x1000 - ALS/proximity
*	QUAT6_SET			0x0800 - game rotation vector
*	QUAT9_SET			0x0400 - rotation vector with heading accuracy
*	PQUAT6_SET			0x0200 - truncated game rotation vector for batching
*	GEOMAG_SET			0x0100 - geomag rotation vector with heading accuracy
*	PRESSURE_SET		0x0080 - pressure
*	GYRO_CALIBR_SET		0x0040 - calibrated gyro
*	CPASS_CALIBR_SET	0x0020 - calibrated magnetic
*	PED_STEPDET_SET		0x0010 - timestamp when each step is detected
*	HEADER2_SET			0x0008 - data output defined in data output control register 2
*	PED_STEPIND_SET		0x0007 - number of steps detected will be attached to the 3 least significant bits of header
*/
int dmp_icm20948_set_data_interrupt_control(struct inv_icm20948 * s, uint32_t interrupt_ctl)
{
	int result;
	unsigned char big8[2]={0};

	result = inv_icm20948_write_mems(s, DATA_INTR_CTL, 2, inv_icm20948_convert_int16_to_big8(interrupt_ctl, big8));

	if (result) 
		return result;

	return 0;
}

/**
* Sets FIFO watermark. DMP will send FIFO interrupt if FIFO count > FIFO watermark
* @param[in] fifo_wm	FIFO watermark set to 80% of actual FIFO size by default
*/
int dmp_icm20948_set_FIFO_watermark(struct inv_icm20948 * s, unsigned short fifo_wm)
{
	int result;
	unsigned char big8[2]={0};

	result = inv_icm20948_write_mems(s, FIFO_WATERMARK, 2, inv_icm20948_convert_int16_to_big8(fifo_wm,big8));

	if (result)
		return result;

	return 0;
}

/**
* Sets data rdy status register.
* @param[in] data_rdy	Indicates which sensor data is available.
*
*	gyro samples available		0x1
*	accel samples available		0x2
*	secondary samples available	0x8
*/
int dmp_icm20948_set_data_rdy_status(struct inv_icm20948 * s, unsigned short data_rdy)
{
	int result;
	unsigned char big8[2]={0};

	result = inv_icm20948_write_mems(s, DATA_RDY_STATUS, 2, inv_icm20948_convert_int16_to_big8(data_rdy, big8));

	if (result) 
		return result;

	return 0;
}

/**
* Sets motion event control register.
* @param[in] output_mask	Turns features on/off according to following bit definition,
*							bit set indicates on, bit clear indicates off.
*
*   BAC_WEAR_EN         0x8000 - change BAC behavior for wearable platform
*	PEDOMETER_EN		0x4000 - pedometer engine
*	PEDOMETER_INT_EN	0x2000 - pedometer step detector interrupt
*	SMD_EN				0x0800 - significant motion detection interrupt
*	ACCEL_CAL_EN		0x0200 - accel calibration
*	GYRO_CAL_EN			0x0100 - gyro calibration
*	COMPASS_CAL_EN		0x0080 - compass calibration
*	NINE_AXIS_EN        0x0040 - 9-axis algorithm execution
*	GEOMAG_EN			0x0008 - Geomag algorithm execution
*	BTS_LTS_EN          0x0004 - bring & look to see
*	BAC_ACCEL_ONLY_EN   0x0002 - run BAC as accel only
*/
int dmp_icm20948_set_motion_event_control(struct inv_icm20948 * s, unsigned short output_mask)
{
	int result;
	unsigned char motion_event_control_reg[2];

	motion_event_control_reg[0] = (unsigned char)(output_mask >> 8);
	motion_event_control_reg[1] = (unsigned char)(output_mask & 0xff);

	result = inv_icm20948_write_mems(s, MOTION_EVENT_CTL, 2, motion_event_control_reg);

	return result;
}

/**
* Sets sensor ODR.
* @param[in] sensor		sensor number based on INV_SENSORS
*	enum INV_SENSORS {
*		INV_SENSOR_ACCEL = 0,
*		INV_SENSOR_GYRO,        
*	    INV_SENSOR_LPQ,
*		INV_SENSOR_COMPASS,
*		INV_SENSOR_ALS,
*		INV_SENSOR_SIXQ,
*		INV_SENSOR_NINEQ,
*		INV_SENSOR_GEOMAG,
*		INV_SENSOR_PEDQ,
*		INV_SENSOR_PRESSURE,
*		INV_SENSOR_CALIB_GYRO,
*		INV_SENSOR_CALIB_COMPASS,
*		INV_SENSOR_NUM_MAX,
*		INV_SENSOR_INVALID,
*	};					
* @param[in] divider	desired ODR = base engine rate/(divider + 1)
*/
int dmp_icm20948_set_sensor_rate(struct inv_icm20948 * s, int invSensor, short divider)
{
	int result;
	unsigned char big8[2]={0};
	int odr_addr = 0;

	switch (invSensor) {
	case INV_SENSOR_ACCEL:
		odr_addr = ODR_ACCEL;
		break;
	case INV_SENSOR_GYRO:
		odr_addr = ODR_GYRO;
		break;
	case INV_SENSOR_COMPASS:
		odr_addr = ODR_CPASS;
		break;
	case INV_SENSOR_ALS:
		odr_addr = ODR_ALS;
		break;
	case INV_SENSOR_SIXQ:
		odr_addr = ODR_QUAT6;
		break;
	case INV_SENSOR_NINEQ:
		odr_addr = ODR_QUAT9;
		break;
	case INV_SENSOR_GEOMAG:
		odr_addr = ODR_GEOMAG;
		break;
	case INV_SENSOR_PEDQ:
		odr_addr = ODR_PQUAT6;
		break;
	case INV_SENSOR_PRESSURE:
		odr_addr = ODR_PRESSURE;
		break;
	case INV_SENSOR_CALIB_GYRO:
		odr_addr = ODR_GYRO_CALIBR;
		break;
	case INV_SENSOR_CALIB_COMPASS:
		odr_addr = ODR_CPASS_CALIBR;
		break;
	case INV_SENSOR_STEP_COUNTER:
		//odr_addr = PED_RATE + 2; //PED_RATE is a 4-byte address but only writing 2 bytes here
		break;
	}	

	result = inv_icm20948_write_mems(s, odr_addr, 2, inv_icm20948_convert_int16_to_big8(divider, big8));

	if (result)
		return result;

	return 0;
}

/**
* Resets batch counter and sets batch mode parameters.
* @param[in] thld	sets batch timeout in DMP ticks, e.g. batch 1 sec, thld= (1 sec * engine base rate in Hz)
* @param[in] mask	ties batch counter to engine specified with same bit definiton as HW register DATA_RDY_STATUS,
*					i.e. batch counter increments only if the engine specified is available in multi-rate setting
*	BIT 0 set: 1 - tie to gyro
*	BIT 1 set: 2 - tie to accel
*	BIT 2 set: 4 - tie to pressure in Diamond
*	BIT 3 set: 8 - tie to secondary
*/
int dmp_icm20948_set_batchmode_params(struct inv_icm20948 * s, unsigned int thld, short mask)
{
	int result;
	unsigned char big8[4]={0};
	unsigned char data[2]={0};

	result = inv_icm20948_write_mems(s, BM_BATCH_CNTR, 4, big8);
	result += inv_icm20948_write_mems(s, BM_BATCH_THLD, 4, inv_icm20948_convert_int32_to_big8(thld,big8));
	result += inv_icm20948_write_mems(s, BM_BATCH_MASK, 2, inv_icm20948_convert_int16_to_big8(mask,data));

	if (result)
		return result;

	return 0;
}

/**
* Sets acc's bias in DMP.
* @param[in] bias
*	array is set as follows:
*	[0] accel_x
*	[1] accel_y
*	[2] accel_z
*/
int dmp_icm20948_set_bias_acc(struct inv_icm20948 * s, int *bias)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_write_mems(s, ACCEL_BIAS_X, 4, inv_icm20948_convert_int32_to_big8(bias[0], big8));
	result += inv_icm20948_write_mems(s, ACCEL_BIAS_Y, 4, inv_icm20948_convert_int32_to_big8(bias[1], big8));
	result += inv_icm20948_write_mems(s, ACCEL_BIAS_Z, 4, inv_icm20948_convert_int32_to_big8(bias[2], big8));

	if (result)
		return result;

	return 0; 
}

/**
* Sets gyro's bias in DMP.
* @param[in] bias
*	array is set as follows:
*	[0] gyro_x
*	[1] gyro_y
*	[2] gyro_z
*/
int dmp_icm20948_set_bias_gyr(struct inv_icm20948 * s, int *bias)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_write_mems(s, GYRO_BIAS_X, 4, inv_icm20948_convert_int32_to_big8(bias[0], big8));
	result += inv_icm20948_write_mems(s, GYRO_BIAS_Y, 4, inv_icm20948_convert_int32_to_big8(bias[1], big8));
	result += inv_icm20948_write_mems(s, GYRO_BIAS_Z, 4, inv_icm20948_convert_int32_to_big8(bias[2], big8));

	if (result)
		return result;

	return 0; 
}

/**
* Sets compass' bias in DMP.
* @param[in] bias
*	array is set as follows:
*	[0] compass_x
*	[1] compass_y
*	[2] compass_z
*/
int dmp_icm20948_set_bias_cmp(struct inv_icm20948 * s, int *bias)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_write_mems(s, CPASS_BIAS_X, 4, inv_icm20948_convert_int32_to_big8(bias[0], big8));
	result += inv_icm20948_write_mems(s, CPASS_BIAS_Y, 4, inv_icm20948_convert_int32_to_big8(bias[1], big8));
	result += inv_icm20948_write_mems(s, CPASS_BIAS_Z, 4, inv_icm20948_convert_int32_to_big8(bias[2], big8));

	if (result)
		return result;

	return 0; 
}

/**
* Gets acc's bias from DMP.
* @param[in] bias
* @param[out] bias
*	array is set as follows:
*	[0] accel_x
*	[1] accel_y
*	[2] accel_z
*/
int dmp_icm20948_get_bias_acc(struct inv_icm20948 * s, int *bias)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_read_mems(s, ACCEL_BIAS_X, 4, big8);
	bias[0] = inv_icm20948_convert_big8_to_int32(big8);
	result += inv_icm20948_read_mems(s, ACCEL_BIAS_Y, 4, big8);
	bias[1] = inv_icm20948_convert_big8_to_int32(big8);
	result += inv_icm20948_read_mems(s, ACCEL_BIAS_Z, 4, big8);
	bias[2] = inv_icm20948_convert_big8_to_int32(big8);

	if (result)
		return result;

	return 0; 
}

/**
* Gets gyro's bias from DMP.
* @param[in] bias
* @param[out] bias
*	array is set as follows:
*	[0] gyro_x
*	[1] gyro_y
*	[2] gyro_z
*/
int dmp_icm20948_get_bias_gyr(struct inv_icm20948 * s, int *bias)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_read_mems(s, GYRO_BIAS_X, 4, big8);
	bias[0] = inv_icm20948_convert_big8_to_int32(big8);
	result += inv_icm20948_read_mems(s, GYRO_BIAS_Y, 4, big8);
	bias[1] = inv_icm20948_convert_big8_to_int32(big8);
	result += inv_icm20948_read_mems(s, GYRO_BIAS_Z, 4, big8);
	bias[2] = inv_icm20948_convert_big8_to_int32(big8);

	if (result)
		return result;

	return 0; 
}

/**
* Gets compass' bias from DMP.
* @param[in] bias
* @param[out] bias
*	array is set as follows:
*	[0] compass_x
*	[1] compass_y
*	[2] compass_z
*/
int dmp_icm20948_get_bias_cmp(struct inv_icm20948 * s, int *bias)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_read_mems(s, CPASS_BIAS_X, 4, big8);
	bias[0] = inv_icm20948_convert_big8_to_int32(big8);
	result += inv_icm20948_read_mems(s, CPASS_BIAS_Y, 4, big8);
	bias[1] = inv_icm20948_convert_big8_to_int32(big8);
	result += inv_icm20948_read_mems(s, CPASS_BIAS_Z, 4, big8);
	bias[2] = inv_icm20948_convert_big8_to_int32(big8);

	if (result)
		return result;

	return 0; 
}

/**
* Sets the gyro_sf used by quaternions on the DMP.
* @param[in] gyro_sf	see inv_icm20948_set_gyro_sf() for value to set based on gyro rate and gyro fullscale range
*/
int dmp_icm20948_set_gyro_sf(struct inv_icm20948 * s, long gyro_sf)
{
	int result;
	unsigned char big8[4];

	result = inv_icm20948_write_mems(s, GYRO_SF, 4, inv_icm20948_convert_int32_to_big8(gyro_sf, big8));

	return result;
}

/**
* Sets the accel gain used by accel quaternion on the DMP.
* @param[in] accel_gain		value changes with accel engine rate
*/
int dmp_icm20948_set_accel_feedback_gain(struct inv_icm20948 * s, int accel_gain)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_write_mems(s, ACCEL_ONLY_GAIN, 4, inv_icm20948_convert_int32_to_big8(accel_gain, big8));

	if (result)
		return result;

	return 0;
}

/**
* Sets accel cal parameters based on different accel engine rate/accel cal running rate
* @param[in] accel_cal
*	array is set as follows:
*	[0] = ACCEL_CAL_ALPHA_VAR
*	[1] = ACCEL_CAL_A_VAR
*   [2] = ACCEL_CAL_DIV - divider from hardware accel engine rate such that acce cal runs at accel_engine_rate/(divider+1)
*/
int dmp_icm20948_set_accel_cal_params(struct inv_icm20948 * s, int *accel_cal)
{
	int result;
	unsigned char big8[4]={0};

	result  = inv_icm20948_write_mems(s, ACCEL_ALPHA_VAR, 4, inv_icm20948_convert_int32_to_big8(accel_cal[ACCEL_CAL_ALPHA_VAR], big8));
	result |= inv_icm20948_write_mems(s, ACCEL_A_VAR, 4, inv_icm20948_convert_int32_to_big8(accel_cal[ACCEL_CAL_A_VAR], big8));
	result |= inv_icm20948_write_mems(s, ACCEL_CAL_RATE, 2, inv_icm20948_convert_int16_to_big8(accel_cal[ACCEL_CAL_DIV], big8));

	if (result)
		return result;

	return 0;
}

/**
* Initialize the orientation parameters.
* @param[in] orientation_params		Orientation parameters in Q30 format
*/
int dmp_icm20948_set_orientation_params(struct inv_icm20948 * s, int *orientation_params)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_write_mems(s, Q0_QUAT6, 4, inv_icm20948_convert_int32_to_big8(orientation_params[0], big8));
	result += inv_icm20948_write_mems(s, Q1_QUAT6, 4, inv_icm20948_convert_int32_to_big8(orientation_params[1], big8));
	result += inv_icm20948_write_mems(s, Q2_QUAT6, 4, inv_icm20948_convert_int32_to_big8(orientation_params[2], big8));
	result += inv_icm20948_write_mems(s, Q3_QUAT6, 4, inv_icm20948_convert_int32_to_big8(orientation_params[3], big8));

	if (result)
		return result;

	return 0;
}

/**
* Sets compass cal parameters based on different compass engine rate/compass cal running rate
* @param[in] compass_cal
*	array is set as follows:
*	[0] = CPASS_CAL_TIME_BUFFER
*	[1] = CPASS_CAL_ALPHA_VAR
*	[2] = CPASS_CAL_A_VAR
*	[3] = CPASS_CAL_RADIUS_3D_THRESH_ANOMALY
*	[4] = CPASS_CAL_NOMOT_VAR_THRESH
*/
int dmp_icm20948_set_compass_cal_params(struct inv_icm20948 * s, int *compass_cal)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_write_mems(s, CPASS_TIME_BUFFER, 2, inv_icm20948_convert_int16_to_big8(compass_cal[CPASS_CAL_TIME_BUFFER], big8));
	result += inv_icm20948_write_mems(s, CPASS_RADIUS_3D_THRESH_ANOMALY, 4, inv_icm20948_convert_int32_to_big8(compass_cal[CPASS_CAL_RADIUS_3D_THRESH_ANOMALY], big8));

	if (result)
		return result;

	return 0;
}

/**
* Sets compass orientation matrix to DMP.
* @param[in] compass_mtx
*/
int dmp_icm20948_set_compass_matrix(struct inv_icm20948 * s, int *compass_mtx)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_write_mems(s, CPASS_MTX_00, 4, inv_icm20948_convert_int32_to_big8(compass_mtx[0], big8));
	result += inv_icm20948_write_mems(s, CPASS_MTX_01, 4, inv_icm20948_convert_int32_to_big8(compass_mtx[1], big8));
	result += inv_icm20948_write_mems(s, CPASS_MTX_02, 4, inv_icm20948_convert_int32_to_big8(compass_mtx[2], big8));
	result += inv_icm20948_write_mems(s, CPASS_MTX_10, 4, inv_icm20948_convert_int32_to_big8(compass_mtx[3], big8));
	result += inv_icm20948_write_mems(s, CPASS_MTX_11, 4, inv_icm20948_convert_int32_to_big8(compass_mtx[4], big8));
	result += inv_icm20948_write_mems(s, CPASS_MTX_12, 4, inv_icm20948_convert_int32_to_big8(compass_mtx[5], big8));
	result += inv_icm20948_write_mems(s, CPASS_MTX_20, 4, inv_icm20948_convert_int32_to_big8(compass_mtx[6], big8));
	result += inv_icm20948_write_mems(s, CPASS_MTX_21, 4, inv_icm20948_convert_int32_to_big8(compass_mtx[7], big8));
	result += inv_icm20948_write_mems(s, CPASS_MTX_22, 4, inv_icm20948_convert_int32_to_big8(compass_mtx[8], big8));

	if (result)
		return result;

	return 0;
}

/**
* Gets pedometer step count.
* @param[in] steps
* @param[out] steps
*/
int dmp_icm20948_get_pedometer_num_of_steps(struct inv_icm20948 * s, unsigned long *steps)
{
	int result;
	unsigned char big8[4]={0};
	(void)s;
	result = inv_icm20948_read_mems(s, PEDSTD_STEPCTR, 4, big8);
	if (result) 
		return result;
	*steps = (big8[0]*(1L<<24)) + (big8[1]*(1L<<16)) + (big8[2]*256) + big8[3];

	return 0;
}

/**
* Sets pedometer engine running rate.
* @param[in] ped_rate	divider based on accel engine rate
*/
int dmp_icm20948_set_pedometer_rate(struct inv_icm20948 * s, int ped_rate)
{
	// int result; 
	// unsigned char big8[4]={0};
	// result = inv_icm20948_write_mems(s, PED_RATE, 4, inv_icm20948_convert_int32_to_big8(ped_rate, big8));
	// if (result)
	//    return result;

	(void)s;
	(void) ped_rate;

	return 0;
}

/**
* Turns software wake on motion feature on/off.
* @param[in] enable		0=off, 1=on
*/
int dmp_icm20948_set_wom_enable(struct inv_icm20948 * s, unsigned char enable)
{
	int result;
	unsigned char big8[2]={0};

	if (enable) {
		big8[1]= 0x1;
	}

	result = inv_icm20948_write_mems(s, WOM_ENABLE, 2, big8);

	if (result)
		return result;

	return 0;
}

/**
* Sets motion threshold to determine motion/no motion for wake on motion feature.
* @param[in] threshold
*/
int dmp_icm20948_set_wom_motion_threshold(struct inv_icm20948 * s, int threshold)
{
	int result;
	unsigned char big8[4]={0};

	result = inv_icm20948_write_mems(s, WOM_THRESHOLD, 4, inv_icm20948_convert_int32_to_big8(threshold, big8));

	if (result)
		return result;

	return 0;
}

/**
* Sets minimum time threshold of no motion before DMP goes to sleep.
* @param[in] threshold
*/
int dmp_icm20948_set_wom_time_threshold(struct inv_icm20948 * s, unsigned short threshold)
{
	int result;
	unsigned char big8[2]={0};

	result = inv_icm20948_write_mems(s, WOM_CNTR_TH, 2, inv_icm20948_convert_int16_to_big8(threshold, big8));

	if (result)
		return result;

	return 0;
}

/**
* Sets scale in DMP to convert gyro data to 4000dps=2^30 regardless of fsr.
* @param[in] fsr for gyro parts
4000: 4000dps. 2000: 2000dps. 1000: 1000dps. 500: 500dps. 250: 250dps.

For 4000dps parts, 4000dps = 2^15.
DMP takes raw gyro data and left shifts by 16 bits, so (<<16) becomes 4000dps=2^31, to make 4000dps=2^30, >>1 bit.
In Q-30 math, >> 1 equals multiply by 2^29 = 536870912.

For 2000dps parts, 2000dps = 2^15.
DMP takes raw gyro data and left shifts by 16 bits, so (<<16) becomes 2000dps=2^31, to make 4000dps=2^30, >>2 bits.
In Q-30 math, >> 2 equals multiply by 2^28 = 268435456.
*/

int dmp_icm20948_set_gyro_fsr(struct inv_icm20948 * s, short gyro_fsr)
{
	unsigned char reg[4];
	int result;
	long scale;

	switch (gyro_fsr) {
	case 4000:
		scale =  536870912L;  // 2^29
		break;
	case 2000:
		scale =  268435456L;  // 2^28
		break;
	case 1000:
		scale = 134217728L;  // 2^27
		break;
	case 500:
		scale = 67108864L;  // 2^26
		break;
	case 250:
		scale = 33554432L;  // 2^25
		break;
	default:
		return -1;
	}

	result = inv_icm20948_write_mems(s, GYRO_FULLSCALE, 4, inv_icm20948_convert_int32_to_big8(scale,reg));

	if (result) {
		return result;
	} else {
		return 0;
	}
}

/**
* Sets scale in DMP to convert accel data to 1g=2^25 regardless of fsr.
* @param[in] fsr for accel parts
2: 2g. 4: 4g. 8: 8g. 16: 16g. 32: 32g.

For 2g parts, 2g = 2^15 -> 1g = 2^14,.
DMP takes raw accel data and left shifts by 16 bits, so 1g=2^14 (<<16) becomes 1g=2^30, to make 1g=2^25, >>5 bits.
In Q-30 math, >> 5 equals multiply by 2^25 = 33554432.

For 8g parts, 8g = 2^15 -> 1g = 2^12.
DMP takes raw accel data and left shifts by 16 bits, so 1g=2^12 (<<16) becomes 1g=2^28, to make 1g=2^25, >>3bits.
In Q-30 math, >> 3 equals multiply by 2^27 = 134217728.
*/
int dmp_icm20948_set_accel_fsr(struct inv_icm20948 * s, short accel_fsr)
{
	unsigned char reg[4];
	int result;
	long scale;

	switch (accel_fsr) {
	case 2:
		scale =  33554432L;  // 2^25
		break;
	case 4:
		scale =  67108864L;  // 2^26
		break;
	case 8:
		scale = 134217728L;  // 2^27
		break;
	case 16:
		scale = 268435456L;  // 2^28
		break;
	case 32:
		scale = 536870912L;  // 2^29
		break;
	default:
		return -1;
	}

	result = inv_icm20948_write_mems(s, ACC_SCALE, 4, inv_icm20948_convert_int32_to_big8(scale,reg));

	if (result) {
		return result;
	} else {
		return 0;
	}
}

/**
* According to input fsr, a scale factor will be set at memory location ACC_SCALE2
* to convert calibrated accel data to 16-bit format same as what comes out of MPU register.
* It is a reverse scaling of the scale factor written to ACC_SCALE.
* @param[in] fsr for accel parts
2: 2g. 4: 4g. 8: 8g. 16: 16g. 32: 32g.
*/
int dmp_icm20948_set_accel_scale2(struct inv_icm20948 * s, short accel_fsr)
{
	unsigned char reg[4];
	int result;
	long scale;

	switch (accel_fsr) {
	case 2:
		scale = 524288L;  // 2^19
		break;
	case 4:
		scale = 262144L;  // 2^18
		break;
	case 8:
		scale = 131072L;  // 2^17
		break;
	case 16:
		scale = 65536L;  // 2^16
		break;
	case 32:
		scale = 32768L;  // 2^15
		break;
	default:
		return -1;
	}

	result = inv_icm20948_write_mems(s, ACC_SCALE2, 4, inv_icm20948_convert_int32_to_big8(scale,reg));

	if (result) {
		return result;
	} else {
		return 0;
	}
}

/**
* Sets the input value for EIS library authentication.
* @param[in] eis_auth_input		random value between (-1,1) in Q30
*/
int dmp_icm20948_set_eis_auth_input(struct inv_icm20948 * s, long eis_auth_input)
{
	int result;
	unsigned char big8[4];

	result = inv_icm20948_write_mems(s, EIS_AUTH_INPUT, 4, inv_icm20948_convert_int32_to_big8(eis_auth_input, big8));

	return result;
}

/**
* Gets the output value from DMP for EIS library authentication.
* @param[out] &eis_auth_output
*/
int dmp_icm20948_get_eis_auth_output(struct inv_icm20948 * s, long *eis_auth_output)
{
	int result;
	unsigned char big8[4];

	result = inv_icm20948_read_mems(s, EIS_AUTH_OUTPUT, 4, big8);

	*eis_auth_output = inv_icm20948_convert_big8_to_int32(big8);

	return result;
}

/**
* BAC only works in 56 Hz. Set divider to make sure accel ODR into BAC is 56Hz.
* @param[in] bac_odr. the values are 56 , 112 , 225 450 or 900 Hz
*/
int dmp_icm20948_set_bac_rate(struct inv_icm20948 * s, short bac_odr)
{
	unsigned char reg[4]={0,0,0,0};
	int result;
	short odr;

	switch (bac_odr) {
	case DMP_ALGO_FREQ_56:
		odr = 0;
		break;
	case DMP_ALGO_FREQ_112:
		odr = 1;
		break;
	case DMP_ALGO_FREQ_225:
		odr = 3;
		break;
	case DMP_ALGO_FREQ_450:
		odr = 7;
		break;
	case DMP_ALGO_FREQ_900:
		odr = 15;
		break;
	default:
		return -1;
	}

	result = inv_icm20948_write_mems(s, BAC_RATE, 2, inv_icm20948_convert_int16_to_big8(odr,reg));
	if (result) {
		return result;
	} else {
		return 0;
	}
}

/**
* B2S only works in 56 Hz. Set divider to make sure accel ODR into B2S is 56Hz.
* @param[in] bac_odr. the values are 56 , 112 , 225 450 or 900 Hz
*/
int dmp_icm20948_set_b2s_rate(struct inv_icm20948 * s, short accel_odr)
{
	unsigned char reg[4]={0,0,0,0};
	int result;
	short odr;

	switch (accel_odr) {
	case DMP_ALGO_FREQ_56:
		odr = 0;
		break;
	case DMP_ALGO_FREQ_112:
		odr = 1;
		break;
	case DMP_ALGO_FREQ_225:
		odr = 3;
		break;
	case DMP_ALGO_FREQ_450:
		odr = 7;
		break;
	case DMP_ALGO_FREQ_900:
		odr = 15;
		break;
	default:
		return -1;
	}

	result = inv_icm20948_write_mems(s, B2S_RATE, 2, inv_icm20948_convert_int16_to_big8(odr,reg));
	if (result) {
		return result;
	} else {
		return 0;
	}
}


/**
* Sets B2S accel orientation matrix to DMP.
* @param[in] b2s_mtx. Unit: 1 = 2^30.
*/
int dmp_icm20948_set_B2S_matrix(struct inv_icm20948 * s, int *b2s_mtx)
{
	int result;
	unsigned char big8[4]={0};

	result  = inv_icm20948_write_mems(s, B2S_MTX_00, 4, inv_icm20948_convert_int32_to_big8(b2s_mtx[0], big8));
	result += inv_icm20948_write_mems(s, B2S_MTX_01, 4, inv_icm20948_convert_int32_to_big8(b2s_mtx[1], big8));
	result += inv_icm20948_write_mems(s, B2S_MTX_02, 4, inv_icm20948_convert_int32_to_big8(b2s_mtx[2], big8));
	result += inv_icm20948_write_mems(s, B2S_MTX_10, 4, inv_icm20948_convert_int32_to_big8(b2s_mtx[3], big8));
	result += inv_icm20948_write_mems(s, B2S_MTX_11, 4, inv_icm20948_convert_int32_to_big8(b2s_mtx[4], big8));
	result += inv_icm20948_write_mems(s, B2S_MTX_12, 4, inv_icm20948_convert_int32_to_big8(b2s_mtx[5], big8));
	result += inv_icm20948_write_mems(s, B2S_MTX_20, 4, inv_icm20948_convert_int32_to_big8(b2s_mtx[6], big8));
	result += inv_icm20948_write_mems(s, B2S_MTX_21, 4, inv_icm20948_convert_int32_to_big8(b2s_mtx[7], big8));
	result += inv_icm20948_write_mems(s, B2S_MTX_22, 4, inv_icm20948_convert_int32_to_big8(b2s_mtx[8], big8));

	if (result)
		return result;

	return 0;
}


/**
* PickUp only works in 56 Hz. Set divider to make sure accel ODR into PickUp is 56Hz.
* @param[in] bac_odr. the values are 56 , 112 , 225 450 or 900 Hz
*/
int dmp_icm20948_set_fp_rate(struct inv_icm20948 * s, short accel_odr)
{
	unsigned char reg[4]={0,0,0,0};
	int result;
	long odr;

	switch (accel_odr) {
	case DMP_ALGO_FREQ_56:
		odr = 0;
		break;
	case DMP_ALGO_FREQ_112:
		odr = 1;
		break;
	case DMP_ALGO_FREQ_225:
		odr = 3;
		break;
	case DMP_ALGO_FREQ_450:
		odr = 7;
		break;
	case DMP_ALGO_FREQ_900:
		odr = 15;
		break;
	default:
		return -1;
	}

	result = inv_icm20948_write_mems(s, FP_RATE, 4, inv_icm20948_convert_int32_to_big8(odr,reg));
	if (result) {
		return result;
	} else {
		return 0;
	}
}

/**
* Clear BAC states when restarting BAC/SMD/Pedometer/Tilt.
* This avoids false triggering of BAC-related modules.
*/
int dmp_icm20948_reset_bac_states(struct inv_icm20948 * s)
{
	int result;
	unsigned char big8[4]={0,0,0,0};
	unsigned char big8_s[2] = {0,0};
	long reset = 0;
	short reset_s = 0;

	result = inv_icm20948_write_mems(s, BAC_STATE,             4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_STATE_PREV,       4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_ACT_ON,           4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_ACT_OFF,          4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_STILL_S_F,        4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_RUN_S_F,          4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_DRIVE_S_F,        4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_WALK_S_F,         4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_SMD_S_F,          4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_BIKE_S_F,         4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_E1_SHORT,         4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_E2_SHORT,         4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_E3_SHORT,         4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_VAR_RUN,          4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_DRIVE_CONFIDENCE, 4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_WALK_CONFIDENCE,  4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_SMD_CONFIDENCE,   4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_BIKE_CONFIDENCE,  4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_STILL_CONFIDENCE, 4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_RUN_CONFIDENCE,   4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_MODE_CNTR,        4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_STATE_T_PREV,     4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_ACT_T_ON,         4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_ACT_T_OFF,        4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_STATE_WRDBS_PREV, 4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_ACT_WRDBS_ON,     4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_ACT_WRDBS_OFF,    4, inv_icm20948_convert_int32_to_big8(reset, big8));
	result += inv_icm20948_write_mems(s, BAC_ACT_ON_OFF,       2, inv_icm20948_convert_int16_to_big8(reset_s, big8_s));
	result += inv_icm20948_write_mems(s, PREV_BAC_ACT_ON_OFF,  2, inv_icm20948_convert_int16_to_big8(reset_s, big8_s));
	result += inv_icm20948_write_mems(s, BAC_CNTR,             2, inv_icm20948_convert_int16_to_big8(reset_s, big8_s));

	if (result)
		return result;

	return 0;
}

/**
* Set BAC ped y ration
* @param[in] ped_y_ratio: value will influence pedometer result
*/
int dmp_icm20948_set_ped_y_ratio(struct inv_icm20948 * s, long ped_y_ratio)
{
	int result;
	unsigned char big8[4]={0, 0, 0, 0};

	result = inv_icm20948_write_mems(s, PED_Y_RATIO, 4, inv_icm20948_convert_int32_to_big8(ped_y_ratio, big8));

	return result;
}

uint8_t * inv_dc_int32_to_little8(int32_t x, uint8_t * little8)
{
	little8[3] = (uint8_t)((x >> 24) & 0xff);
	little8[2] = (uint8_t)((x >> 16) & 0xff);
	little8[1] = (uint8_t)((x >> 8) & 0xff);
	little8[0] = (uint8_t)(x & 0xff);

	return little8;
}

uint8_t * inv_dc_int16_to_little8(int16_t x, uint8_t * little8)
{
	little8[0] = (uint8_t)(x & 0xff);
	little8[1] = (uint8_t)((x >> 8) & 0xff);

	return little8;
}

uint8_t * inv_dc_int32_to_big8(int32_t x, uint8_t * big8)
{
	big8[0] = (uint8_t)((x >> 24) & 0xff);
	big8[1] = (uint8_t)((x >> 16) & 0xff);
	big8[2] = (uint8_t)((x >> 8) & 0xff);
	big8[3] = (uint8_t)(x & 0xff);

	return big8;
}

uint8_t * inv_dc_int16_to_big8(int16_t x, uint8_t * big8)
{
	big8[0] = (uint8_t)((x >> 8) & 0xff);
	big8[1] = (uint8_t)(x & 0xff);

	return big8;
}

int32_t inv_dc_little8_to_int32(const uint8_t * little8)
{
	int32_t x = 0;

	x |= ((int32_t)little8[3] << 24);
	x |= ((int32_t)little8[2] << 16);
	x |= ((int32_t)little8[1] << 8);
	x |= ((int32_t)little8[0]);

	return x;
}

int16_t inv_dc_big16_to_int16(uint8_t * data)
{
	int16_t result;

	result  = (*data << 8);
	data++;
	result |= *data;

	return result;
}

int16_t inv_dc_le_to_int16(const uint8_t * little8)
{
	uint16_t x = 0;

	x |= ((uint16_t)little8[0]);
	x |= ((uint16_t)little8[1] << 8);

	return (int16_t)x;
}

void inv_dc_sfix32_to_float(const int32_t * in, uint32_t len, uint8_t qx, float * out)
{
	uint8_t i;

	for(i = 0; i < len; ++i) {
		out[i] = (float)in[i] / (1 << qx);
	}
}

void inv_dc_float_to_sfix32(const float * in, uint32_t len, uint8_t qx, int32_t * out)
{
	uint8_t i;

	for(i = 0; i < len; ++i) {
		out[i] = (int32_t)((in[i] * (1 << qx)) + ((in[i] >= 0) - 0.5f));
	}
}



// Determine the fastest ODR for all gravity-based sensors
#define AUGMENTED_SENSOR_GET_6QUAT_MIN_ODR(s, newOdr) \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_GRAVITY)) \
		newOdr = MIN(s->sGravityOdrMs,newOdr); \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_GAME_ROTATION_VECTOR)) \
		newOdr = MIN(s->sGrvOdrMs,newOdr);  \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_LINEAR_ACCELERATION)) \
		newOdr = MIN(s->sLinAccOdrMs,newOdr);
#define AUGMENTED_SENSOR_GET_6QUATWU_MIN_ODR(s, newOdr) \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_WAKEUP_GRAVITY)) \
		newOdr = MIN(s->sGravityWuOdrMs,newOdr); \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR)) \
		newOdr = MIN(s->sGrvWuOdrMs,newOdr);  \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION)) \
		newOdr = MIN(s->sLinAccWuOdrMs,newOdr);

// Determine the fastest ODR for all rotation vector-based sensors
#define AUGMENTED_SENSOR_GET_9QUAT_MIN_ODR(s, newOdr) \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_ORIENTATION)) \
		newOdr = MIN(s->sOriOdrMs,newOdr); \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_ROTATION_VECTOR)) \
		newOdr = MIN(s->sRvOdrMs,newOdr);
#define AUGMENTED_SENSOR_GET_9QUATWU_MIN_ODR(s, newOdr) \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_WAKEUP_ORIENTATION)) \
		newOdr = MIN(s->sOriWuOdrMs,newOdr); \
	if	(inv_icm20948_ctrl_androidSensor_enabled	(s, ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR)) \
		newOdr = MIN(s->sRvWuOdrMs,newOdr);

int inv_icm20948_augmented_init(struct inv_icm20948 * s)
{
	// ODR expected for gravity-based sensors
	s->sGravityOdrMs = 0xFFFF;
	s->sGrvOdrMs = 0xFFFF;
	s->sLinAccOdrMs = 0xFFFF;
	s->sGravityWuOdrMs = 0xFFFF;
	s->sGrvWuOdrMs = 0xFFFF;
	s->sLinAccWuOdrMs = 0xFFFF;
	// ODR expected for rotation vector-based sensors
	s->sRvOdrMs = 0xFFFF;
	s->sOriOdrMs = 0xFFFF;
	s->sRvWuOdrMs = 0xFFFF;
	s->sOriWuOdrMs = 0xFFFF;
	
	return 0;
}

int inv_icm20948_augmented_sensors_get_gravity(struct inv_icm20948 * s, long gravity[3], const long quat6axis_3e[3])
{
	long quat6axis_4e[4];
	long quat6axis_4e_body_to_world[4];

	if(!gravity) return -1;
	if(!quat6axis_3e) return -1;

	// compute w element
	inv_icm20948_convert_compute_scalar_part_fxp(quat6axis_3e, quat6axis_4e);
	// apply mounting matrix
	inv_icm20948_q_mult_q_qi(quat6axis_4e, s->s_quat_chip_to_body, quat6axis_4e_body_to_world);

	gravity[0] = ( 2 * inv_icm20948_convert_mult_qfix_fxp(quat6axis_4e_body_to_world[1], quat6axis_4e_body_to_world[3], 30) - 
	               2 * inv_icm20948_convert_mult_qfix_fxp(quat6axis_4e_body_to_world[0], quat6axis_4e_body_to_world[2], 30) ) >> (30 - 16);
	gravity[1] = ( 2 * inv_icm20948_convert_mult_qfix_fxp(quat6axis_4e_body_to_world[2], quat6axis_4e_body_to_world[3], 30) + 
	               2 * inv_icm20948_convert_mult_qfix_fxp(quat6axis_4e_body_to_world[0], quat6axis_4e_body_to_world[1], 30) ) >> (30 - 16);
	gravity[2] = ( (1 << 30) - 2 * inv_icm20948_convert_mult_qfix_fxp(quat6axis_4e_body_to_world[1], quat6axis_4e_body_to_world[1], 30) - 
	                2 * inv_icm20948_convert_mult_qfix_fxp(quat6axis_4e_body_to_world[2], quat6axis_4e_body_to_world[2], 30) ) >> (30 - 16);

	return MPU_SUCCESS;
}

int inv_icm20948_augmented_sensors_get_linearacceleration(long linacc[3], const long gravity[3], const long accel[3])
{
    if(!linacc) return -1;
    if(!gravity) return -1;
    if(!accel) return -1;
    
    linacc[0] = accel[0] - gravity[0];
    linacc[1] = accel[1] - gravity[1];
    linacc[2] = accel[2] - gravity[2];
                    
    return MPU_SUCCESS;
}


int inv_icm20948_augmented_sensors_get_orientation(long orientation[3], const long quat9axis_3e[4])
{
    long lQuat9axis4e[4];
	long lMatrixQ30[9];       
	long lMatrixQ30Square; 
	long lRad2degQ16 = 0x394BB8; // (float)(180.0 / 3.14159265358979) in Q16
    
    if(!orientation) return -1;
    if(!quat9axis_3e) return -1;
    
    // compute w element
	inv_icm20948_convert_compute_scalar_part_fxp(quat9axis_3e, lQuat9axis4e);
    
	// quaternion to a rotation matrix, q30 to q30
	inv_icm20948_convert_quat_to_col_major_matrix_fxp((const long *)lQuat9axis4e, (long *)lMatrixQ30);

	// compute orientation in q16
	// orientationFlt[0] = atan2f(-matrixFlt[1][0], matrixFlt[0][0]) * rad2deg;
	orientation[0] = inv_icm20948_math_atan2_q15_fxp(-lMatrixQ30[3] >> 15, lMatrixQ30[0] >> 15) << 1;
	orientation[0] = inv_icm20948_convert_mult_qfix_fxp(orientation[0], lRad2degQ16, 16);

	// orientationFlt[1] = atan2f(-matrixFlt[2][1], matrixFlt[2][2]) * rad2deg;
	orientation[1] = inv_icm20948_math_atan2_q15_fxp(-lMatrixQ30[7] >> 15, lMatrixQ30[8] >> 15) << 1;
	orientation[1] = inv_icm20948_convert_mult_qfix_fxp(orientation[1], lRad2degQ16, 16);

	// orientationFlt[2] = asinf ( matrixFlt[2][0]) * rad2deg;
	// asin(x) = atan (x/sqrt(1-x�))
	// atan2(y,x) = atan(y/x)
	// asin(x) = atan2(x, sqrt(1-x�))
	lMatrixQ30Square = inv_icm20948_convert_mult_qfix_fxp(lMatrixQ30[6], lMatrixQ30[6], 30); // x�
	lMatrixQ30Square = (1UL << 30) - lMatrixQ30Square; // 1-x�
	lMatrixQ30Square = inv_icm20948_convert_fast_sqrt_fxp(lMatrixQ30Square); // sqrt(1-x�)
	orientation[2] = inv_icm20948_math_atan2_q15_fxp(lMatrixQ30[6] >> 15,  lMatrixQ30Square >> 15) << 1; // atan2(x, sqrt(1-x�))
	orientation[2] = inv_icm20948_convert_mult_qfix_fxp(orientation[2], lRad2degQ16, 16); // * rad2deg

	if (orientation[0] < 0)
		orientation[0] += 360UL << 16;

    return MPU_SUCCESS;
}

unsigned short inv_icm20948_augmented_sensors_set_odr(struct inv_icm20948 * s, unsigned char androidSensor, unsigned short delayInMs)
{
	switch(androidSensor)
	{
		case ANDROID_SENSOR_GRAVITY:
			s->sGravityOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_6QUAT_MIN_ODR(s, delayInMs);
			break;
        case ANDROID_SENSOR_GAME_ROTATION_VECTOR:
			s->sGrvOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_6QUAT_MIN_ODR(s, delayInMs);
			break;
        case ANDROID_SENSOR_LINEAR_ACCELERATION:
			s->sLinAccOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_6QUAT_MIN_ODR(s, delayInMs);
			break;
        case ANDROID_SENSOR_ORIENTATION:
			s->sOriOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_9QUAT_MIN_ODR(s, delayInMs);
			break;
        case ANDROID_SENSOR_ROTATION_VECTOR:
			s->sRvOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_9QUAT_MIN_ODR(s, delayInMs);
			break;
		case ANDROID_SENSOR_WAKEUP_GRAVITY:
			s->sGravityWuOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_6QUATWU_MIN_ODR(s, delayInMs);
			break;
        case ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR:
			s->sGrvWuOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_6QUATWU_MIN_ODR(s, delayInMs);
			break;
        case ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION:
			s->sLinAccWuOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_6QUATWU_MIN_ODR(s, delayInMs);
			break;
        case ANDROID_SENSOR_WAKEUP_ORIENTATION:
			s->sOriWuOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_9QUATWU_MIN_ODR(s, delayInMs);
			break;
        case ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR:
			s->sRvWuOdrMs = delayInMs;
			AUGMENTED_SENSOR_GET_9QUATWU_MIN_ODR(s, delayInMs);
			break;
		default :
			break;
	}

	return delayInMs;
}

void inv_icm20948_augmented_sensors_update_odr(struct inv_icm20948 * s, unsigned char androidSensor, unsigned short * updatedDelayPtr)
{
	unsigned short lDelayInMs = 0xFFFF; // max value of uint16_t, so that we can get min value of all enabled sensors
	switch(androidSensor)
	{
		case ANDROID_SENSOR_GRAVITY:
        case ANDROID_SENSOR_GAME_ROTATION_VECTOR:
        case ANDROID_SENSOR_LINEAR_ACCELERATION:
			AUGMENTED_SENSOR_GET_6QUAT_MIN_ODR(s, lDelayInMs);
			*updatedDelayPtr = lDelayInMs;
			break;
		case ANDROID_SENSOR_WAKEUP_GRAVITY:
        case ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR:
        case ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION:
			AUGMENTED_SENSOR_GET_6QUATWU_MIN_ODR(s, lDelayInMs);
			*updatedDelayPtr = lDelayInMs;
			break;
		case ANDROID_SENSOR_ORIENTATION:
        case ANDROID_SENSOR_ROTATION_VECTOR:
			AUGMENTED_SENSOR_GET_9QUAT_MIN_ODR(s, lDelayInMs);
			*updatedDelayPtr = lDelayInMs;
			break;
		case ANDROID_SENSOR_WAKEUP_ORIENTATION:
        case ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR:
			AUGMENTED_SENSOR_GET_9QUATWU_MIN_ODR(s, lDelayInMs);
			*updatedDelayPtr = lDelayInMs;
			break;
		default :
			break;
	}
}



/* AKM definitions */
#define REG_AKM_ID               0x00
#define REG_AKM_INFO             0x01
#define REG_AKM_STATUS           0x02
#define REG_AKM_MEASURE_DATA     0x03
#define REG_AKM_MODE             0x0A
#define REG_AKM_ST_CTRL          0x0C
#define REG_AKM_SENSITIVITY      0x10
#define REG_AKM8963_CNTL1        0x0A

#if (MEMS_CHIP == HW_ICM20648)
/* AK09911 register definition */
#define REG_AK09911_DMP_READ    0x3
#define REG_AK09911_STATUS1     0x10
#define REG_AK09911_CNTL2       0x31
#define REG_AK09911_SENSITIVITY 0x60
#define REG_AK09911_MEASURE_DATA     0x11

/* AK09912 register definition */
#define REG_AK09912_DMP_READ    0x3
#define REG_AK09912_STATUS1     0x10
#define REG_AK09912_CNTL1       0x30
#define REG_AK09912_CNTL2       0x31
#define REG_AK09912_SENSITIVITY 0x60
#define REG_AK09912_MEASURE_DATA     0x11
#endif

/* AK09916 register definition */
#define REG_AK09916_DMP_READ    0x3
#define REG_AK09916_STATUS1     0x10
#define REG_AK09916_STATUS2     0x18
#define REG_AK09916_CNTL2       0x31
#define REG_AK09916_CNTL3       0x32
#define REG_AK09916_MEASURE_DATA     0x11
#define REG_AK09916_TEST        0x33

//-- REG WIA
#define DATA_AKM_ID              0x48
//-- REG CNTL2
#define DATA_AKM_MODE_PD	 0x00
#define DATA_AKM_MODE_SM	 0x01
#define DATA_AKM_MODE_ST	 0x08
#define DATA_AK09911_MODE_ST	 0x10
#define DATA_AK09912_MODE_ST	 0x10
#define DATA_AK09916_MODE_ST	 0x10
#define DATA_AKM_MODE_FR	 0x0F
#define DATA_AK09911_MODE_FR     0x1F
#define DATA_AK09912_MODE_FR     0x1F
// AK09916 doesn't support Fuse ROM access
#define DATA_AKM_SELF_TEST       0x40
//-- REG Status 1
#define DATA_AKM_DRDY            0x01
#define DATA_AKM9916_DOR         0x01
#define DATA_AKM8963_BIT         0x10

#if (MEMS_CHIP == HW_ICM20648)
/* 0.3 uT * (1 << 30) */
#define DATA_AKM8975_SCALE       322122547
/* 0.6 uT * (1 << 30) */
#define DATA_AKM8972_SCALE       644245094
/* 0.6 uT * (1 << 30) */
#define DATA_AKM8963_SCALE0      644245094
/* 0.6 uT * (1 << 30) */
#define DATA_AK09911_SCALE       644245094
/* 0.15 uT * (1 << 30) */
#define DATA_AK09912_SCALE       161061273
#endif
/* 0.15 uT * (1 << 30) */
#define DATA_AKM8963_SCALE1      161061273
/* 0.15 uT * (1 << 30) */
#define DATA_AK09916_SCALE       161061273

#define DATA_AKM8963_SCALE_SHIFT      4
#define DATA_AKM_MIN_READ_TIME            (9 * NSEC_PER_MSEC)

/* AK09912C NSF */
/* 0:disable, 1:Low, 2:Middle, 3:High */
#define DATA_AK9912_NSF  1
#define DATA_AK9912_NSF_SHIFT 5

#define DEF_ST_COMPASS_WAIT_MIN     (10 * 1000)
#define DEF_ST_COMPASS_WAIT_MAX     (15 * 1000)
#define DEF_ST_COMPASS_TRY_TIMES    10
#define DEF_ST_COMPASS_8963_SHIFT   2
#define DEF_ST_COMPASS_9916_SHIFT   2
const int X  =                      0;
const int Y  =                      1;
const int Z  =                      2;

/* milliseconds between each access */
#define AKM_RATE_SCALE       10

#define DATA_AKM_99_BYTES_DMP   10
#define DATA_AKM_89_BYTES_DMP   9

#if (MEMS_CHIP == HW_ICM20648)
const short AKM8975_ST_Lower[3] = {-100, -100, -1000};
const short AKM8975_ST_Upper[3] = {100, 100, -300};

const short AKM8972_ST_Lower[3] = {-50, -50, -500};
const short AKM8972_ST_Upper[3] = {50, 50, -100};

const short AKM8963_ST_Lower[3] = {-200, -200, -3200};
const short AKM8963_ST_Upper[3] = {200, 200, -800};

const short AK09911_ST_Lower[3] = {-30, -30, -400};
const short AK09911_ST_Upper[3] = {30, 30, -50};

const short AK09912_ST_Lower[3] = {-200, -200, -1600};
const short AK09912_ST_Upper[3] = {200, 200, -400};
#endif

const short AK09916_ST_Lower[3] = {-200, -200, -1000};
const short AK09916_ST_Upper[3] = {200, 200, -200};

void inv_icm20948_register_aux_compass(struct inv_icm20948 * s,
		enum inv_icm20948_compass_id compass_id, uint8_t compass_i2c_addr)
{
	switch(compass_id) {
	case INV_ICM20948_COMPASS_ID_AK09911:
		s->secondary_state.compass_slave_id = HW_AK09911;
		s->secondary_state.compass_chip_addr = compass_i2c_addr;
		s->secondary_state.compass_state = INV_ICM20948_COMPASS_INITED;
		/* initialise mounting matrix of compass to identity akm9911 */
		s->mounting_matrix_secondary_compass[0] = -1 ;
		s->mounting_matrix_secondary_compass[4] = -1;
		s->mounting_matrix_secondary_compass[8] = 1;
		break;
	case INV_ICM20948_COMPASS_ID_AK09912:
		s->secondary_state.compass_slave_id = HW_AK09912;
		s->secondary_state.compass_chip_addr = compass_i2c_addr;
		s->secondary_state.compass_state = INV_ICM20948_COMPASS_INITED;
		/* initialise mounting matrix of compass to identity akm9912 */
		s->mounting_matrix_secondary_compass[0] = 1 ;
		s->mounting_matrix_secondary_compass[4] = 1;
		s->mounting_matrix_secondary_compass[8] = 1;
		break;
	case INV_ICM20948_COMPASS_ID_AK08963:
		s->secondary_state.compass_slave_id = HW_AK8963;
		s->secondary_state.compass_chip_addr = compass_i2c_addr;
		s->secondary_state.compass_state = INV_ICM20948_COMPASS_INITED;
		/* initialise mounting matrix of compass to identity akm8963 */
		s->mounting_matrix_secondary_compass[0] = 1;
		s->mounting_matrix_secondary_compass[4] = 1;
		s->mounting_matrix_secondary_compass[8] = 1;
		break;
	case INV_ICM20948_COMPASS_ID_AK09916:
		s->secondary_state.compass_slave_id = HW_AK09916;
		s->secondary_state.compass_chip_addr = compass_i2c_addr;
		s->secondary_state.compass_state = INV_ICM20948_COMPASS_INITED;
		/* initialise mounting matrix of compass to identity akm9916 */
		s->mounting_matrix_secondary_compass[0] = 1 ;
		s->mounting_matrix_secondary_compass[4] = -1;
		s->mounting_matrix_secondary_compass[8] = -1;
		break;
	default:
		s->secondary_state.compass_slave_id  = 0;
		s->secondary_state.compass_chip_addr = 0;
		s->secondary_state.compass_state = INV_ICM20948_COMPASS_RESET;
	}
}

/*
 *  inv_icm20948_setup_compass_akm() - Configure akm series compass.
 */
int inv_icm20948_setup_compass_akm(struct inv_icm20948 * s)
{
	int result;
	unsigned char data[4];
#if (MEMS_CHIP != HW_ICM20948)
	uint8_t sens, cmd;
#endif
	//reset variable to initial values
	memset(s->secondary_state.final_matrix, 0, sizeof(s->secondary_state.final_matrix));
	memset(s->secondary_state.compass_sens, 0, sizeof(s->secondary_state.compass_sens));
	s->secondary_state.scale = 0;
	s->secondary_state.dmp_on = 1;
	s->secondary_state.secondary_resume_compass_state = 0;

	/* Read WHOAMI through I2C SLV for compass */
	result = inv_icm20948_execute_read_secondary(s, COMPASS_I2C_SLV_READ, s->secondary_state.compass_chip_addr, REG_AKM_ID, 1, data);
	if (result) {
        // inv_log("Read secondary error: Compass.\r\n");
		return result;
    }
	if (data[0] != DATA_AKM_ID) {
        // inv_log("Compass not found!!\r\n");
		return -1;
    }
    // inv_log("Compass found.\r\n");

	/* setup upper and lower limit of self-test */
#if (MEMS_CHIP == HW_ICM20948)
	s->secondary_state.st_upper = AK09916_ST_Upper;
	s->secondary_state.st_lower = AK09916_ST_Lower;
#else
	if (HW_AK8975 == s->secondary_state.compass_slave_id) {
		s->secondary_state.st_upper = AKM8975_ST_Upper;
		s->secondary_state.st_lower = AKM8975_ST_Lower;
	} else if (HW_AK8972 == s->secondary_state.compass_slave_id) {
		s->secondary_state.st_upper = AKM8972_ST_Upper;
		s->secondary_state.st_lower = AKM8972_ST_Lower;
	} else if (HW_AK8963 == s->secondary_state.compass_slave_id) {
		s->secondary_state.st_upper = AKM8963_ST_Upper;
		s->secondary_state.st_lower = AKM8963_ST_Lower;
	} else if (HW_AK09911 == s->secondary_state.compass_slave_id) {
		s->secondary_state.st_upper = AK09911_ST_Upper;
		s->secondary_state.st_lower = AK09911_ST_Lower;
	} else if (HW_AK09912 == s->secondary_state.compass_slave_id) {
		s->secondary_state.st_upper = AK09912_ST_Upper;
		s->secondary_state.st_lower = AK09912_ST_Lower;
	} else if (HW_AK09916 == s->secondary_state.compass_slave_id) {
		s->secondary_state.st_upper = AK09916_ST_Upper;
		s->secondary_state.st_lower = AK09916_ST_Lower;
	} else {
		return -1;
	}
#endif


#if (MEMS_CHIP == HW_ICM20948)
	/* Read conf and configure compass through I2C SLV for compass and subsequent channel */
	s->secondary_state.mode_reg_addr = REG_AK09916_CNTL2;
	// no sensitivity adjustment value
	s->secondary_state.compass_sens[0] = 128;
	s->secondary_state.compass_sens[1] = 128;
	s->secondary_state.compass_sens[2] = 128;
#else
	/* Read conf and configure compass through I2C SLV for compass and subsequent channel */
	if (HW_AK09916 == s->secondary_state.compass_slave_id) {
		s->secondary_state.mode_reg_addr = REG_AK09916_CNTL2;
		// no sensitivity adjustment value
		s->secondary_state.compass_sens[0] = 128;
		s->secondary_state.compass_sens[1] = 128;
		s->secondary_state.compass_sens[2] = 128;
	}
	else {
		// Fuse ROM access not possible for ak9916
		/* set AKM to Fuse ROM access mode */
		if (HW_AK09911 == s->secondary_state.compass_slave_id) {
			s->secondary_state.mode_reg_addr = REG_AK09911_CNTL2;
			sens = REG_AK09911_SENSITIVITY;
			cmd = DATA_AK09911_MODE_FR;
		} else if (HW_AK09912 == s->secondary_state.compass_slave_id) {
			s->secondary_state.mode_reg_addr = REG_AK09912_CNTL2;
			sens = REG_AK09912_SENSITIVITY;
			cmd = DATA_AK09912_MODE_FR;
		} else {
			s->secondary_state.mode_reg_addr = REG_AKM_MODE;
			sens = REG_AKM_SENSITIVITY;
			cmd = DATA_AKM_MODE_FR;
		}

		result = inv_icm20948_read_secondary(s, COMPASS_I2C_SLV_READ, s->secondary_state.compass_chip_addr, sens, THREE_AXES);
		if (result)
			return result;
		// activate FUSE_ROM mode to CNTL2
		result = inv_icm20948_execute_write_secondary(s, COMPASS_I2C_SLV_WRITE, s->secondary_state.compass_chip_addr,
				s->secondary_state.mode_reg_addr, cmd);

		if (result)
			return result;
		// read sensitivity
		result = inv_icm20948_read_mems_reg(s, REG_EXT_SLV_SENS_DATA_00, THREE_AXES, s->secondary_state.compass_sens);
		if (result)
			return result;
	}
	//aply noise suppression filter (only available for 9912)
	if (HW_AK09912 == s->secondary_state.compass_slave_id) {
		result = inv_icm20948_execute_write_secondary(s, COMPASS_I2C_SLV_WRITE, s->secondary_state.compass_chip_addr, REG_AK09912_CNTL1,
                                     DATA_AK9912_NSF << DATA_AK9912_NSF_SHIFT);
		if (result)
			return result;
	}
#endif
	/* Set compass in power down through I2C SLV for compass */
	result = inv_icm20948_execute_write_secondary(s, COMPASS_I2C_SLV_WRITE, s->secondary_state.compass_chip_addr, s->secondary_state.mode_reg_addr, DATA_AKM_MODE_PD);
	if (result)
		return result;

	s->secondary_state.secondary_resume_compass_state = 1;
	s->secondary_state.compass_state = INV_ICM20948_COMPASS_SETUP;
	return inv_icm20948_suspend_akm(s);
}

int inv_icm20948_check_akm_self_test(struct inv_icm20948 * s)
{
	int result;
	unsigned char data[6], mode, addr;
	unsigned char counter;
	short x, y, z;
	unsigned char *sens;
	int shift;
	unsigned char slv_ctrl[2];
	unsigned char odr_cfg;
#if (MEMS_CHIP != HW_ICM20948)
	unsigned char cntl;
#endif
	addr = s->secondary_state.compass_chip_addr;
	sens = s->secondary_state.compass_sens;

	/* back up registers */
	/* SLV0_CTRL */
	result = inv_icm20948_read_mems_reg(s, REG_I2C_SLV0_CTRL, 1, &slv_ctrl[0]);
	if (result)
		return result;
	result = inv_icm20948_write_single_mems_reg(s, REG_I2C_SLV0_CTRL, 0);
	if (result)
		return result;
	/* SLV1_CTRL */
	result = inv_icm20948_read_mems_reg(s, REG_I2C_SLV1_CTRL, 1, &slv_ctrl[1]);
	if (result)
		return result;
	result = inv_icm20948_write_single_mems_reg(s, REG_I2C_SLV1_CTRL, 0);
	if (result)
		return result;
	/* I2C_MST ODR */
	result = inv_icm20948_read_mems_reg(s, REG_I2C_MST_ODR_CONFIG, 1, &odr_cfg);
	if (result)
		return result;
	result = inv_icm20948_write_single_mems_reg(s, REG_I2C_MST_ODR_CONFIG, 0);
	if (result)
		return result;

#if (MEMS_CHIP == HW_ICM20948)
	mode = REG_AK09916_CNTL2;
#else
	if (HW_AK09911 == s->secondary_state.compass_slave_id)
		mode = REG_AK09911_CNTL2;
	else if (HW_AK09912 == s->secondary_state.compass_slave_id)
		mode = REG_AK09912_CNTL2;
	else if (HW_AK09916 == s->secondary_state.compass_slave_id)
		mode = REG_AK09916_CNTL2;
	else
		mode = REG_AKM_MODE;
#endif
	/* set to power down mode */
	result = inv_icm20948_execute_write_secondary(s, 0, addr, mode, DATA_AKM_MODE_PD);
	if (result)
		goto AKM_fail;

	/* write 1 to ASTC register */
	if ((HW_AK09911 != s->secondary_state.compass_slave_id) &&
		(HW_AK09912 != s->secondary_state.compass_slave_id)) {
		result = inv_icm20948_execute_write_secondary(s, 0, addr, REG_AKM_ST_CTRL, DATA_AKM_SELF_TEST);
		if (result)
			goto AKM_fail;
	}
#if (MEMS_CHIP == HW_ICM20948)
	result = inv_icm20948_execute_write_secondary(s, 0, addr, mode, DATA_AK09916_MODE_ST);
#else
	/* set self test mode */
	if (HW_AK09911 == s->secondary_state.compass_slave_id)
		result = inv_icm20948_execute_write_secondary(s, 0, addr, mode, DATA_AK09911_MODE_ST);
	else if (HW_AK09912 == s->secondary_state.compass_slave_id)
		result = inv_icm20948_execute_write_secondary(s, 0, addr, mode, DATA_AK09912_MODE_ST);
	else if (HW_AK09916 == s->secondary_state.compass_slave_id)
		result = inv_icm20948_execute_write_secondary(s, 0, addr, mode, DATA_AK09916_MODE_ST);
	else
		result = inv_icm20948_execute_write_secondary(s, 0, addr, mode,	DATA_AKM_MODE_ST);
#endif
	if (result)
		goto AKM_fail;
	counter = DEF_ST_COMPASS_TRY_TIMES;
	while (counter > 0) {
//		usleep_range(DEF_ST_COMPASS_WAIT_MIN, DEF_ST_COMPASS_WAIT_MAX);
        inv_icm20948_sleep_us(15000);

#if (MEMS_CHIP == HW_ICM20948)
		result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AK09916_STATUS1, 1, data);
#else
		if (HW_AK09911 == s->secondary_state.compass_slave_id)
			result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AK09911_STATUS1, 1, data);
		else if (HW_AK09912 == s->secondary_state.compass_slave_id)
			result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AK09912_STATUS1, 1, data);
		else if (HW_AK09916 == s->secondary_state.compass_slave_id)
			result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AK09916_STATUS1, 1, data);
		else
			result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AKM_STATUS, 1, data);
#endif
		if (result)
			goto AKM_fail;
		if ((data[0] & DATA_AKM_DRDY) == 0)
			counter--;
		else
			counter = 0;
	}
	if ((data[0] & DATA_AKM_DRDY) == 0) {
		result = -1;
		goto AKM_fail;
	}
#if (MEMS_CHIP == HW_ICM20948)
	result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AK09916_MEASURE_DATA, BYTES_PER_SENSOR, data);
#else
	if (HW_AK09911 == s->secondary_state.compass_slave_id) {
		result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AK09911_MEASURE_DATA, BYTES_PER_SENSOR, data);
	} else if (HW_AK09912 == s->secondary_state.compass_slave_id) {
		result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AK09912_MEASURE_DATA, BYTES_PER_SENSOR, data);
	} else if (HW_AK09916 == s->secondary_state.compass_slave_id) {
		result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AK09916_MEASURE_DATA, BYTES_PER_SENSOR, data);
	} else {
		result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AKM_MEASURE_DATA, BYTES_PER_SENSOR, data);
	}
#endif
	if (result)
		goto AKM_fail;

    x = ((short)data[1])<<8|data[0];
    y = ((short)data[3])<<8|data[2];
    z = ((short)data[5])<<8|data[4];

	if (HW_AK09911 == s->secondary_state.compass_slave_id)
		shift = 7;
	else
		shift = 8;
	x = ((x * (sens[0] + 128)) >> shift);
	y = ((y * (sens[1] + 128)) >> shift);
	z = ((z * (sens[2] + 128)) >> shift);
#if (MEMS_CHIP == HW_ICM20648)
	if (HW_AK8963 == s->secondary_state.compass_slave_id) {
		result = inv_icm20948_execute_read_secondary(s, 0, addr, REG_AKM8963_CNTL1, 1, &cntl);
		if (result)
			goto AKM_fail;
		if (0 == (cntl & DATA_AKM8963_BIT)) {
			x <<= DEF_ST_COMPASS_8963_SHIFT;
			y <<= DEF_ST_COMPASS_8963_SHIFT;
			z <<= DEF_ST_COMPASS_8963_SHIFT;
		}
	}
#endif

	result = -1;
	if (x > s->secondary_state.st_upper[0] || x < s->secondary_state.st_lower[0])
		goto AKM_fail;
	if (y > s->secondary_state.st_upper[1] || y < s->secondary_state.st_lower[1])
		goto AKM_fail;
	if (z > s->secondary_state.st_upper[2] || z < s->secondary_state.st_lower[2])
		goto AKM_fail;
	result = 0;
AKM_fail:
	/*write 0 to ASTC register */
	if ((HW_AK09911 != s->secondary_state.compass_slave_id) &&
		(HW_AK09912 != s->secondary_state.compass_slave_id) &&
		(HW_AK09916 != s->secondary_state.compass_slave_id)) {
		result |= inv_icm20948_execute_write_secondary(s, 0, addr, REG_AKM_ST_CTRL, 0);
	}
	/*set to power down mode */
	result |= inv_icm20948_execute_write_secondary(s, 0, addr, mode, DATA_AKM_MODE_PD);

    return result;
}

/*
 *  inv_icm20948_write_akm_scale() - Configure the akm scale range.
 */
int inv_icm20948_write_akm_scale(struct inv_icm20948 * s, int data)
{
	char d, en;
	int result;

	if (HW_AK8963 != s->secondary_state.compass_slave_id)
		return 0;
	en = !!data;
	if (s->secondary_state.scale == en)
		return 0;
	d = (DATA_AKM_MODE_SM | (en << DATA_AKM8963_SCALE_SHIFT));

	result = inv_icm20948_write_single_mems_reg(s, REG_I2C_SLV1_DO, d);
	if (result)
		return result;

	s->secondary_state.scale = en;

	return 0;
}

/*
 *  inv_icm20948_read_akm_scale() - show AKM scale.
 */
int inv_icm20948_read_akm_scale(struct inv_icm20948 * s, int *scale)
{
#if (MEMS_CHIP == HW_ICM20948)
	(void)s;
	*scale = DATA_AK09916_SCALE;
#else
	if (HW_AK8975 == s->secondary_state.compass_slave_id)
		*scale = DATA_AKM8975_SCALE;
	else if (HW_AK8972 == s->secondary_state.compass_slave_id)
		*scale = DATA_AKM8972_SCALE;
	else if (HW_AK8963 == s->secondary_state.compass_slave_id)
		if (s->secondary_state.scale)
			*scale = DATA_AKM8963_SCALE1;
		else
			*scale = DATA_AKM8963_SCALE0;
	else if (HW_AK09911 == s->secondary_state.compass_slave_id)
		*scale = DATA_AK09911_SCALE;
	else if (HW_AK09912 == s->secondary_state.compass_slave_id)
		*scale = DATA_AK09912_SCALE;
	else if (HW_AK09916 == s->secondary_state.compass_slave_id)
		*scale = DATA_AK09916_SCALE;
	else
		return -1;
#endif
	return 0;
}

int inv_icm20948_suspend_akm(struct inv_icm20948 * s)
{
	int result;

	if (!s->secondary_state.secondary_resume_compass_state)
		return 0;

	/* slave 0 is disabled */
	result = inv_icm20948_secondary_stop_channel(s, COMPASS_I2C_SLV_READ);
	/* slave 1 is disabled */
	result |= inv_icm20948_secondary_stop_channel(s, COMPASS_I2C_SLV_WRITE);
	if (result)
		return result;

	// Switch off I2C Interface as compass is alone
	result |= inv_icm20948_secondary_disable_i2c(s);

	s->secondary_state.secondary_resume_compass_state = 0;

	return result;
}

int inv_icm20948_resume_akm(struct inv_icm20948 * s)
{
	int result;
	uint8_t reg_addr, bytes;
    unsigned char lDataToWrite;

	if (s->secondary_state.secondary_resume_compass_state)
		return 0;

	/* slave 0 is used to read data from compass */
	/*read mode */
#if (MEMS_CHIP == HW_ICM20948)
	if (s->secondary_state.dmp_on) {
		reg_addr = REG_AK09916_DMP_READ;
		bytes = DATA_AKM_99_BYTES_DMP;
	} else {
		reg_addr = REG_AK09916_STATUS1;
		bytes = DATA_AKM_99_BYTES_DMP - 1;
	}
#else
	/* AKM status register address is 1 */
	if (HW_AK09911 == s->secondary_state.compass_slave_id) {
		if (s->secondary_state.dmp_on) {
			reg_addr = REG_AK09911_DMP_READ;
			bytes = DATA_AKM_99_BYTES_DMP;
		} else {
			reg_addr = REG_AK09911_STATUS1;
			bytes = DATA_AKM_99_BYTES_DMP - 1;
		}
	} else if (HW_AK09912 == s->secondary_state.compass_slave_id) {
		if (s->secondary_state.dmp_on) {
			reg_addr = REG_AK09912_DMP_READ;
			bytes = DATA_AKM_99_BYTES_DMP;
		} else {
			reg_addr = REG_AK09912_STATUS1;
			bytes = DATA_AKM_99_BYTES_DMP - 1;
		}
	} else if (HW_AK09916 == s->secondary_state.compass_slave_id) {
		if (s->secondary_state.dmp_on) {
			reg_addr = REG_AK09916_DMP_READ;
			bytes = DATA_AKM_99_BYTES_DMP;
		} else {
			reg_addr = REG_AK09916_STATUS1;
			bytes = DATA_AKM_99_BYTES_DMP - 1;
		}
	} else {
		if (s->secondary_state.dmp_on) {
			reg_addr = REG_AKM_INFO;
			bytes = DATA_AKM_89_BYTES_DMP;
		} else {
			reg_addr = REG_AKM_STATUS;
			bytes = DATA_AKM_89_BYTES_DMP - 1;
		}
	}
#endif
	/* slave 0 is enabled, read 10 or 8 bytes from here depending on compass type, swap bytes to feed DMP */
	result = inv_icm20948_read_secondary(s, COMPASS_I2C_SLV_READ, s->secondary_state.compass_chip_addr, reg_addr, INV_MPU_BIT_GRP | INV_MPU_BIT_BYTE_SW | bytes);
	if (result)
		return result;
#if (MEMS_CHIP == HW_ICM20948)
	lDataToWrite = DATA_AKM_MODE_SM;
#else
	/* slave 1 is used to write one-shot accquisition configuration to compass */
	/* output data for slave 1 is fixed, single measure mode */
	s->secondary_state.scale = 1;
	if (HW_AK8975 == s->secondary_state.compass_slave_id) {
		lDataToWrite = DATA_AKM_MODE_SM;
	} else if (HW_AK8972 == s->secondary_state.compass_slave_id) {
		lDataToWrite = DATA_AKM_MODE_SM;
	} else if (HW_AK8963 == s->secondary_state.compass_slave_id) {
		lDataToWrite = DATA_AKM_MODE_SM |
			(s->secondary_state.scale << DATA_AKM8963_SCALE_SHIFT);
	}  else if (HW_AK09911 == s->secondary_state.compass_slave_id) {
		lDataToWrite = DATA_AKM_MODE_SM;
	}  else if (HW_AK09912 == s->secondary_state.compass_slave_id) {
		lDataToWrite = DATA_AKM_MODE_SM;
	}  else if (HW_AK09916 == s->secondary_state.compass_slave_id) {
		lDataToWrite = DATA_AKM_MODE_SM;
	} else {
		return -1;
	}
#endif
	result = inv_icm20948_write_secondary(s, COMPASS_I2C_SLV_WRITE, s->secondary_state.compass_chip_addr, s->secondary_state.mode_reg_addr, lDataToWrite);
	if (result)
		return result;

	result |= inv_icm20948_secondary_enable_i2c(s);

    s->secondary_state.secondary_resume_compass_state = 1;

	return result;
}

char inv_icm20948_compass_getstate(struct inv_icm20948 * s)
{
	return s->secondary_state.secondary_resume_compass_state;
}

int inv_icm20948_compass_isconnected(struct inv_icm20948 * s)
{
	if(s->secondary_state.compass_state == INV_ICM20948_COMPASS_SETUP) {
		return 1;
	} else {
		return 0;
	}
}

/**
*  @brief      Set up the soft-iron matrix for compass in DMP.
*  @param[in]  Accel/Gyro mounting matrix
*  @param[in]  Compass mounting matrix
*  @return     0 if successful.
*/

int inv_icm20948_compass_dmp_cal(struct inv_icm20948 * s, const signed char *m, const signed char *compass_m)
{
	int8_t trans[NINE_ELEM];
	int tmp_m[NINE_ELEM];
	int i, j, k;
	int sens[THREE_AXES];
	int scale;
	int shift;
    int current_compass_matrix[NINE_ELEM];

	for (i = 0; i < THREE_AXES; i++)
		for (j = 0; j < THREE_AXES; j++)
			trans[THREE_AXES * j + i] = m[THREE_AXES * i + j];

    switch (s->secondary_state.compass_slave_id)
    {
#if (MEMS_CHIP == HW_ICM20648)
        case HW_AK8972:
            scale = DATA_AKM8972_SCALE;
            shift = AK89XX_SHIFT;
            break;
        case HW_AK8975:
            scale = DATA_AKM8975_SCALE;
            shift = AK89XX_SHIFT;
            break;
        case HW_AK8963:
            scale = DATA_AKM8963_SCALE1;
            shift = AK89XX_SHIFT;
            break;
        case HW_AK09911:
            scale = DATA_AK09911_SCALE;
            shift = AK99XX_SHIFT;
            break;
        case HW_AK09912:
            scale = DATA_AK09912_SCALE;
            shift = AK89XX_SHIFT;
            break;
#else
        case HW_AK09916:
            scale = DATA_AK09916_SCALE;
            shift = AK89XX_SHIFT;
            break;
#endif
		default:
				scale = DATA_AKM8963_SCALE1;
				shift = AK89XX_SHIFT;
				break;
    }

	for (i = 0; i < THREE_AXES; i++) {
		sens[i] = s->secondary_state.compass_sens[i] + 128;
		sens[i] = inv_icm20948_convert_mult_q30_fxp(sens[i] << shift, scale);
	}
	for (i = 0; i < NINE_ELEM; i++) {
		current_compass_matrix[i] = compass_m[i] * sens[i % THREE_AXES];
		tmp_m[i] = 0;
	}

    for (i = 0; i < THREE_AXES; i++) {
		for (j = 0; j < THREE_AXES; j++) {
			s->secondary_state.final_matrix[i * THREE_AXES + j] = 0;
			for (k = 0; k < THREE_AXES; k++)
				s->secondary_state.final_matrix[i * THREE_AXES + j] +=
					inv_icm20948_convert_mult_q30_fxp(s->soft_iron_matrix[i * THREE_AXES + k],
                                 current_compass_matrix[j + k * THREE_AXES]);
		}
	}

    for (i = 0; i < THREE_AXES; i++)
		for (j = 0; j < THREE_AXES; j++)
			for (k = 0; k < THREE_AXES; k++)
				tmp_m[THREE_AXES * i + j] +=
					trans[THREE_AXES * i + k] *
						s->secondary_state.final_matrix[THREE_AXES * k + j];

    return dmp_icm20948_set_compass_matrix(s, tmp_m);
}

/**
*  @brief      Apply mounting matrix and scaling to raw compass data.
*  @param[in]  Raw compass data
*  @param[in]  Compensated compass data
*  @return     0 if successful.
*/

int inv_icm20948_apply_raw_compass_matrix(struct inv_icm20948 * s, short *raw_data, long *compensated_out)
{
	int i, j;
	long long tmp;

	for (i = 0; i < THREE_AXES; i++) {
		tmp = 0;
		for (j = 0; j < THREE_AXES; j++)
			tmp  +=
			(long long)s->secondary_state.final_matrix[i * THREE_AXES + j] * (((int)raw_data[j]) << 16);
		compensated_out[i] = (long)(tmp >> 30);
	}

	return 0;
}



void inv_icm20948_init_secondary(struct inv_icm20948 * s)
{
	s->secondary_state.slv_reg[0].addr = REG_I2C_SLV0_ADDR;
	s->secondary_state.slv_reg[0].reg  = REG_I2C_SLV0_REG;
	s->secondary_state.slv_reg[0].ctrl = REG_I2C_SLV0_CTRL;
	s->secondary_state.slv_reg[0].d0   = REG_I2C_SLV0_DO;
    
    s->secondary_state.slv_reg[1].addr = REG_I2C_SLV1_ADDR;
	s->secondary_state.slv_reg[1].reg  = REG_I2C_SLV1_REG;
	s->secondary_state.slv_reg[1].ctrl = REG_I2C_SLV1_CTRL;
	s->secondary_state.slv_reg[1].d0   = REG_I2C_SLV1_DO;
    
    s->secondary_state.slv_reg[2].addr = REG_I2C_SLV2_ADDR;
	s->secondary_state.slv_reg[2].reg  = REG_I2C_SLV2_REG;
	s->secondary_state.slv_reg[2].ctrl = REG_I2C_SLV2_CTRL;
	s->secondary_state.slv_reg[2].d0   = REG_I2C_SLV2_DO;
    
	s->secondary_state.slv_reg[3].addr = REG_I2C_SLV3_ADDR;
	s->secondary_state.slv_reg[3].reg  = REG_I2C_SLV3_REG;
	s->secondary_state.slv_reg[3].ctrl = REG_I2C_SLV3_CTRL;
	s->secondary_state.slv_reg[3].d0   = REG_I2C_SLV3_DO;
	
	/* Make sure that by default all channels are disabled 
	To not inherit from a previous configuration from a previous run*/
	inv_icm20948_secondary_stop_channel(s, 0);
	inv_icm20948_secondary_stop_channel(s, 1);
	inv_icm20948_secondary_stop_channel(s, 2);
	inv_icm20948_secondary_stop_channel(s, 3);
}

/* the following functions are used for configuring the secondary devices */

/*
* inv_configure_secondary_read(): set secondary registers for reading.
The chip must be set as bank 3 before calling.
* This is derived from inv_icm20948_read_secondary in linux...
* for now, uses a very simple data struct for the registers
* 
* index gives the mapping to the particular SLVx registers
* addr is the physical address of the device to be accessed
* reg is the device register we wish to access
* len is the number of bytes to be read
* 
*/
int inv_icm20948_read_secondary(struct inv_icm20948 * s, int index, unsigned char addr, unsigned char reg, char len)
{
	int result = 0;
    unsigned char data;

    data = INV_MPU_BIT_I2C_READ | addr;
	result |= inv_icm20948_write_mems_reg(s, s->secondary_state.slv_reg[index].addr, 1, &data);

    data = reg;
	result |= inv_icm20948_write_mems_reg(s, s->secondary_state.slv_reg[index].reg, 1, &data);
    
    data = INV_MPU_BIT_SLV_EN | len;
	result |= inv_icm20948_write_mems_reg(s, s->secondary_state.slv_reg[index].ctrl, 1, &data);
    
	return result;
}

int inv_icm20948_execute_read_secondary(struct inv_icm20948 * s, int index, unsigned char addr, int reg, int len, uint8_t *d)
{
	int result = 0;

	result |= inv_icm20948_read_secondary(s, index, addr, reg, len);
	
	result |= inv_icm20948_secondary_enable_i2c(s);
    
	inv_icm20948_sleep_us(SECONDARY_INIT_WAIT*1000);
    
	result |= inv_icm20948_secondary_disable_i2c(s);

    result |= inv_icm20948_read_mems_reg(s, REG_EXT_SLV_SENS_DATA_00, len, d); 

	result |= inv_icm20948_secondary_stop_channel(s, index);

	return result;
}

/*
* inv_icm20948_write_secondary(): set secondary registers for writing?.
The chip must be set as bank 3 before calling.
* This is derived from inv_icm20948_write_secondary in linux...
* for now, uses a very simple data struct for the registers
* 
* index gives the mapping to the particular SLVx registers
* addr is the physical address of the device to be accessed
* reg is the device register we wish to access
* len is the number of bytes to be read
* 
*/
int inv_icm20948_write_secondary(struct inv_icm20948 * s, int index, unsigned char addr, unsigned char reg, char v)
{
	int result = 0;
    unsigned char data;
    
    data = (unsigned char)addr;
	result |= inv_icm20948_write_mems_reg(s, s->secondary_state.slv_reg[index].addr, 1, &data);

    data = reg;
	result |= inv_icm20948_write_mems_reg(s, s->secondary_state.slv_reg[index].reg, 1, &data);

    data = v;
    result |= inv_icm20948_write_mems_reg(s, s->secondary_state.slv_reg[index].d0, 1, &data);
    
    data = INV_MPU_BIT_SLV_EN | 1;
	result |= inv_icm20948_write_mems_reg(s, s->secondary_state.slv_reg[index].ctrl, 1, &data);
    
    return result;
}

int inv_icm20948_execute_write_secondary(struct inv_icm20948 * s, int index, unsigned char addr, int reg, uint8_t v)
{
	int result = 0;

	result |= inv_icm20948_write_secondary(s, index, addr, reg, v);
	
	result |= inv_icm20948_secondary_enable_i2c(s);
    
	inv_icm20948_sleep_us(SECONDARY_INIT_WAIT*1000);
    
	result |= inv_icm20948_secondary_disable_i2c(s);

	result |= inv_icm20948_secondary_stop_channel(s, index);

	return result;
}

void inv_icm20948_secondary_saveI2cOdr(struct inv_icm20948 * s)
{
	inv_icm20948_read_mems_reg(s, REG_I2C_MST_ODR_CONFIG,1,&s->secondary_state.sSavedI2cOdr);
}

void inv_icm20948_secondary_restoreI2cOdr(struct inv_icm20948 * s)
{
	inv_icm20948_write_single_mems_reg(s, REG_I2C_MST_ODR_CONFIG,s->secondary_state.sSavedI2cOdr);
}

int inv_icm20948_secondary_stop_channel(struct inv_icm20948 * s, int index)
{
	return inv_icm20948_write_single_mems_reg(s, s->secondary_state.slv_reg[index].ctrl, 0);
}

int inv_icm20948_secondary_enable_i2c(struct inv_icm20948 * s)
{
	s->base_state.user_ctrl |= BIT_I2C_MST_EN;
	return inv_icm20948_write_single_mems_reg(s, REG_USER_CTRL, s->base_state.user_ctrl); 
}

int inv_icm20948_secondary_disable_i2c(struct inv_icm20948 * s)
{
	s->base_state.user_ctrl &= ~BIT_I2C_MST_EN;
	return inv_icm20948_write_single_mems_reg(s, REG_USER_CTRL, s->base_state.user_ctrl); 
}

int inv_icm20948_secondary_set_odr(struct inv_icm20948 * s, int divider, unsigned int* effectiveDivider)
{
	int mst_odr_config = 0;

    // find 2^x = divider to fit BASE_SAMPLE_RATE/2^REG_I2C_MST_ODR_CONFIG
    do
    {
		divider>>=1;
		mst_odr_config++;
    } while(divider>>1);
    
	if (mst_odr_config < MIN_MST_ODR_CONFIG)
		mst_odr_config = MIN_MST_ODR_CONFIG;

	*effectiveDivider = 1<<mst_odr_config;

	return	inv_icm20948_set_secondary_divider(s, (unsigned char)mst_odr_config);
}

// BAC ped y ration for wearable, the value will influence pedometer result
#define BAC_PED_Y_RATIO_WEARABLE 1073741824

unsigned long inv_icm20948_ctrl_androidSensor_enabled(struct inv_icm20948 * s, unsigned char androidSensor)
{
	return s->inv_androidSensorsOn_mask[(androidSensor>>5)] & (1L << (androidSensor&0x1F));
}

typedef	struct {
	enum ANDROID_SENSORS AndroidSensor;
	enum INV_SENSORS     InvSensor;
}	MinDelayGenElementT;

#define MinDelayGen(s, list) MinDelayGenActual(s, list, sizeof(list) / sizeof (MinDelayGenElementT))

unsigned short MinDelayGenActual(struct inv_icm20948 *s, const MinDelayGenElementT *element, unsigned long elementQuan)
{
	unsigned short minDelay = (unsigned short) -1;

	while(elementQuan--) {
		if (inv_icm20948_ctrl_androidSensor_enabled(s, element->AndroidSensor)) {
			unsigned short odrDelay = s->inv_dmp_odr_delays[element->InvSensor];

			if (minDelay > odrDelay)
					minDelay = odrDelay;
		}
		element++;
	} // end while elements to process

	return	minDelay;
}

int DividerRateSet(struct inv_icm20948 *s, unsigned short minDelay, unsigned short hwSampleRateDivider, enum INV_SENSORS InvSensor)
{
	int result = 0;
	
	if (minDelay != 0xFFFF) {
		unsigned short dmpOdrDivider = (minDelay * 1125L) / (hwSampleRateDivider * 1000L); // a divider from (1125Hz/hw_smplrt_divider).

		s->inv_dmp_odr_dividers[InvSensor] = hwSampleRateDivider * dmpOdrDivider;
		result |= dmp_icm20948_set_sensor_rate(s, InvSensor, (dmpOdrDivider - 1));
	}
	
	return result;
}

unsigned short SampleRateDividerGet(unsigned short minDelay)
{
	unsigned short delay = MIN(INV_ODR_MIN_DELAY, minDelay); // because of GYRO_SMPLRT_DIV which relies on 8 bits, we can't have ODR value higher than 200ms
	return delay * 1125L / 1000L; // a divider from 1125Hz.
}



/** @brief Get minimum ODR to be applied to accel engine based on all accel-based enabled sensors.
* @return ODR in ms we expect to be applied to accel engine
*/
unsigned short getMinDlyAccel(struct inv_icm20948 *s)
{
	const MinDelayGenElementT MinDelayGenAccelList[] ={
		{ANDROID_SENSOR_ACCELEROMETER,                      INV_SENSOR_ACCEL                },
		{ANDROID_SENSOR_RAW_ACCELEROMETER,                  INV_SENSOR_ACCEL                },
		{ANDROID_SENSOR_WAKEUP_ACCELEROMETER,               INV_SENSOR_WAKEUP_ACCEL         },
		{ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR,        INV_SENSOR_GEOMAG               },
		{ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR, INV_SENSOR_WAKEUP_GEOMAG        },
		{ANDROID_SENSOR_STEP_DETECTOR,                      INV_SENSOR_STEP_COUNTER         },
		{ANDROID_SENSOR_STEP_COUNTER,                       INV_SENSOR_STEP_COUNTER         },
		{ANDROID_SENSOR_WAKEUP_STEP_DETECTOR,               INV_SENSOR_WAKEUP_STEP_COUNTER  },
		{ANDROID_SENSOR_WAKEUP_STEP_COUNTER,                INV_SENSOR_WAKEUP_STEP_COUNTER  },
		{ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION,          INV_SENSOR_WAKEUP_STEP_COUNTER  },
		{ANDROID_SENSOR_WAKEUP_TILT_DETECTOR,               INV_SENSOR_WAKEUP_TILT_DETECTOR },
		{ANDROID_SENSOR_GRAVITY,                            INV_SENSOR_SIXQ_accel           },
		{ANDROID_SENSOR_GAME_ROTATION_VECTOR,               INV_SENSOR_SIXQ_accel           },
		{ANDROID_SENSOR_LINEAR_ACCELERATION,                INV_SENSOR_SIXQ_accel           },
		{ANDROID_SENSOR_WAKEUP_GRAVITY,                     INV_SENSOR_WAKEUP_SIXQ_accel    },
		{ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR,        INV_SENSOR_WAKEUP_SIXQ_accel    },
		{ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION,         INV_SENSOR_WAKEUP_SIXQ_accel    },
		{ANDROID_SENSOR_ORIENTATION,                        INV_SENSOR_NINEQ_accel          },
		{ANDROID_SENSOR_ROTATION_VECTOR,                    INV_SENSOR_NINEQ_accel          },
		{ANDROID_SENSOR_WAKEUP_ORIENTATION,                 INV_SENSOR_WAKEUP_NINEQ_accel   },
		{ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR,             INV_SENSOR_WAKEUP_NINEQ_accel   }
	};

	unsigned short lMinOdr = MinDelayGen(s, MinDelayGenAccelList);

	if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_ACCELEROMETER))
		if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_RAW_ACCELEROMETER))
			s->inv_dmp_odr_delays[INV_SENSOR_ACCEL] = MIN(s->odr_acc_ms,s->odr_racc_ms);
		else
			s->inv_dmp_odr_delays[INV_SENSOR_ACCEL] = s->odr_acc_ms;
	else
		if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_RAW_ACCELEROMETER))
			s->inv_dmp_odr_delays[INV_SENSOR_ACCEL] = s->odr_racc_ms;

	if (s->bac_status != 0)
		lMinOdr = MIN(lMinOdr, s->inv_dmp_odr_delays[INV_SENSOR_ACTIVITY_CLASSIFIER]);
	if (s->flip_pickup_status != 0)
		lMinOdr = MIN(lMinOdr, s->inv_dmp_odr_delays[INV_SENSOR_FLIP_PICKUP]);
	if (s->b2s_status != 0)
		lMinOdr = MIN(lMinOdr, s->inv_dmp_odr_delays[INV_SENSOR_BRING_TO_SEE]);
	
	/** To have correct algorithm performance and quick convergence of GMRV, it is advised to set accelerometer to 225Hz.
	    In case power consumption is to be improved at the expense of performance, this setup should be commented out */
	if (   inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR) 
		|| inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR) )
		lMinOdr = MIN(lMinOdr, 5);

	/** To have correct algorithm performance and quick convergence of RV, it is advised to set accelerometer to 225Hz.
	    In case power consumption is to be improved at the expense of performance, this setup should be commented out */
	if (   inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR) 
		|| inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_ROTATION_VECTOR) )
		lMinOdr = MIN(lMinOdr, 5);

	return lMinOdr;
}

/** @brief Get minimum ODR to be applied to gyro engine based on all gyro-based enabled sensors.
* @return ODR in ms we expect to be applied to gyro engine
*/
unsigned short getMinDlyGyro(struct inv_icm20948 *s)
{
	const MinDelayGenElementT MinDelayGenGyroList[] = {
		{ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED,        INV_SENSOR_GYRO              },
		{ANDROID_SENSOR_WAKEUP_GYROSCOPE_UNCALIBRATED, INV_SENSOR_WAKEUP_GYRO       },
		{ANDROID_SENSOR_GYROSCOPE,                     INV_SENSOR_CALIB_GYRO        },
		{ANDROID_SENSOR_RAW_GYROSCOPE,                 INV_SENSOR_GYRO              },
		{ANDROID_SENSOR_WAKEUP_GYROSCOPE,              INV_SENSOR_WAKEUP_CALIB_GYRO },
		{ANDROID_SENSOR_GRAVITY,                       INV_SENSOR_SIXQ              },
		{ANDROID_SENSOR_GAME_ROTATION_VECTOR,          INV_SENSOR_SIXQ              },
		{ANDROID_SENSOR_LINEAR_ACCELERATION,           INV_SENSOR_SIXQ              },
		{ANDROID_SENSOR_WAKEUP_GRAVITY,                INV_SENSOR_WAKEUP_SIXQ       },
		{ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR,   INV_SENSOR_WAKEUP_SIXQ       },
		{ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION,    INV_SENSOR_WAKEUP_SIXQ       },
		{ANDROID_SENSOR_ORIENTATION,                   INV_SENSOR_NINEQ             },
		{ANDROID_SENSOR_ROTATION_VECTOR,               INV_SENSOR_NINEQ             },
		{ANDROID_SENSOR_WAKEUP_ORIENTATION,            INV_SENSOR_WAKEUP_NINEQ      },
		{ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR,        INV_SENSOR_WAKEUP_NINEQ      }
	};

	unsigned short lMinOdr = MinDelayGen(s, MinDelayGenGyroList);

	if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED))
		if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_RAW_GYROSCOPE))
			s->inv_dmp_odr_delays[INV_SENSOR_GYRO] = MIN(s->odr_gyr_ms,s->odr_rgyr_ms);
		else
			s->inv_dmp_odr_delays[INV_SENSOR_GYRO] = s->odr_gyr_ms;
	else
		if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_RAW_GYROSCOPE))
			s->inv_dmp_odr_delays[INV_SENSOR_GYRO] = s->odr_rgyr_ms;

	/** To have correct algorithm performance and quick convergence of RV, it is advised to set gyro to 225Hz.
	    In case power consumption is to be improved at the expense of performance, this setup should be commented out */
	if (   inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR) 
		|| inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_ROTATION_VECTOR) )
		lMinOdr	= MIN(lMinOdr, 5);

	return lMinOdr;
}

/** @brief Get minimum ODR to be applied to compass engine based on all compass-based enabled sensors.
* @return ODR in ms we expect to be applied to compass engine
*/
unsigned short getMinDlyCompass(struct inv_icm20948 *s)
{
	const MinDelayGenElementT MinDelayGenCpassList[] = {
		{ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED,        INV_SENSOR_COMPASS              },
		{ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD_UNCALIBRATED, INV_SENSOR_WAKEUP_COMPASS       },
		{ANDROID_SENSOR_GEOMAGNETIC_FIELD,                  INV_SENSOR_CALIB_COMPASS        },
		{ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD,              INV_SENSOR_WAKEUP_CALIB_COMPASS },
		{ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR,        INV_SENSOR_GEOMAG_cpass         },
		{ANDROID_SENSOR_ORIENTATION,                        INV_SENSOR_NINEQ_cpass          },
		{ANDROID_SENSOR_ROTATION_VECTOR,                    INV_SENSOR_NINEQ_cpass          },
		{ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR, INV_SENSOR_WAKEUP_GEOMAG_cpass  },
		{ANDROID_SENSOR_WAKEUP_ORIENTATION,                 INV_SENSOR_WAKEUP_NINEQ_cpass   },
		{ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR,             INV_SENSOR_WAKEUP_NINEQ_cpass   }
	};

	unsigned short lMinOdr = MinDelayGen(s, MinDelayGenCpassList);

	/** To have correct algorithm performance and quick convergence of GMRV, it is advised to set compass to 70Hz.
	    In case power consumption is to be improved at the expense of performance, this setup should be commented out */
	if (   inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR) 
		|| inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR) )
		lMinOdr= MIN(lMinOdr, 15);
	/** To have correct algorithm performance and quick convergence of RV, it is advised to set compass to 35Hz.
	    In case power consumption is to be improved at the expense of performance, this setup should be commented out */
	if (   inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR) 
		|| inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_ROTATION_VECTOR) )
		lMinOdr = MIN(lMinOdr, 28);

	return lMinOdr;
}

int inv_icm20948_base_control_init(struct inv_icm20948 * s)
{
	int result = 0;
	unsigned int i;

	memset(s->inv_dmp_odr_dividers, 0, sizeof(s->inv_dmp_odr_dividers));
	
	for(i = 0; i < (sizeof(s->inv_dmp_odr_delays)/sizeof(unsigned short)); i++) {
		if((i == INV_SENSOR_ACTIVITY_CLASSIFIER) ||
		   (i == INV_SENSOR_STEP_COUNTER) ||
		   (i == INV_SENSOR_WAKEUP_STEP_COUNTER) ||
		   (i == INV_SENSOR_WAKEUP_TILT_DETECTOR) ||
		   (i == INV_SENSOR_FLIP_PICKUP) )
			s->inv_dmp_odr_delays[i] = INV_ODR_DEFAULT_BAC;
		else if(i == INV_SENSOR_BRING_TO_SEE)
			s->inv_dmp_odr_delays[i] = INV_ODR_DEFAULT_B2S;
		else
			s->inv_dmp_odr_delays[i] = INV_ODR_MIN_DELAY;
	}
	for(i = 0; i < (sizeof(s->inv_androidSensorsOdr_boundaries)/sizeof(s->inv_androidSensorsOdr_boundaries[0])); i++) {
		if ((i == ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED) || (i == ANDROID_SENSOR_GEOMAGNETIC_FIELD) ||
		    (i == ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD_UNCALIBRATED) || (i == ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD)) {
			s->inv_androidSensorsOdr_boundaries[i][0] = INV_MIN_ODR_CPASS;
			s->inv_androidSensorsOdr_boundaries[i][1] = INV_MAX_ODR_CPASS;
		} else if ((i == ANDROID_SENSOR_GAME_ROTATION_VECTOR) || (i == ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR) ||
		           (i == ANDROID_SENSOR_GRAVITY) || (i == ANDROID_SENSOR_WAKEUP_GRAVITY) ||
		           (i == ANDROID_SENSOR_LINEAR_ACCELERATION) || (i == ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION) ||
		           (i == ANDROID_SENSOR_ROTATION_VECTOR) || (i == ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR) ||
		           (i == ANDROID_SENSOR_ORIENTATION) || (i == ANDROID_SENSOR_WAKEUP_ORIENTATION)) {
			s->inv_androidSensorsOdr_boundaries[i][0] = INV_MIN_ODR_GRV;
			s->inv_androidSensorsOdr_boundaries[i][1] = INV_MAX_ODR_GRV;
		} else {
			s->inv_androidSensorsOdr_boundaries[i][0] = INV_MIN_ODR;
			s->inv_androidSensorsOdr_boundaries[i][1] = INV_MAX_ODR;
		}
	}
	s->lLastHwSmplrtDividerAcc = 0;
	s->lLastHwSmplrtDividerGyr = 0;
	s->sBatchMode              = 0;
	s->header2_count           = 0;
	s->mems_put_to_sleep       = 1;
	s->smd_status              = 0;
	s->ped_int_status          = 0;
	s->b2s_status              = 0;
	s->bac_request             = 0;
	s->odr_acc_ms = INV_ODR_MIN_DELAY;
	//s->odr_acc_wom_ms = INV_ODR_MIN_DELAY;
	s->odr_racc_ms = INV_ODR_MIN_DELAY;
	s->odr_gyr_ms = INV_ODR_MIN_DELAY;
	s->odr_rgyr_ms = INV_ODR_MIN_DELAY;

	return result;
}

int inv_set_hw_smplrt_dmp_odrs(struct inv_icm20948 * s)
{
	int result = 0;
	unsigned short minDly, minDly_accel, minDly_gyro;
	unsigned short minDly_cpass;
	unsigned short minDly_pressure;
	unsigned short hw_smplrt_divider = 0;
	
	const MinDelayGenElementT MinDelayGenPressureList[] = {
		{ANDROID_SENSOR_PRESSURE,                           INV_SENSOR_PRESSURE             },
		{ANDROID_SENSOR_WAKEUP_PRESSURE,                    INV_SENSOR_WAKEUP_PRESSURE      }
	};
	const MinDelayGenElementT MinDelayGenAccel2List[] = {
		{ANDROID_SENSOR_ACCELEROMETER,                      INV_SENSOR_ACCEL                },
		{ANDROID_SENSOR_WAKEUP_ACCELEROMETER,               INV_SENSOR_WAKEUP_ACCEL         },
		{ANDROID_SENSOR_RAW_ACCELEROMETER,                  INV_SENSOR_ACCEL                },
		{ANDROID_SENSOR_LINEAR_ACCELERATION,                INV_SENSOR_SIXQ_accel           },
		{ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION,         INV_SENSOR_WAKEUP_SIXQ_accel    }
	};
	const MinDelayGenElementT MinDelayGenAccel3List[] = {
		{ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR,        INV_SENSOR_GEOMAG               },
		{ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR, INV_SENSOR_WAKEUP_GEOMAG        }
	};
	const MinDelayGenElementT MinDelayGenAccel4List[] = {
		{ANDROID_SENSOR_STEP_DETECTOR,                      INV_SENSOR_STEP_COUNTER         },
		{ANDROID_SENSOR_STEP_COUNTER,                       INV_SENSOR_STEP_COUNTER         },
		{ANDROID_SENSOR_WAKEUP_STEP_DETECTOR,               INV_SENSOR_WAKEUP_STEP_COUNTER  },
		{ANDROID_SENSOR_WAKEUP_STEP_COUNTER,                INV_SENSOR_WAKEUP_STEP_COUNTER  },
		{ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION,          INV_SENSOR_WAKEUP_STEP_COUNTER  }
	};
	const MinDelayGenElementT MinDelayGenGyro2List[] = {
		{ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED,             INV_SENSOR_GYRO                 },
		{ANDROID_SENSOR_WAKEUP_GYROSCOPE_UNCALIBRATED,      INV_SENSOR_WAKEUP_GYRO          },
		{ANDROID_SENSOR_GYROSCOPE,                          INV_SENSOR_CALIB_GYRO           },
		{ANDROID_SENSOR_RAW_GYROSCOPE,                      INV_SENSOR_GYRO           },
		{ANDROID_SENSOR_WAKEUP_GYROSCOPE,                   INV_SENSOR_WAKEUP_CALIB_GYRO    }
	};
	const MinDelayGenElementT MinDelayGenGyro3List[] = {
		{ANDROID_SENSOR_GYROSCOPE,                          INV_SENSOR_CALIB_GYRO           },
		{ANDROID_SENSOR_WAKEUP_GYROSCOPE,                   INV_SENSOR_WAKEUP_CALIB_GYRO    }
	};
	const MinDelayGenElementT MinDelayGenGyro4List[] = {
		{ANDROID_SENSOR_GRAVITY,                            INV_SENSOR_SIXQ                 },
		{ANDROID_SENSOR_GAME_ROTATION_VECTOR,               INV_SENSOR_SIXQ                 },
		{ANDROID_SENSOR_LINEAR_ACCELERATION,                INV_SENSOR_SIXQ                 },
		{ANDROID_SENSOR_WAKEUP_GRAVITY,                     INV_SENSOR_WAKEUP_SIXQ          },
		{ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR,        INV_SENSOR_WAKEUP_SIXQ          },
		{ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION,         INV_SENSOR_WAKEUP_SIXQ          }
	};
	const MinDelayGenElementT MinDelayGenGyro5List[] = {
		{ANDROID_SENSOR_ORIENTATION,                        INV_SENSOR_NINEQ                },
		{ANDROID_SENSOR_ROTATION_VECTOR,                    INV_SENSOR_NINEQ                },
		{ANDROID_SENSOR_WAKEUP_ORIENTATION,                 INV_SENSOR_WAKEUP_NINEQ         },
		{ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR,             INV_SENSOR_WAKEUP_NINEQ         }
	};
	const MinDelayGenElementT MinDelayGenCpass2List[] = {
		{ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED,        INV_SENSOR_COMPASS              },
		{ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD_UNCALIBRATED,	INV_SENSOR_WAKEUP_COMPASS       }
	};
	const MinDelayGenElementT MinDelayGenCpass3List[] = {
		{ANDROID_SENSOR_GEOMAGNETIC_FIELD,                  INV_SENSOR_CALIB_COMPASS        },
		{ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD,              INV_SENSOR_WAKEUP_CALIB_COMPASS }
	};
	const MinDelayGenElementT MinDelayGenPressure2List[] = {
		{ANDROID_SENSOR_PRESSURE,                           INV_SENSOR_PRESSURE             },
		{ANDROID_SENSOR_WAKEUP_PRESSURE,                    INV_SENSOR_WAKEUP_PRESSURE      }
	};
	
	// Engine ACCEL Based
	minDly_accel = getMinDlyAccel(s);

	// Engine Gyro Based
	minDly_gyro  = getMinDlyGyro(s);

	// Engine Cpass Based	
	minDly_cpass = getMinDlyCompass(s);

	// Engine Pressure Based	
	minDly_pressure	=	MinDelayGen	(s, MinDelayGenPressureList);

	// get min delay of all enabled sensors of all sensor engine groups
	minDly = MIN(minDly_gyro, minDly_accel);
	minDly = MIN(minDly, minDly_cpass);
	minDly = MIN(minDly, minDly_pressure);
	
	// switch between low power and low noise at 500Hz boundary
	if (minDly != 0xFFFF) {
		// above 500Hz boundary, force LN mode
		if (minDly==1) {
			if (s->base_state.chip_lp_ln_mode == CHIP_LOW_POWER_ICM20948) {
				s->go_back_lp_when_odr_low = 1;
				inv_icm20948_enter_low_noise_mode(s);
			}
		} else { // below 500 Hz boundary, go back to originally requested mode
			if (s->go_back_lp_when_odr_low) {
				s->go_back_lp_when_odr_low = 0;
				inv_icm20948_enter_duty_cycle_mode(s);
			}	
		}
	} else // all sensors are turned OFF, force originally requested mode
	{
		if (s->go_back_lp_when_odr_low) {
			s->go_back_lp_when_odr_low = 0;
			inv_icm20948_enter_duty_cycle_mode(s);
		}
	}
	
	if (minDly_accel != 0xFFFF)    minDly_accel = minDly;
	if (minDly_gyro  != 0xFFFF)    minDly_gyro  = minDly;
	if (minDly_cpass != 0xFFFF)    minDly_cpass = minDly;
	if (minDly_pressure != 0xFFFF) minDly_pressure = minDly;

	if (s->bac_request != 0) {
		unsigned short lBACMinDly = MIN(INV_ODR_DEFAULT_BAC, minDly_accel);
		// estimate closest decimator value to have 56Hz multiple and apply it
		lBACMinDly = 1000/(get_multiple_56_rate(lBACMinDly));
		dmp_icm20948_set_bac_rate(s, get_multiple_56_rate(lBACMinDly));
		minDly_accel = lBACMinDly;
		hw_smplrt_divider = SampleRateDividerGet(minDly_accel);
		result |= DividerRateSet(s, lBACMinDly, hw_smplrt_divider, INV_SENSOR_ACTIVITY_CLASSIFIER);
	}
	if (s->b2s_status != 0) {
		unsigned short lB2SMinDly = MIN(INV_ODR_DEFAULT_B2S, minDly_accel);
		lB2SMinDly = 1000/(get_multiple_56_rate(lB2SMinDly));
		dmp_icm20948_set_b2s_rate(s, get_multiple_56_rate(lB2SMinDly));
		minDly_accel = lB2SMinDly;
		hw_smplrt_divider = SampleRateDividerGet(minDly_accel);
		result |= DividerRateSet(s, lB2SMinDly, hw_smplrt_divider, INV_SENSOR_BRING_TO_SEE);
	}

	// set odrs for each enabled sensors

	// Engine ACCEL Based
	if (minDly_accel != 0xFFFF)	{ // 0xFFFF -- none accel based sensor enable
		hw_smplrt_divider = SampleRateDividerGet(minDly_accel);

		if (hw_smplrt_divider != s->lLastHwSmplrtDividerAcc) {
			
			result |= inv_icm20948_ctrl_set_accel_quaternion_gain(s, hw_smplrt_divider);
			result |= inv_icm20948_ctrl_set_accel_cal_params(s, hw_smplrt_divider);
			result |= inv_icm20948_set_accel_divider(s, hw_smplrt_divider - 1);
			s->lLastHwSmplrtDividerAcc = hw_smplrt_divider;
		}

		result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenAccel2List), hw_smplrt_divider, INV_SENSOR_ACCEL);
		result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenAccel3List), hw_smplrt_divider, INV_SENSOR_GEOMAG);
		result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenAccel4List), hw_smplrt_divider, INV_SENSOR_STEP_COUNTER);
		
	}

	// Engine Gyro Based
	if (minDly_gyro != 0xFFFF) { // 0xFFFF -- none gyro based sensor enable
		hw_smplrt_divider = SampleRateDividerGet(minDly_gyro);

		if (hw_smplrt_divider != s->lLastHwSmplrtDividerGyr) {
			result |= inv_icm20948_set_gyro_divider(s, (unsigned char)(hw_smplrt_divider - 1));
			s->lLastHwSmplrtDividerGyr = hw_smplrt_divider;
		}

		result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenGyro2List), hw_smplrt_divider, INV_SENSOR_GYRO);
		result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenGyro3List), hw_smplrt_divider, INV_SENSOR_CALIB_GYRO);
		result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenGyro4List), hw_smplrt_divider, INV_SENSOR_SIXQ);
		result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenGyro5List), hw_smplrt_divider, INV_SENSOR_NINEQ);
	}

	// Engine Cpass and Pressure Based	
	if ((minDly_cpass != 0xFFFF) || (minDly_pressure != 0xFFFF)) {
		unsigned int lI2cEffectiveDivider = 0;

		// if compass or pressure are alone, compute 1st stage divider, otherwise it will be taken from accel or gyro
		if ( (minDly_accel == 0xFFFF) && (minDly_gyro == 0xFFFF) )
			hw_smplrt_divider = SampleRateDividerGet(minDly);

		// Apply compass or pressure ODR to I2C and get effective ODR
		// so that 2nd level of divider can take into account real frequency we can expect
		// to determine its divider value
		result |= inv_icm20948_secondary_set_odr(s, hw_smplrt_divider, &lI2cEffectiveDivider);

		// if compass or pressure are alone, recompute 1st stage divider based on configured divider for I2C
		// otherwise divider is taken from accel or gyro, so there is no need to recompute effective divider value
		// based on the divider we just applied
		if ( (minDly_accel == 0xFFFF) && (minDly_gyro == 0xFFFF) )
			hw_smplrt_divider = lI2cEffectiveDivider;

		if (minDly_cpass != 0xFFFF) {
			result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenCpass2List), hw_smplrt_divider, INV_SENSOR_COMPASS);
			result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenCpass3List), hw_smplrt_divider, INV_SENSOR_CALIB_COMPASS);
		}

		if (minDly_pressure != 0xFFFF)
			result |= DividerRateSet(s, MinDelayGen(s, MinDelayGenPressure2List), hw_smplrt_divider, INV_SENSOR_PRESSURE);
	}

	return result;
}

short get_multiple_56_rate(unsigned short delayInMs)
{
	short lfreq = 0;

	// > 1KHz
	if( delayInMs < 2 ){
	lfreq = DMP_ALGO_FREQ_900;
	}
	// 225Hz - 500Hz
	else if(( delayInMs >= 2 ) && ( delayInMs < 4 )){
	lfreq = DMP_ALGO_FREQ_450;
	}
	// 112Hz - 225Hz
	else if(( delayInMs >= 4 ) && ( delayInMs < 8 )){
	lfreq = DMP_ALGO_FREQ_225;
	}
	// 56Hz - 112Hz
	else if(( delayInMs >= 8 ) && ( delayInMs < 17 )){
	lfreq = DMP_ALGO_FREQ_112;
	}
	// < 56Hz
	else if(delayInMs >= 17){
	lfreq = DMP_ALGO_FREQ_56;
	}
	
	return lfreq;
}

int inv_icm20948_set_odr(struct inv_icm20948 * s, unsigned char androidSensor, unsigned short delayInMs)
{
	int result;

	if(sensor_needs_compass(androidSensor))
		if(!inv_icm20948_get_compass_availability(s))
			return -1;
	
	//check if sensor is bac algo dependant
	if(sensor_needs_bac_algo(androidSensor)) {
		// set odr for sensors using BAC (1/56)
		delayInMs = INV_ODR_DEFAULT_BAC;
	}
	
	inv_icm20948_prevent_lpen_control(s);

	// check that requested ODR is within the allowed limits
	if (delayInMs < s->inv_androidSensorsOdr_boundaries[androidSensor][0]) delayInMs = s->inv_androidSensorsOdr_boundaries[androidSensor][0];
	if (delayInMs > s->inv_androidSensorsOdr_boundaries[androidSensor][1]) delayInMs = s->inv_androidSensorsOdr_boundaries[androidSensor][1];
	switch (androidSensor) {
		case ANDROID_SENSOR_ACCELEROMETER:
			if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_RAW_ACCELEROMETER))
				s->inv_dmp_odr_delays[INV_SENSOR_ACCEL] = MIN(delayInMs,s->odr_racc_ms);
			else
				s->inv_dmp_odr_delays[INV_SENSOR_ACCEL] = delayInMs;
			s->odr_acc_ms = delayInMs;
			break;
		case ANDROID_SENSOR_RAW_ACCELEROMETER:
			if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_ACCELEROMETER))
				s->inv_dmp_odr_delays[INV_SENSOR_ACCEL] = MIN(delayInMs,s->odr_acc_ms);
			else
				s->inv_dmp_odr_delays[INV_SENSOR_ACCEL] = delayInMs;
			s->odr_racc_ms = delayInMs;
			break;

		case ANDROID_SENSOR_STEP_DETECTOR:
		case ANDROID_SENSOR_STEP_COUNTER:
			s->inv_dmp_odr_delays[INV_SENSOR_STEP_COUNTER] = delayInMs;
			break;

		case ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR:
			s->inv_dmp_odr_delays[INV_SENSOR_GEOMAG] = delayInMs;
			s->inv_dmp_odr_delays[INV_SENSOR_GEOMAG_cpass] = delayInMs;
			break;

		case ANDROID_SENSOR_ACTIVITY_CLASSIFICATON:
			s->inv_dmp_odr_delays[INV_SENSOR_ACTIVITY_CLASSIFIER] = delayInMs;
			break;

		case ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED:
			if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_RAW_GYROSCOPE))
				s->inv_dmp_odr_delays[INV_SENSOR_GYRO] = MIN(delayInMs,s->odr_rgyr_ms);
			else
				s->inv_dmp_odr_delays[INV_SENSOR_GYRO] = delayInMs;
			s->odr_gyr_ms = delayInMs;
			break;
		case ANDROID_SENSOR_RAW_GYROSCOPE:
			if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED))
				s->inv_dmp_odr_delays[INV_SENSOR_GYRO] = MIN(delayInMs,s->odr_gyr_ms);
			else
				s->inv_dmp_odr_delays[INV_SENSOR_GYRO] = delayInMs;
			s->odr_rgyr_ms = delayInMs;
			break;
		case ANDROID_SENSOR_GYROSCOPE:
			s->inv_dmp_odr_delays[INV_SENSOR_CALIB_GYRO] = delayInMs;
			break;

		case ANDROID_SENSOR_GRAVITY:
		case ANDROID_SENSOR_GAME_ROTATION_VECTOR:
		case ANDROID_SENSOR_LINEAR_ACCELERATION:
			// if augmented sensors are handled by this driver,
			// then the fastest 6quat-based sensor which is enabled
			// should be applied to all 6quat-based sensors
			delayInMs = inv_icm20948_augmented_sensors_set_odr(s, androidSensor, delayInMs);
			s->inv_dmp_odr_delays[INV_SENSOR_SIXQ] = delayInMs;
			s->inv_dmp_odr_delays[INV_SENSOR_SIXQ_accel] = delayInMs;
			break;

		case ANDROID_SENSOR_ORIENTATION:
		case ANDROID_SENSOR_ROTATION_VECTOR:
			// if augmented sensors are handled by this driver,
			// then the fastest 9quat-based sensor which is enabled
			// should be applied to all 9quat-based sensors
			delayInMs = inv_icm20948_augmented_sensors_set_odr(s, androidSensor, delayInMs);
			s->inv_dmp_odr_delays[INV_SENSOR_NINEQ] = delayInMs;
			s->inv_dmp_odr_delays[INV_SENSOR_NINEQ_accel] = delayInMs;
			s->inv_dmp_odr_delays[INV_SENSOR_NINEQ_cpass] = delayInMs;
			break;

		case ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED:
			s->inv_dmp_odr_delays[INV_SENSOR_COMPASS] = delayInMs;
			break;

		case ANDROID_SENSOR_GEOMAGNETIC_FIELD:
			s->inv_dmp_odr_delays[INV_SENSOR_CALIB_COMPASS] = delayInMs;
			break;

		case ANDROID_SENSOR_LIGHT:
		case ANDROID_SENSOR_PROXIMITY:
			s->inv_dmp_odr_delays[INV_SENSOR_ALS] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_ACCELEROMETER:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_ACCEL] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_STEP_DETECTOR:
		case ANDROID_SENSOR_WAKEUP_STEP_COUNTER:
		case ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_STEP_COUNTER] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_GEOMAG] = delayInMs;
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_GEOMAG_cpass] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_TILT_DETECTOR:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_TILT_DETECTOR] = delayInMs;
			break;

		case ANDROID_SENSOR_B2S:
			s->inv_dmp_odr_delays[INV_SENSOR_BRING_TO_SEE] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_GYROSCOPE_UNCALIBRATED:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_GYRO] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_GYROSCOPE:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_CALIB_GYRO] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_GRAVITY:
		case ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR:
		case ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION:
			// if augmented sensors are handled by this driver,
			// then the fastest 6quat-based sensor which is enabled
			// should be applied to all 6quat-based sensors
			delayInMs = inv_icm20948_augmented_sensors_set_odr(s, androidSensor, delayInMs);
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_SIXQ] = delayInMs;
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_SIXQ_accel] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_ORIENTATION:
		case ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR:
			// if augmented sensors are handled by this driver,
			// then the fastest 9quat-based sensor which is enabled
			// should be applied to all 9quat-based sensors
			delayInMs = inv_icm20948_augmented_sensors_set_odr(s, androidSensor, delayInMs);
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_NINEQ] = delayInMs;
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_NINEQ_accel] = delayInMs;
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_NINEQ_cpass] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD_UNCALIBRATED:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_COMPASS] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_CALIB_COMPASS] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_LIGHT:
		case ANDROID_SENSOR_WAKEUP_PROXIMITY:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_ALS] = delayInMs;
			break;

		case ANDROID_SENSOR_PRESSURE:
			s->inv_dmp_odr_delays[INV_SENSOR_PRESSURE] = delayInMs;
			break;

		case ANDROID_SENSOR_WAKEUP_PRESSURE:
			s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_PRESSURE] = delayInMs;
			break;

		case ANDROID_SENSOR_FLIP_PICKUP:
			s->inv_dmp_odr_delays[INV_SENSOR_FLIP_PICKUP] = delayInMs;
			break;

		// not support yet
		case ANDROID_SENSOR_META_DATA:
		case ANDROID_SENSOR_TEMPERATURE:
		case ANDROID_SENSOR_AMBIENT_TEMPERATURE:
		case ANDROID_SENSOR_HUMIDITY:
		case ANDROID_SENSOR_HEART_RATE:
		case ANDROID_SENSOR_SCREEN_ROTATION:
		case ANDROID_SENSOR_WAKEUP_AMBIENT_TEMPERATURE:
		case ANDROID_SENSOR_WAKEUP_RELATIVE_HUMIDITY:
		case ANDROID_SENSOR_WAKEUP_HEART_RATE:
			break;

		default:
			break;
	}

	result = inv_set_hw_smplrt_dmp_odrs(s);
	result |= inv_icm20948_set_gyro_sf(s, inv_icm20948_get_gyro_divider(s), inv_icm20948_get_gyro_fullscale(s));

	// debug get odr
	// result should be SAME as you entered in Ms in the Rolldice console
	// i.e. If you use: O a 63 [ Press capital O then 'a' then 63 then ENTER]
	// You should get the nearest number to 63 here if you debug  the 'test_odr'  

	//inv_icm20948_ctrl_get_odr( androidSensor, &test_odr );

	inv_icm20948_allow_lpen_control(s);
	return result;
}

/*
   inv_icm20948_ctrl_get_odr(s)
   Function to Query DMP3 DataRate (ODR)
   
   *odr = inv_icm20948_get_odr_in_units( );

    The result in odr_units saved in *odr param
*/
int inv_icm20948_ctrl_get_odr(struct inv_icm20948 * s, unsigned char SensorId, uint32_t *odr, enum INV_ODR_TYPE odr_units)
{
	int result=0;

	if(!odr) // sanity
		return -1;

	*odr = 0;

	/*
	You can obtain the odr in Milliseconds, Micro Seconds or Ticks.
	Use the enum values: ODR_IN_Ms, ODR_IN_Us or ODR_IN_Ticks,
	when calling inv_icm20948_get_odr_in_units().
	*/

	switch (SensorId) {
		case ANDROID_SENSOR_ACCELEROMETER:
		case ANDROID_SENSOR_RAW_ACCELEROMETER:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_ACCEL] , odr_units );
			break;

		case ANDROID_SENSOR_STEP_DETECTOR:
		case ANDROID_SENSOR_STEP_COUNTER:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_STEP_COUNTER] , odr_units );
			break;

		case ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_GEOMAG] , odr_units );            
			break;

		case ANDROID_SENSOR_ACTIVITY_CLASSIFICATON:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_ACTIVITY_CLASSIFIER] , odr_units );
			break;

		case ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED:
		case ANDROID_SENSOR_RAW_GYROSCOPE:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_GYRO] , odr_units );
			break;

		case ANDROID_SENSOR_GYROSCOPE:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_CALIB_GYRO] , odr_units );
			break;

		case ANDROID_SENSOR_GAME_ROTATION_VECTOR:
		case ANDROID_SENSOR_GRAVITY:
		case ANDROID_SENSOR_LINEAR_ACCELERATION:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_SIXQ] , odr_units );
			break;

		case ANDROID_SENSOR_ORIENTATION:
		case ANDROID_SENSOR_ROTATION_VECTOR:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_NINEQ] , odr_units );
			break;

		case ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_COMPASS] , odr_units );
			break;

		case ANDROID_SENSOR_GEOMAGNETIC_FIELD:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_CALIB_COMPASS] , odr_units );
			break;

		case ANDROID_SENSOR_LIGHT:
		case ANDROID_SENSOR_PROXIMITY:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_ALS] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_ACCELEROMETER:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_ACCEL] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_STEP_DETECTOR:
		case ANDROID_SENSOR_WAKEUP_STEP_COUNTER:
		case ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_STEP_COUNTER] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_GEOMAG] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_TILT_DETECTOR:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_TILT_DETECTOR] , odr_units );
			break;

		case ANDROID_SENSOR_B2S:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_BRING_TO_SEE] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_GYROSCOPE_UNCALIBRATED:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_GYRO] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_GYROSCOPE:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_CALIB_GYRO] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_SIXQ] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_GRAVITY:
		case ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_SIXQ_accel] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_ORIENTATION:
		case ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_NINEQ] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD_UNCALIBRATED:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_COMPASS] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_CALIB_COMPASS] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_LIGHT:
		case ANDROID_SENSOR_WAKEUP_PROXIMITY:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_ALS] , odr_units );
			break;

		case ANDROID_SENSOR_PRESSURE:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_PRESSURE] , odr_units );
			break;

		case ANDROID_SENSOR_WAKEUP_PRESSURE:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_WAKEUP_PRESSURE] , odr_units );
			break;

		case ANDROID_SENSOR_FLIP_PICKUP:
			*odr = inv_icm20948_get_odr_in_units(s, s->inv_dmp_odr_dividers[INV_SENSOR_FLIP_PICKUP] , odr_units ); 
			break;

		// not support yet
		case ANDROID_SENSOR_META_DATA:
		case ANDROID_SENSOR_TEMPERATURE:
		case ANDROID_SENSOR_AMBIENT_TEMPERATURE:
		case ANDROID_SENSOR_HUMIDITY:
		case ANDROID_SENSOR_HEART_RATE:
		case ANDROID_SENSOR_SCREEN_ROTATION:
		case ANDROID_SENSOR_WAKEUP_AMBIENT_TEMPERATURE:
		case ANDROID_SENSOR_WAKEUP_RELATIVE_HUMIDITY:
		case ANDROID_SENSOR_WAKEUP_HEART_RATE:
			*odr=0;
			break;

		default:
			*odr=0;
	}

	return result;
}

void inv_reGenerate_sensorControl(struct inv_icm20948 * s, const short *sen_num_2_ctrl, unsigned short *sensor_control, uint8_t header2_count)
{
	short delta;
	int i, cntr;
	unsigned long tmp_androidSensorsOn_mask;

	//check if only header2 still remaining
	if(header2_count)
		*sensor_control = HEADER2_SET;
	else
		*sensor_control = 0;
	for (i = 0; i < 2; i++) {
		cntr = 32 * i;
		tmp_androidSensorsOn_mask = s->inv_androidSensorsOn_mask[i];
		while (tmp_androidSensorsOn_mask) {
			if (tmp_androidSensorsOn_mask & 1) {
				delta = sen_num_2_ctrl[cntr];
				if (delta != -1) *sensor_control |= delta;
			}
			tmp_androidSensorsOn_mask >>= 1;
			cntr++;
		}
	}
}

/** Computes the sensor control register that needs to be sent to the DMP
* @param[in] androidSensor A sensor number, the numbers correspond to sensors.h definition in Android
* @param[in] enable non-zero to turn sensor on, 0 to turn sensor off
* @param[in] sen_num_2_ctrl Table matching android sensor number to bits in DMP control register
* @param[in,out] sensor_control Sensor control register to write to DMP to enable/disable sensors
*/
void inv_convert_androidSensor_to_control(struct inv_icm20948 * s, unsigned char androidSensor, unsigned char enable, const short *sen_num_2_ctrl, unsigned short *sensor_control)
{
	short delta = 0;

	if (androidSensor == ANDROID_SENSOR_ACTIVITY_CLASSIFICATON || androidSensor == ANDROID_SENSOR_FLIP_PICKUP || 
			androidSensor == ANDROID_SENSOR_WAKEUP_TILT_DETECTOR || androidSensor == ANDROID_SENSOR_B2S) {
		if (enable) {
			*sensor_control |= HEADER2_SET;
			//we increment counter
			s->header2_count ++;
		}
		else {
			s->header2_count --;
			// control has to be regenerated when removing sensors because of overlap
			inv_reGenerate_sensorControl(s, sen_num_2_ctrl, sensor_control, s->header2_count);
		}
	}

	if (androidSensor >= ANDROID_SENSOR_NUM_MAX)
		return; // Sensor not supported

	delta = sen_num_2_ctrl[androidSensor];
	if (delta == -1)
		return; // This sensor not supported

	if (enable) {
		s->inv_androidSensorsOn_mask[(androidSensor>>5)] |= 1L << (androidSensor & 0x1F); // Set bit
		*sensor_control |= delta;
	}
	else {
		s->inv_androidSensorsOn_mask[(androidSensor>>5)] &= ~(1L << (androidSensor & 0x1F)); // Clear bit
		// control has to be regenerated when removing sensors because of overlap
		inv_reGenerate_sensorControl(s, sen_num_2_ctrl, sensor_control, s->header2_count);
	}

	return;
}

int inv_icm20948_ctrl_enable_sensor(struct inv_icm20948 * s, unsigned char androidSensor, unsigned char enable)
{
	int result = 0;

	if(sensor_needs_compass(androidSensor))
		if(!inv_icm20948_get_compass_availability(s))
			return -1;

	inv_icm20948_prevent_lpen_control(s);
	if( s->mems_put_to_sleep ) {
		s->mems_put_to_sleep = 0;
		result |= inv_icm20948_wakeup_mems(s);
	}
	result |= inv_enable_sensor_internal(s, androidSensor, enable, &s->mems_put_to_sleep);
	inv_icm20948_allow_lpen_control(s);
	return result;
}

int inv_enable_sensor_internal(struct inv_icm20948 * s, unsigned char androidSensor, unsigned char enable, char * mems_put_to_sleep)
{
	int result = 0;
	unsigned short inv_event_control = 0;
	unsigned short data_rdy_status = 0;
	unsigned long steps=0;
	const short inv_androidSensor_to_control_bits[ANDROID_SENSOR_NUM_MAX]=
	{
		// Unsupported Sensors are -1
		-1, // Meta Data
		-32760, //0x8008, // Accelerometer
		0x0028, // Magnetic Field
		0x0408, // Orientation
		0x4048, // Gyroscope
		0x1008, // Light
		0x0088, // Pressure
		-1, // Temperature
		-1, // Proximity <----------- fixme
		0x0808, // Gravity
		-30712, // 0x8808, // Linear Acceleration
		0x0408, // Rotation Vector
		-1, // Humidity
		-1, // Ambient Temperature
		0x2008, // Magnetic Field Uncalibrated
		0x0808, // Game Rotation Vector
		0x4008, // Gyroscope Uncalibrated
		0, // Significant Motion
		0x0018, // Step Detector
		0x0010, // Step Counter <----------- fixme
		0x0108, // Geomagnetic Rotation Vector
		-1, //ANDROID_SENSOR_HEART_RATE,
		-1, //ANDROID_SENSOR_PROXIMITY,

		-32760, // ANDROID_SENSOR_WAKEUP_ACCELEROMETER,
		0x0028, // ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD,
		0x0408, // ANDROID_SENSOR_WAKEUP_ORIENTATION,
		0x4048, // ANDROID_SENSOR_WAKEUP_GYROSCOPE,
		0x1008, // ANDROID_SENSOR_WAKEUP_LIGHT,
		0x0088, // ANDROID_SENSOR_WAKEUP_PRESSURE,
		0x0808, // ANDROID_SENSOR_WAKEUP_GRAVITY,
		-30712, // ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION,
		0x0408, // ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR,
		-1,		// ANDROID_SENSOR_WAKEUP_RELATIVE_HUMIDITY,
		-1,		// ANDROID_SENSOR_WAKEUP_AMBIENT_TEMPERATURE,
		0x2008, // ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD_UNCALIBRATED,
		0x0808, // ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR,
		0x4008, // ANDROID_SENSOR_WAKEUP_GYROSCOPE_UNCALIBRATED,
		0x0018, // ANDROID_SENSOR_WAKEUP_STEP_DETECTOR,
		0x0010, // ANDROID_SENSOR_WAKEUP_STEP_COUNTER,
		0x0108, // ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR
		-1,		// ANDROID_SENSOR_WAKEUP_HEART_RATE,
		0,		// ANDROID_SENSOR_WAKEUP_TILT_DETECTOR,
		(short)0x8008, // Raw Acc . Why is this value being narrowed ? what does it do ?
		0x4048, // Raw Gyr
	};

	if(enable && !inv_icm20948_ctrl_androidSensor_enabled(s, androidSensor))
		s->skip_sample[inv_icm20948_sensor_android_2_sensor_type(androidSensor)] = 1;
		
	if (androidSensor == ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION) {
		if (enable) {
			s->smd_status = INV_SMD_EN;
			s->bac_request ++;
		}
		else {
			s->smd_status = 0;
			s->bac_request --;
		}
	}

	if (androidSensor == ANDROID_SENSOR_STEP_DETECTOR) {
		if (enable) {
			s->ped_int_status = INV_PEDOMETER_INT_EN;
			s->bac_request ++;
		}
		else {
			s->ped_int_status = 0;
			s->bac_request --;
		}
	}
	
	if (androidSensor == ANDROID_SENSOR_STEP_COUNTER) {
		if (enable) {
			s->bac_request ++;
		}
		else {
			s->bac_request --;
		}
	}

	if (androidSensor == ANDROID_SENSOR_FLIP_PICKUP) {
		if (enable){
			s->flip_pickup_status = FLIP_PICKUP_SET;
		}
		else
			s->flip_pickup_status = 0;
	}

	if (androidSensor == ANDROID_SENSOR_B2S) {
		if(enable){
			s->b2s_status = INV_BTS_EN;
			s->bac_request ++;
		}
		else {
			s->b2s_status = 0;
			s->bac_request --;
		}
	}
	if (androidSensor == ANDROID_SENSOR_ACTIVITY_CLASSIFICATON)
		inv_icm20948_ctrl_enable_activity_classifier(s, enable);

	if (androidSensor == ANDROID_SENSOR_WAKEUP_TILT_DETECTOR)
		inv_icm20948_ctrl_enable_tilt(s, enable);

	inv_convert_androidSensor_to_control(s, androidSensor, enable, inv_androidSensor_to_control_bits, &s->inv_sensor_control);
	result = dmp_icm20948_set_data_output_control1(s, s->inv_sensor_control);
	if (s->b2s_status)
		result |= dmp_icm20948_set_data_interrupt_control(s, s->inv_sensor_control|0x8008);
		// result |= dmp_icm20948_set_data_interrupt_control(s, s->inv_sensor_control|0x0000);
	else
		result |= dmp_icm20948_set_data_interrupt_control(s, s->inv_sensor_control);

	if (s->inv_sensor_control & ACCEL_SET)
		s->inv_sensor_control2 |= ACCEL_ACCURACY_SET;
	else
		s->inv_sensor_control2 &= ~ACCEL_ACCURACY_SET;

	if ((s->inv_sensor_control & GYRO_CALIBR_SET) || (s->inv_sensor_control & GYRO_SET))
		s->inv_sensor_control2 |= GYRO_ACCURACY_SET;
	else
		s->inv_sensor_control2 &= ~GYRO_ACCURACY_SET;

	if ((s->inv_sensor_control & CPASS_CALIBR_SET) || (s->inv_sensor_control & QUAT9_SET)
		|| (s->inv_sensor_control & GEOMAG_SET) || (s->inv_sensor_control & CPASS_SET))
		s->inv_sensor_control2 |= CPASS_ACCURACY_SET;
	else
		s->inv_sensor_control2 &= ~CPASS_ACCURACY_SET;

	if(s->flip_pickup_status)
		s->inv_sensor_control2 |= FLIP_PICKUP_SET;
	else
		s->inv_sensor_control2 &= ~FLIP_PICKUP_SET;

	// inv_event_control   |= s->b2s_status; 
	if(s->b2s_status)
	{
		inv_event_control |= INV_BRING_AND_LOOK_T0_SEE_EN;
		inv_event_control |= INV_PEDOMETER_EN;
#ifndef ICM20948_FOR_MOBILE // Next lines change BAC behavior to wearable platform
		inv_event_control |= INV_BAC_WEARABLE_EN;
		dmp_icm20948_set_ped_y_ratio(s, BAC_PED_Y_RATIO_WEARABLE);
#endif
	}
	else
	{
		inv_event_control &= ~INV_BRING_AND_LOOK_T0_SEE_EN;
		inv_event_control &= ~INV_PEDOMETER_EN;
#ifndef ICM20948_FOR_MOBILE // Next lines change BAC behavior to wearable platform
		inv_event_control &= ~INV_BAC_WEARABLE_EN;
#endif
	}

	result |= dmp_icm20948_set_data_output_control2(s, s->inv_sensor_control2);

	// sets DATA_RDY_STATUS in DMP based on which sensors are on
	if (s->inv_androidSensorsOn_mask[0] & INV_NEEDS_GYRO_MASK || s->inv_androidSensorsOn_mask[1] & INV_NEEDS_GYRO_MASK1)
		data_rdy_status |= GYRO_AVAILABLE;
	
	if (s->inv_androidSensorsOn_mask[0] & INV_NEEDS_ACCEL_MASK || s->inv_androidSensorsOn_mask[1] & INV_NEEDS_ACCEL_MASK1)
		data_rdy_status |= ACCEL_AVAILABLE;

	if (s->flip_pickup_status || s->b2s_status)
		data_rdy_status |= ACCEL_AVAILABLE;

	if (s->bac_status)
		data_rdy_status |= ACCEL_AVAILABLE;

	if (s->inv_androidSensorsOn_mask[0] & INV_NEEDS_COMPASS_MASK || s->inv_androidSensorsOn_mask[1] & INV_NEEDS_COMPASS_MASK1) {
		data_rdy_status |= SECONDARY_COMPASS_AVAILABLE;
		inv_event_control |= INV_COMPASS_CAL_EN;
	}
	// turn on gyro cal only if gyro is available
	if (data_rdy_status & GYRO_AVAILABLE)
		inv_event_control |= INV_GYRO_CAL_EN;
		
	// turn on acc cal only if acc is available
	if (data_rdy_status & ACCEL_AVAILABLE)
		inv_event_control |= INV_ACCEL_CAL_EN;

	inv_event_control |= s->smd_status | s->ped_int_status;

	if (s->inv_sensor_control & QUAT9_SET)
		inv_event_control |= INV_NINE_AXIS_EN;

	if (s->inv_sensor_control & (PED_STEPDET_SET | PED_STEPIND_SET) || inv_event_control & INV_SMD_EN) {
		inv_event_control |= INV_PEDOMETER_EN;
#ifndef ICM20948_FOR_MOBILE // Next lines change BAC behavior to wearable platform
		inv_event_control |= INV_BAC_WEARABLE_EN;
		dmp_icm20948_set_ped_y_ratio(s, BAC_PED_Y_RATIO_WEARABLE);
#endif
	}

	if (s->inv_sensor_control2 & ACT_RECOG_SET) {
		inv_event_control |= INV_PEDOMETER_EN;
#ifndef ICM20948_FOR_MOBILE // Next lines this to change BAC behavior to wearable platform
		inv_event_control |= INV_BAC_WEARABLE_EN;
		dmp_icm20948_set_ped_y_ratio(s, BAC_PED_Y_RATIO_WEARABLE);
#endif
	}

	if (s->inv_sensor_control2 & FLIP_PICKUP_SET){
		inv_event_control |= FLIP_PICKUP_EN;
	}

	if (s->inv_sensor_control & GEOMAG_SET)
		inv_event_control |= GEOMAG_EN;

	result |= dmp_icm20948_set_motion_event_control(s, inv_event_control);
	
	// A sensor was just enabled/disabled, need to recompute the required ODR for all augmented sensor-related sensors
	// The fastest ODR will always be applied to other related sensors
	if (   (androidSensor == ANDROID_SENSOR_GRAVITY) 
		|| (androidSensor == ANDROID_SENSOR_GAME_ROTATION_VECTOR) 
		|| (androidSensor == ANDROID_SENSOR_LINEAR_ACCELERATION) ) {
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_SIXQ]);
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_SIXQ_accel]);
	}

	if (   (androidSensor == ANDROID_SENSOR_ORIENTATION) 
		|| (androidSensor == ANDROID_SENSOR_ROTATION_VECTOR) ) {
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_NINEQ]);
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_NINEQ_accel]);
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_NINEQ_cpass]);
	}

	if (   (androidSensor == ANDROID_SENSOR_WAKEUP_GRAVITY) 
		|| (androidSensor == ANDROID_SENSOR_WAKEUP_GAME_ROTATION_VECTOR) 
		|| (androidSensor == ANDROID_SENSOR_WAKEUP_LINEAR_ACCELERATION) ) {
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_SIXQ]);
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_SIXQ_accel]);
	}

	if (   (androidSensor == ANDROID_SENSOR_WAKEUP_ORIENTATION) 
		|| (androidSensor == ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR) ) {
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_NINEQ]);
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_NINEQ_accel]);
		inv_icm20948_augmented_sensors_update_odr(s, androidSensor, &s->inv_dmp_odr_delays[INV_SENSOR_WAKEUP_NINEQ_cpass]);
	}

	result |= inv_set_hw_smplrt_dmp_odrs(s);
	result |= inv_icm20948_set_gyro_sf(s, inv_icm20948_get_gyro_divider(s), inv_icm20948_get_gyro_fullscale(s));

	if (!s->inv_sensor_control && !(s->inv_androidSensorsOn_mask[0] & (1L << ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION)) && !s->b2s_status) {
		*mems_put_to_sleep =1 ;
		result |= inv_icm20948_sleep_mems(s);
	}

	// DMP no longer controls PWR_MGMT_2 because of hardware bug, 0x80 set to override default behaviour of inv_icm20948_enable_hw_sensors()
	result |= inv_icm20948_enable_hw_sensors(s, (int)data_rdy_status | 0x80);

	// set DATA_RDY_STATUS in DMP
	if (data_rdy_status & SECONDARY_COMPASS_AVAILABLE)	{
		data_rdy_status |= SECONDARY_COMPASS_AVAILABLE;
	}

	result |= dmp_icm20948_set_data_rdy_status(s, data_rdy_status);

	// To have the all steps when you enable the sensor
	if (androidSensor == ANDROID_SENSOR_STEP_COUNTER)
	{
		if (enable)
		{
			dmp_icm20948_get_pedometer_num_of_steps(s, &steps);
			s->sStepCounterToBeSubtracted = steps - s->sOldSteps;
		}
	}

	return result;
}

void inv_icm20948_ctrl_enable_activity_classifier(struct inv_icm20948 * s, unsigned char enable) 
{
	s->bac_on = enable;
	if (enable) {
		s->bac_status = ACT_RECOG_SET;
		s->inv_sensor_control2 |= ACT_RECOG_SET;
		s->bac_request ++;
	}
	else {
		// only disable tilt engine if no request for tilt sensor
		if (!inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_WAKEUP_TILT_DETECTOR)) {
			s->bac_status = 0;
			s->inv_sensor_control2 &= ~ACT_RECOG_SET;
			s->bac_request --;
		}
	}
}

void inv_icm20948_ctrl_enable_tilt(struct inv_icm20948 * s, unsigned char enable) 
{
	if (enable) {
		s->bac_status = ACT_RECOG_SET;
		s->inv_sensor_control2 |= ACT_RECOG_SET;
		s->bac_request ++;
	}
	else {
		// do not disable BAC engine if BAC sensor is still on even though tilt is off
		if (!s->bac_on) {
			s->bac_status = 0;
			s->inv_sensor_control2 &= ~ACT_RECOG_SET;
			s->bac_request --;
		}
	}
}

int inv_icm20948_ctrl_enable_batch(struct inv_icm20948 * s, unsigned char enable)
{
	int ret = 0;

	if(enable)
		s->inv_sensor_control2 |= BATCH_MODE_EN;
	else
		s->inv_sensor_control2 &= ~BATCH_MODE_EN;

	ret = dmp_icm20948_set_data_output_control2(s, s->inv_sensor_control2);

	/* give batch mode status to mems transport layer 
	to allow disable/enable LP_EN when reading FIFO in batch mode */
	inv_icm20948_ctrl_set_batch_mode_status(s, enable);

	return ret;
}

void inv_icm20948_ctrl_set_batch_mode_status(struct inv_icm20948 * s, unsigned char enable)
{
	if(enable)
		s->sBatchMode=1;
	else
		s->sBatchMode=0;
}

unsigned char inv_icm20948_ctrl_get_batch_mode_status(struct inv_icm20948 * s)
{
	return s->sBatchMode;
}

int inv_icm20948_ctrl_set_batch_timeout(struct inv_icm20948 * s, unsigned short batch_time_in_seconds)
{
	unsigned int timeout = 0;

	if(    s->inv_sensor_control & GYRO_CALIBR_SET 
		|| s->inv_sensor_control & QUAT6_SET 
		|| s->inv_sensor_control & QUAT9_SET 
		|| s->inv_sensor_control & GYRO_SET ) { // If Gyro based sensor is enabled.
		timeout = (unsigned int) (batch_time_in_seconds * (BASE_SAMPLE_RATE/ (inv_icm20948_get_gyro_divider(s) + 1)));
		return dmp_icm20948_set_batchmode_params(s, timeout, GYRO_AVAILABLE);
	}

	if(    s->inv_sensor_control & ACCEL_SET 
		|| s->inv_sensor_control & GEOMAG_SET ) { // If Accel is enabled and no Gyro based sensor is enabled.
		timeout = (unsigned int) (batch_time_in_seconds * (BASE_SAMPLE_RATE/ (inv_icm20948_get_accel_divider(s) + 1)));
		return dmp_icm20948_set_batchmode_params(s, timeout, ACCEL_AVAILABLE);
	}

	if(    s->inv_sensor_control & CPASS_SET 
		|| s->inv_sensor_control & CPASS_CALIBR_SET ) {
		int rc = 0;

		timeout = (unsigned int) (batch_time_in_seconds * (BASE_SAMPLE_RATE/ inv_icm20948_get_secondary_divider(s)));
	
		if(    s->inv_sensor_control & CPASS_SET 
			|| s->inv_sensor_control & CPASS_CALIBR_SET ) {
			rc |= dmp_icm20948_set_batchmode_params(s, timeout, SECONDARY_COMPASS_AVAILABLE);
		}
	
		return rc;
	}

	return -1;  // Call batch only when a sensor is enabled.
}    

int inv_icm20948_ctrl_set_batch_timeout_ms(struct inv_icm20948 * s, unsigned short batch_time_in_ms)
{
	unsigned int timeout = 0;

	if(    s->inv_sensor_control & GYRO_CALIBR_SET 
		|| s->inv_sensor_control & QUAT6_SET 
		|| s->inv_sensor_control & QUAT9_SET 
		|| s->inv_sensor_control & GYRO_SET ) { // If Gyro based sensor is enabled.
		timeout = (unsigned int) ((batch_time_in_ms * (BASE_SAMPLE_RATE/ (inv_icm20948_get_gyro_divider(s) + 1)))/1000);
		if(batch_time_in_ms < s->inv_androidSensorsOdr_boundaries[ANDROID_SENSOR_GYROSCOPE][0]) {
			return -1; // requested batch timeout is not supported
		} else {
			return dmp_icm20948_set_batchmode_params(s, timeout, GYRO_AVAILABLE);
		}
	}

	if(    s->inv_sensor_control & ACCEL_SET
		|| s->inv_sensor_control & GEOMAG_SET ) { // If Accel is enabled and no Gyro based sensor is enabled.
		timeout = (unsigned int) ((batch_time_in_ms * (BASE_SAMPLE_RATE/ (inv_icm20948_get_accel_divider(s) + 1)))/1000);
		if(batch_time_in_ms < s->inv_androidSensorsOdr_boundaries[ANDROID_SENSOR_ACCELEROMETER][0]) {
			return -1; // requested batch timeout is not supported
		} else {
			return dmp_icm20948_set_batchmode_params(s, timeout, ACCEL_AVAILABLE);
		}
	}

	if(    s->inv_sensor_control & CPASS_SET 
		|| s->inv_sensor_control & CPASS_CALIBR_SET ) {
		timeout = (unsigned int) ((batch_time_in_ms * (BASE_SAMPLE_RATE/ inv_icm20948_get_secondary_divider(s)))/1000);
		if(batch_time_in_ms < s->inv_androidSensorsOdr_boundaries[ANDROID_SENSOR_GEOMAGNETIC_FIELD][0]) {
			return -1; // requested batch timeout is not supported
		} else {
			return dmp_icm20948_set_batchmode_params(s, timeout, SECONDARY_COMPASS_AVAILABLE);
		}
	}

	return -1; // Call batch only when a sensor is enabled.
}

/** Each bit corresponds to a sensor being on (Sensors 0 to 21)
*/
unsigned long *inv_icm20948_ctrl_get_androidSensorsOn_mask(struct inv_icm20948 * s)
{
	return s->inv_androidSensorsOn_mask;
}

unsigned short inv_icm20948_ctrl_get_activitiy_classifier_on_flag(struct inv_icm20948 * s)
{
	return s->bac_on;
}

/** @brief Sets accel quaternion gain according to accel engine rate.
* @param[in] hw_smplrt_divider  hardware sample rate divider such that accel engine rate = 1125Hz/hw_smplrt_divider
* @return 0 in case of success, -1 for any error
*/
int inv_icm20948_ctrl_set_accel_quaternion_gain(struct inv_icm20948 * s, unsigned short hw_smplrt_divider)
{
	int accel_gain = 15252014L; //set 225Hz gain as default

	switch (hw_smplrt_divider) {
		case 5: //1125Hz/5 = 225Hz
			accel_gain = 15252014L;
			break;
		case 10: //1125Hz/10 = 112Hz
			accel_gain = 30504029L;
			break;
		case 11: //1125Hz/11 = 102Hz
			accel_gain = 33554432L;
			break;
		case 22: //1125Hz/22 = 51Hz
			accel_gain = 67108864L;
			break;
		default:
			accel_gain = 15252014L;
			break;
	}

	return dmp_icm20948_set_accel_feedback_gain(s, accel_gain);
}

int inv_icm20948_ctrl_set_accel_cal_params(struct inv_icm20948 * s, unsigned short hw_smplrt_divider)
{
	int accel_cal_params[NUM_ACCEL_CAL_PARAMS] = {0};

	if (hw_smplrt_divider <= 5) { // freq = 225Hz
		accel_cal_params[ACCEL_CAL_ALPHA_VAR] = 1026019965L;
		accel_cal_params[ACCEL_CAL_A_VAR] = 47721859L;
	} 
	else if (hw_smplrt_divider <= 10) { // 225Hz > freq >= 112Hz
		accel_cal_params[ACCEL_CAL_ALPHA_VAR] = 977872018L;
		accel_cal_params[ACCEL_CAL_A_VAR] = 95869806L;
	} 
	else if (hw_smplrt_divider <= 11) { // 112Hz > freq >= 102Hz
		accel_cal_params[ACCEL_CAL_ALPHA_VAR] = 858993459L;
		accel_cal_params[ACCEL_CAL_A_VAR] = 214748365L;
		accel_cal_params[ACCEL_CAL_DIV] = 1;
	} 
	else if (hw_smplrt_divider <= 20) { // 102Hz > freq >= 56Hz
		accel_cal_params[ACCEL_CAL_ALPHA_VAR] = 882002213L;
		accel_cal_params[ACCEL_CAL_A_VAR] = 191739611L;
	} 
	else if (hw_smplrt_divider <= 22) { // 56Hz > freq >= 51Hz
		accel_cal_params[ACCEL_CAL_ALPHA_VAR] = 858993459L;
		accel_cal_params[ACCEL_CAL_A_VAR] = 214748365L;
	} 
	else if (hw_smplrt_divider <= 75) { // 51Hz > freq >= 15Hz
		accel_cal_params[ACCEL_CAL_ALPHA_VAR] = 357913941L;
		accel_cal_params[ACCEL_CAL_A_VAR] = 715827883L;
	} 
	else if (hw_smplrt_divider <= 225) { // 15Hz > freq >= 5Hz
		accel_cal_params[ACCEL_CAL_ALPHA_VAR] = 107374182L;
		accel_cal_params[ACCEL_CAL_A_VAR] = 966367642L;
	}

	return dmp_icm20948_set_accel_cal_params(s, accel_cal_params);
}

/* 5061:  this should be used to disable PICKUp after it triggers once
 * DO WE NEED TO CLEAR A BIT IN EVENT CONTROL?
 */
int inv_icm20948_ctrl_enable_pickup(struct inv_icm20948 * s, unsigned char enable)
{
	s->pickup = enable;
	if(enable)
		s->inv_sensor_control2 |= FLIP_PICKUP_EN;
	else
		s->inv_sensor_control2 &= ~FLIP_PICKUP_EN;

	return dmp_icm20948_set_data_output_control2(s, s->inv_sensor_control2);
}

int inv_icm20948_ctrl_get_acc_bias(struct inv_icm20948 * s, int * acc_bias)
{
	return dmp_icm20948_get_bias_acc(s, acc_bias);
}

int inv_icm20948_ctrl_get_gyr_bias(struct inv_icm20948 * s, int * gyr_bias)
{
	return dmp_icm20948_get_bias_gyr(s, gyr_bias);
}

int inv_icm20948_ctrl_get_mag_bias(struct inv_icm20948 * s, int * mag_bias)
{
	return dmp_icm20948_get_bias_cmp(s, mag_bias);
}

int inv_icm20948_ctrl_set_acc_bias(struct inv_icm20948 * s, int * acc_bias)
{
	int rc = 0;
	
	s->bias[0] = acc_bias[0];
	s->bias[1] = acc_bias[1];
	s->bias[2] = acc_bias[2];
	
	rc = dmp_icm20948_set_bias_acc(s, &s->bias[0]);
	
	return rc;
}

int inv_icm20948_ctrl_set_gyr_bias(struct inv_icm20948 * s, int * gyr_bias)
{
	int rc = 0;
	
	s->bias[3] = gyr_bias[0];
	s->bias[4] = gyr_bias[1];
	s->bias[5] = gyr_bias[2];
	
	rc = dmp_icm20948_set_bias_gyr(s, &s->bias[3]);
	
	return rc;
}

int inv_icm20948_ctrl_set_mag_bias(struct inv_icm20948 * s, int * mag_bias)
{
	int rc = 0;
	
	s->bias[6] = mag_bias[0];
	s->bias[7] = mag_bias[1];
	s->bias[8] = mag_bias[2];
	
	rc = dmp_icm20948_set_bias_cmp(s, &s->bias[6]);
	
	return rc;
}

unsigned char sensor_needs_compass(unsigned char androidSensor)
{
	switch(androidSensor) {
		case ANDROID_SENSOR_GEOMAGNETIC_FIELD:
		case ANDROID_SENSOR_ROTATION_VECTOR:
		case ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED:
		case ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR:
		case ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD:
		case ANDROID_SENSOR_WAKEUP_ROTATION_VECTOR:
		case ANDROID_SENSOR_WAKEUP_MAGNETIC_FIELD_UNCALIBRATED:
		case ANDROID_SENSOR_WAKEUP_GEOMAGNETIC_ROTATION_VECTOR:
			return 1;

		default :
			return 0;
	}
}

unsigned char sensor_needs_bac_algo(unsigned char androidSensor)
{
	switch(androidSensor){
	case ANDROID_SENSOR_FLIP_PICKUP:
	case ANDROID_SENSOR_ACTIVITY_CLASSIFICATON:
	case ANDROID_SENSOR_STEP_DETECTOR:
	case ANDROID_SENSOR_STEP_COUNTER:
	case ANDROID_SENSOR_WAKEUP_TILT_DETECTOR:
	case ANDROID_SENSOR_WAKEUP_STEP_DETECTOR:
	case ANDROID_SENSOR_WAKEUP_STEP_COUNTER:
	case ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION:
	case ANDROID_SENSOR_B2S:
		return 1;
	default:
		return 0;
	}
}

void inv_icm20948_prevent_lpen_control(struct inv_icm20948 * s)
{
	s->sAllowLpEn = 0;
}
void inv_icm20948_allow_lpen_control(struct inv_icm20948 * s)
{
	s->sAllowLpEn = 1;
	inv_icm20948_set_chip_power_state(s, CHIP_LP_ENABLE, 1);
}

uint8_t inv_icm20948_get_lpen_control(struct inv_icm20948 * s)
{
	return s->sAllowLpEn;
}

/*!
 ******************************************************************************
 *   @brief     This function sets the power state of the Ivory chip 
 *				loop
 *   @param[in] Function - CHIP_AWAKE, CHIP_LP_ENABLE
 *   @param[in] On/Off - The functions are enabled if previously disabled and 
                disabled if previously enabled based on the value of On/Off.
 ******************************************************************************
 */ 
int inv_icm20948_set_chip_power_state(struct inv_icm20948 * s, unsigned char func, unsigned char on_off)
{
	int status = 0;

	switch(func) {

		case CHIP_AWAKE:    
			if(on_off){
				if((s->base_state.wake_state & CHIP_AWAKE) == 0) {// undo sleep_en
					s->base_state.pwr_mgmt_1 &= ~BIT_SLEEP;
					status = inv_icm20948_write_single_mems_reg_core(s, REG_PWR_MGMT_1, s->base_state.pwr_mgmt_1);
					s->base_state.wake_state |= CHIP_AWAKE;
					inv_icm20948_sleep_100us(1); // after writing the bit wait 100 Micro Seconds
				}
			} else {
				if(s->base_state.wake_state & CHIP_AWAKE) {// set sleep_en
					s->base_state.pwr_mgmt_1 |= BIT_SLEEP;
					status = inv_icm20948_write_single_mems_reg_core(s, REG_PWR_MGMT_1, s->base_state.pwr_mgmt_1);
					s->base_state.wake_state &= ~CHIP_AWAKE;
					inv_icm20948_sleep_100us(1); // after writing the bit wait 100 Micro Seconds
				}
			}
		break;

		case CHIP_LP_ENABLE:
			if(s->base_state.lp_en_support == 1) {
				if(on_off) {
					if( (inv_icm20948_get_lpen_control(s)) && ((s->base_state.wake_state & CHIP_LP_ENABLE) == 0)){
						s->base_state.pwr_mgmt_1 |= BIT_LP_EN; // lp_en ON
						status = inv_icm20948_write_single_mems_reg_core(s, REG_PWR_MGMT_1, s->base_state.pwr_mgmt_1);
						s->base_state.wake_state |= CHIP_LP_ENABLE;
					}
				} else {
					if(s->base_state.wake_state & CHIP_LP_ENABLE){
						s->base_state.pwr_mgmt_1 &= ~BIT_LP_EN; // lp_en off
						status = inv_icm20948_write_single_mems_reg_core(s, REG_PWR_MGMT_1, s->base_state.pwr_mgmt_1);
						s->base_state.wake_state &= ~CHIP_LP_ENABLE;
						inv_icm20948_sleep_100us(1); // after writing the bit wait 100 Micro Seconds
					}
				}
			}
		break;

		default:
		break;

	}// end switch

	return status;
}

/*!
 ******************************************************************************
 *   @return    Current wake status of the Ivory chip.
 ******************************************************************************
 */
uint8_t inv_icm20948_get_chip_power_state(struct inv_icm20948 * s)
{
	return s->base_state.wake_state;
}

/** Wakes up DMP3 (SMARTSENSOR).
*/
int inv_icm20948_wakeup_mems(struct inv_icm20948 * s)
{
	unsigned char data;
	int result = 0;

	result = inv_icm20948_set_chip_power_state(s, CHIP_AWAKE, 1);

	if(s->base_state.serial_interface == SERIAL_INTERFACE_SPI) {
		s->base_state.user_ctrl |= BIT_I2C_IF_DIS;
		inv_icm20948_write_single_mems_reg(s, REG_USER_CTRL, s->base_state.user_ctrl);  
	}

	data = 0x47;	// FIXME, should set up according to sensor/engines enabled.
	result |= inv_icm20948_write_mems_reg(s, REG_PWR_MGMT_2, 1, &data);

	if(s->base_state.firmware_loaded == 1) {
		s->base_state.user_ctrl |= BIT_DMP_EN | BIT_FIFO_EN;
		result |= inv_icm20948_write_single_mems_reg(s, REG_USER_CTRL, s->base_state.user_ctrl);  
	}

	result |= inv_icm20948_set_chip_power_state(s, CHIP_LP_ENABLE, 1);
	return result;
}

/** Puts DMP3 (SMARTSENSOR) into the lowest power state. Assumes sensors are all off.
*/
int inv_icm20948_sleep_mems(struct inv_icm20948 * s)
{
	int result;
	unsigned char data;

	data = 0x7F;
	result = inv_icm20948_write_mems_reg(s, REG_PWR_MGMT_2, 1, &data);

	result |= inv_icm20948_set_chip_power_state(s, CHIP_AWAKE, 0);

	return result;
}

int inv_icm20948_set_dmp_address(struct inv_icm20948 * s)
{
	int result;
	unsigned char dmp_cfg[2] = {0};
	unsigned short config;

	// Write DMP Start address
	inv_icm20948_get_dmp_start_address(s, &config);
	/* setup DMP start address and firmware */
	dmp_cfg[0] = (unsigned char)((config >> 8) & 0xff);
	dmp_cfg[1] = (unsigned char)(config & 0xff);

	result = inv_icm20948_write_mems_reg(s, REG_PRGM_START_ADDRH, 2, dmp_cfg);
	return result;
}

/**
*  @brief      Set up the secondary I2C bus on 20630.
*  @param[in]  MPU state varible
*  @return     0 if successful.
*/

int inv_icm20948_set_secondary(struct inv_icm20948 * s)
{
	int r = 0;
	lIsInited = 0;

	if(lIsInited == 0) {
		r  = inv_icm20948_write_single_mems_reg(s, REG_I2C_MST_CTRL, BIT_I2C_MST_P_NSR);
		r |= inv_icm20948_write_single_mems_reg(s, REG_I2C_MST_ODR_CONFIG, MIN_MST_ODR_CONFIG);

		lIsInited = 1;
	}
	return r;
}

int inv_icm20948_enter_duty_cycle_mode(struct inv_icm20948 * s)
{
	/* secondary cycle mode should be set all the time */
	unsigned char data  = BIT_I2C_MST_CYCLE|BIT_ACCEL_CYCLE|BIT_GYRO_CYCLE;

	s->base_state.chip_lp_ln_mode = CHIP_LOW_POWER_ICM20948;
	return inv_icm20948_write_mems_reg(s, REG_LP_CONFIG, 1, &data);
}

int inv_icm20948_enter_low_noise_mode(struct inv_icm20948 * s)
{
	/* secondary cycle mode should be set all the time */
	unsigned char data  = BIT_I2C_MST_CYCLE;

	s->base_state.chip_lp_ln_mode = CHIP_LOW_NOISE_ICM20948;
	return inv_icm20948_write_mems_reg(s, REG_LP_CONFIG, 1, &data);
}

/** Should be called once on power up. Loads DMP3, initializes internal variables needed 
*   for other lower driver functions.
*/
int inv_icm20948_initialize_lower_driver(struct inv_icm20948 * s, enum SMARTSENSOR_SERIAL_INTERFACE type, 
	const uint8_t *dmp3_image, uint32_t dmp3_image_size)
{
	int result = 0;
	// set static variable
	s->sAllowLpEn = 1;
	s->s_compass_available = 0;
	// ICM20948 do not support the proximity sensor for the moment.
	// s_proximity_available variable is nerver changes
	s->s_proximity_available = 0;

	// Set varialbes to default values
	memset(&s->base_state, 0, sizeof(s->base_state));
	s->base_state.pwr_mgmt_1 = BIT_CLK_PLL;
	s->base_state.pwr_mgmt_2 = BIT_PWR_ACCEL_STBY | BIT_PWR_GYRO_STBY | BIT_PWR_PRESSURE_STBY;
	s->base_state.serial_interface = type;
	result |= inv_icm20948_read_mems_reg(s, REG_USER_CTRL, 1, &s->base_state.user_ctrl);

	result |= inv_icm20948_wakeup_mems(s);

	result |= inv_icm20948_read_mems_reg(s, REG_WHO_AM_I, 1, &data);

	/* secondary cycle mode should be set all the time */
	data = BIT_I2C_MST_CYCLE|BIT_ACCEL_CYCLE|BIT_GYRO_CYCLE;

	// Set default mode to low power mode
	result |= inv_icm20948_set_lowpower_or_highperformance(s, 0);
	
	// Disable Ivory DMP.
	if(s->base_state.serial_interface == SERIAL_INTERFACE_SPI)   
		s->base_state.user_ctrl = BIT_I2C_IF_DIS;
	else
		s->base_state.user_ctrl = 0;

	result |= inv_icm20948_write_single_mems_reg(s, REG_USER_CTRL, s->base_state.user_ctrl);

	//Setup Ivory DMP.
	result |= inv_icm20948_load_firmware(s, dmp3_image, dmp3_image_size);
	if(result)
		return result;
	else
		s->base_state.firmware_loaded = 1;

	result |= inv_icm20948_set_dmp_address(s);
	// Turn off all sensors on DMP by default.
	//result |= dmp_set_data_output_control1(0);   // FIXME in DMP, these should be off by default.
	result |= dmp_icm20948_reset_control_registers(s);
	
	// set FIFO watermark to 80% of actual FIFO size
	result |= dmp_icm20948_set_FIFO_watermark(s, 800);

	// Enable Interrupts.
	data = 0x2;
	result |= inv_icm20948_write_mems_reg(s, REG_INT_ENABLE, 1, &data); // Enable DMP Interrupt
	data = 0x1;
	result |= inv_icm20948_write_mems_reg(s, REG_INT_ENABLE_2, 1, &data); // Enable FIFO Overflow Interrupt

	// TRACKING : To have accelerometers datas and the interrupt without gyro enables.
	data = 0XE4;
	result |= inv_icm20948_write_mems_reg(s, REG_SINGLE_FIFO_PRIORITY_SEL, 1, &data);

	// Disable HW temp fix
	inv_icm20948_read_mems_reg(s, REG_HW_FIX_DISABLE,1,&data);
	data |= 0x08;
	inv_icm20948_write_mems_reg(s, REG_HW_FIX_DISABLE,1,&data);

	// Setup MEMs properties.
	s->base_state.accel_averaging = 1; //Change this value if higher sensor sample avergaing is required.
	s->base_state.gyro_averaging = 1;  //Change this value if higher sensor sample avergaing is required.
	inv_icm20948_set_gyro_divider(s, FIFO_DIVIDER);       //Initial sampling rate 1125Hz/19+1 = 56Hz.
	inv_icm20948_set_accel_divider(s, FIFO_DIVIDER);      //Initial sampling rate 1125Hz/19+1 = 56Hz.

	// Init the sample rate to 56 Hz for BAC,STEPC and B2S
	dmp_icm20948_set_bac_rate(s, DMP_ALGO_FREQ_56);
	dmp_icm20948_set_b2s_rate(s, DMP_ALGO_FREQ_56);

	// FIFO Setup.
	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_CFG, BIT_SINGLE_FIFO_CFG); // FIFO Config. fixme do once? burst write?
	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_RST, 0x1f); // Reset all FIFOs.
	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_RST, 0x1e); // Keep all but Gyro FIFO in reset.
	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_EN, 0x0); // Slave FIFO turned off.
	result |= inv_icm20948_write_single_mems_reg(s, REG_FIFO_EN_2, 0x0); // Hardware FIFO turned off.
    
	s->base_state.lp_en_support = 1;
	
	if(s->base_state.lp_en_support == 1)
		inv_icm20948_set_chip_power_state(s, CHIP_LP_ENABLE, 1);

	result |= inv_icm20948_sleep_mems(s);   
        
	return result;
}

void activate_compass(struct inv_icm20948 * s)
{
	s->s_compass_available = 1;
}

void desactivate_compass(struct inv_icm20948 * s)
{
	s->s_compass_available = 0;
}

int inv_icm20948_get_compass_availability(struct inv_icm20948 * s)
{
	return s->s_compass_available;
}

// return true 1 if gyro was enabled, otherwise false 0
unsigned char inv_is_gyro_enabled(struct inv_icm20948 * s)
{
	if ((s->inv_androidSensorsOn_mask[0] & INV_NEEDS_GYRO_MASK) || (s->inv_androidSensorsOn_mask[1] & INV_NEEDS_GYRO_MASK1))
		return 1;
	return 0;
}

int inv_icm20948_get_proximity_availability(struct inv_icm20948 * s)
{
	return s->s_proximity_available;
}

int inv_icm20948_set_slave_compass_id(struct inv_icm20948 * s, int id)
{
	int result = 0;
	(void)id;

	//result = inv_icm20948_wakeup_mems(s);
	//if (result)
	//	return result;
		
	inv_icm20948_prevent_lpen_control(s);
	activate_compass(s);
	
	inv_icm20948_init_secondary(s);

	// Set up the secondary I2C bus on 20630.
	inv_icm20948_set_secondary(s);

	//Setup Compass
	result = inv_icm20948_setup_compass_akm(s);

	//Setup Compass mounting matrix into DMP
	result |= inv_icm20948_compass_dmp_cal(s, s->mounting_matrix, s->mounting_matrix_secondary_compass);
	
	if (result)
		desactivate_compass(s);

	//result = inv_icm20948_sleep_mems(s);
	inv_icm20948_allow_lpen_control(s);
	return result;
}

int inv_icm20948_set_gyro_divider(struct inv_icm20948 * s, unsigned char div)
{
	s->base_state.gyro_div = div;
	return inv_icm20948_write_mems_reg(s, REG_GYRO_SMPLRT_DIV, 1, &div);
}

unsigned char inv_icm20948_get_gyro_divider(struct inv_icm20948 * s)
{
	return s->base_state.gyro_div;
}

int inv_icm20948_set_secondary_divider(struct inv_icm20948 * s, unsigned char div)
{
	s->base_state.secondary_div = 1UL<<div;
	return inv_icm20948_write_single_mems_reg(s, REG_I2C_MST_ODR_CONFIG, div);
}

unsigned short inv_icm20948_get_secondary_divider(struct inv_icm20948 * s)
{
	return s->base_state.secondary_div;
}

int inv_icm20948_set_accel_divider(struct inv_icm20948 * s, short div)
{
	unsigned char data[2] = {0};

	s->base_state.accel_div = div;
	data[0] = (unsigned char)(div >> 8);
	data[1] = (unsigned char)(div & 0xff);

	return inv_icm20948_write_mems_reg(s, REG_ACCEL_SMPLRT_DIV_1, 2, data);
}

short inv_icm20948_get_accel_divider(struct inv_icm20948 * s)
{
	return s->base_state.accel_div;
}

/*
 You can obtain the real odr in Milliseconds, Micro Seconds or Ticks.
 Use the enum values: ODR_IN_Ms, ODR_IN_Us or ODR_IN_Ticks,
 when calling inv_icm20948_get_odr_in_units().
*/
uint32_t inv_icm20948_get_odr_in_units(struct inv_icm20948 * s, unsigned short odrInDivider, unsigned char odr_units )
{
	unsigned long odr=0;
	unsigned long Us=0;
	unsigned char PLL=0, gyro_is_on=0;

	if(s->base_state.timebase_correction_pll == 0)
		inv_icm20948_read_mems_reg(s, REG_TIMEBASE_CORRECTION_PLL, 1, &s->base_state.timebase_correction_pll);
	
	PLL = s->base_state.timebase_correction_pll;

	// check if Gyro is currently enabled
	gyro_is_on = inv_is_gyro_enabled(s);

	if( PLL < 0x80 ) { // correction positive
		// In Micro Seconds
		Us = (odrInDivider*1000000L/1125L) * (1270L)/(1270L+ (gyro_is_on ? PLL : 0));
	} 
	else {
		PLL &= 0x7F;

		// In Micro Seconds 
		Us = (odrInDivider*1000000L/1125L) * (1270L)/(1270L-(gyro_is_on ? PLL : 0));
	}

	switch( odr_units ) {
		// ret in Milliseconds 
		case ODR_IN_Ms:
			odr = Us/1000;
			break;

		// ret in Micro
		case ODR_IN_Us:
			odr = Us;
			break;

		// ret in Ticks
		case ODR_IN_Ticks:
			odr = (Us/1000) * (32768/1125);// According to Mars
			break;
	}

	return odr;
}
 
/**
* Sets the DMP for a particular gyro configuration.
* @param[in] gyro_div Value written to GYRO_SMPLRT_DIV register, where
*            0=1125Hz sample rate, 1=562.5Hz sample rate, ... 4=225Hz sample rate, ...
*            10=102.2727Hz sample rate, ... etc.
* @param[in] gyro_level 0=250 dps, 1=500 dps, 2=1000 dps, 3=2000 dps
*/
int inv_icm20948_set_gyro_sf(struct inv_icm20948 * s, unsigned char div, int gyro_level)
{
	long gyro_sf;
	lLastGyroSf = 0;
	int result = 0;

	// gyro_level should be set to 4 regardless of fullscale, due to the addition of API dmp_icm20648_set_gyro_fsr()
	gyro_level = 4;

	if(s->base_state.timebase_correction_pll == 0)
		result |= inv_icm20948_read_mems_reg(s, REG_TIMEBASE_CORRECTION_PLL, 1, &s->base_state.timebase_correction_pll);

	{
		unsigned long long const MagicConstant = 264446880937391LL;
		unsigned long long const MagicConstantScale = 100000LL;
		unsigned long long ResultLL;

		if (s->base_state.timebase_correction_pll & 0x80) {
			ResultLL = (MagicConstant * (long long)(1ULL << gyro_level) * (1 + div) / (1270 - (s->base_state.timebase_correction_pll & 0x7F)) / MagicConstantScale);
		}
		else {
			ResultLL = (MagicConstant * (long long)(1ULL << gyro_level) * (1 + div) / (1270 + s->base_state.timebase_correction_pll) / MagicConstantScale);
		}
		/*
		    In above deprecated FP version, worst case arguments can produce a result that overflows a signed long.
		    Here, for such cases, we emulate the FP behavior of setting the result to the maximum positive value, as
		    the compiler's conversion of a u64 to an s32 is simple truncation of the u64's high half, sadly....
		*/
		if  (ResultLL > 0x7FFFFFFF) 
			gyro_sf = 0x7FFFFFFF;
		else
			gyro_sf = (long)ResultLL;
	}

	if (gyro_sf != lLastGyroSf) {
		result |= dmp_icm20948_set_gyro_sf(s, gyro_sf);
		lLastGyroSf = gyro_sf;
	}

	return result;
}

int inv_icm20948_set_gyro_fullscale(struct inv_icm20948 * s, int level)
{
	int result;
	s->base_state.gyro_fullscale = level;
	result = inv_icm20948_set_icm20948_gyro_fullscale(s, level);
	result |= inv_icm20948_set_gyro_sf(s, s->base_state.gyro_div, level);
	result |= dmp_icm20948_set_gyro_fsr(s, 250<<level);

	return result;
}

uint8_t inv_icm20948_get_gyro_fullscale(struct inv_icm20948 * s)
{
	return s->base_state.gyro_fullscale;
}


int inv_icm20948_set_icm20948_gyro_fullscale(struct inv_icm20948 * s, int level)
{
	int result = 0;
	unsigned char gyro_config_1_reg;
	unsigned char gyro_config_2_reg;
	unsigned char dec3_cfg;
	if (level >= NUM_MPU_GFS)
		return -1;

	result |= inv_icm20948_read_mems_reg(s, REG_GYRO_CONFIG_1, 1, &gyro_config_1_reg);
	gyro_config_1_reg &= 0xC0;
	gyro_config_1_reg |= (level << 1) | 1;  //fchoice = 1, filter = 0.
	result |= inv_icm20948_write_mems_reg(s, REG_GYRO_CONFIG_1, 1, &gyro_config_1_reg);

	result |= inv_icm20948_read_mems_reg(s, REG_GYRO_CONFIG_2, 1, &gyro_config_2_reg);
	gyro_config_2_reg &= 0xF8;
	
	switch(s->base_state.gyro_averaging) {
		case 1:
			dec3_cfg = 0;
			break;

		case 2:
			dec3_cfg = 1;
			break;

		case 4:
			dec3_cfg = 2;
			break;

		case 8:
			dec3_cfg = 3;
			break;

		case 16:
			dec3_cfg = 4;
			break;

		case 32:
			dec3_cfg = 5;
			break;

		case 64:
			dec3_cfg = 6;
			break;

		case 128:
			dec3_cfg = 7;
			break;

		default:
			dec3_cfg = 0;
			break;
	}
	gyro_config_2_reg |= dec3_cfg;  
	result |= inv_icm20948_write_single_mems_reg(s, REG_GYRO_CONFIG_2, gyro_config_2_reg);
	return result;
}


int inv_icm20948_set_accel_fullscale(struct inv_icm20948 * s, int level)
{
	int result;
	s->base_state.accel_fullscale = level;
	result = inv_icm20948_set_icm20948_accel_fullscale(s, level);
	result |= dmp_icm20948_set_accel_fsr(s, 2<<level);
	result |= dmp_icm20948_set_accel_scale2(s, 2<<level);
	return result;
}

uint8_t inv_icm20948_get_accel_fullscale(struct inv_icm20948 * s)
{
	return s->base_state.accel_fullscale;
}


int inv_icm20948_set_icm20948_accel_fullscale(struct inv_icm20948 * s, int level)
{
	int result = 0;
	unsigned char accel_config_1_reg;
	unsigned char accel_config_2_reg;
	unsigned char dec3_cfg;

	if (level >= NUM_MPU_AFS)
		return -1;

	result |= inv_icm20948_read_mems_reg(s, REG_ACCEL_CONFIG, 1, &accel_config_1_reg);
	accel_config_1_reg &= 0xC0;

	if(s->base_state.accel_averaging > 1)
		accel_config_1_reg |= (7 << 3) | (level << 1) | 1;   //fchoice = 1, filter = 7.
	else
		accel_config_1_reg |= (level << 1) | 0;  //fchoice = 0, filter = 0.
	/* /!\ FCHOICE=0 considers we are in low power mode always and allows us to have correct values on raw data since not averaged,
	in case low noise mode is to be supported for 20649, please reconsider this value and update base sample rate from 1125 to 4500...
	*/
	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_CONFIG, accel_config_1_reg);

	switch(s->base_state.accel_averaging) {
		case 1:
			dec3_cfg = 0;
			break;

		case 4:
			dec3_cfg = 0;
			break;
		
		case 8:
			dec3_cfg = 1;
			break;
	
		case 16:
			dec3_cfg = 2;
			break;
		
		case 32:
			dec3_cfg = 3;
			break;

		default:
			dec3_cfg = 0;
			break;
	}

	result |= inv_icm20948_read_mems_reg(s, REG_ACCEL_CONFIG_2, 1, &accel_config_2_reg);
	accel_config_2_reg &= 0xFC;

	accel_config_2_reg |=  dec3_cfg;
	result |= inv_icm20948_write_single_mems_reg(s, REG_ACCEL_CONFIG_2, accel_config_2_reg);

	return result;
}


int inv_icm20948_enable_hw_sensors(struct inv_icm20948 * s, int bit_mask)
{
	int rc = 0;

	if ((s->base_state.pwr_mgmt_2 == (BIT_PWR_ACCEL_STBY | BIT_PWR_GYRO_STBY | BIT_PWR_PRESSURE_STBY)) | (bit_mask & 0x80)) {
		// All sensors off, or override is on
		s->base_state.pwr_mgmt_2 = 0; // Zero means all sensors are on
		// Gyro and Accel were off
		if ((bit_mask & 2) == 0) {
			s->base_state.pwr_mgmt_2 = BIT_PWR_ACCEL_STBY; // Turn off accel
		}
		if ((bit_mask & 1) == 0) {
			s->base_state.pwr_mgmt_2 |= BIT_PWR_GYRO_STBY; // Turn off gyro
		}
		if ((bit_mask & 4) == 0) {
			s->base_state.pwr_mgmt_2 |= BIT_PWR_PRESSURE_STBY; // Turn off pressure
		}

		rc |= inv_icm20948_write_mems_reg(s, REG_PWR_MGMT_2, 1, &s->base_state.pwr_mgmt_2);
	}

	if (bit_mask & SECONDARY_COMPASS_AVAILABLE) {
		rc |= inv_icm20948_resume_akm(s);
	} 
	else {
		rc |= inv_icm20948_suspend_akm(s);
	}

	return rc;
}

int inv_icm20948_set_serial_comm(struct inv_icm20948 * s, enum SMARTSENSOR_SERIAL_INTERFACE type)
{
	s->base_state.serial_interface = type;

	return 0;
}


int inv_icm20948_set_int1_assertion(struct inv_icm20948 * s, int enable)
{
	int   result = 0;
	// unsigned char reg_pin_cfg;
	unsigned char reg_int_enable;

	// INT1 held until interrupt status is cleared
	/*
	result         |= inv_icm20948_read_mems_reg(s, REG_INT_PIN_CFG, 1, &reg_pin_cfg);
	reg_pin_cfg    |= BIT_INT_LATCH_EN ;	// Latchen : BIT5 held the IT until register is read
	result         |= inv_icm20948_write_single_mems_reg(s, REG_INT_PIN_CFG, reg_pin_cfg);
	*/

	// Set int1 enable
	result |= inv_icm20948_read_mems_reg(s, REG_INT_ENABLE, 1, &reg_int_enable);

	if(enable) { // Enable bit
		reg_int_enable |= BIT_DMP_INT_EN;
	}
	else { // Disable bit
		reg_int_enable &= ~BIT_DMP_INT_EN;
	}

	result |= inv_icm20948_write_single_mems_reg(s, REG_INT_ENABLE, reg_int_enable);

	return result;
}


/**
*  @brief      Read accel data stored in hw reg
*  @param[in]  level  See mpu_accel_fs
*  @return     0 if successful
*/
int inv_icm20948_accel_read_hw_reg_data(struct inv_icm20948 * s, short accel_hw_reg_data[3])
{
	int result = 0;
	uint8_t accel_data[6]; // Store 6 bytes for that

	// read mem regs
	result = inv_icm20948_read_mems_reg(s, REG_ACCEL_XOUT_H_SH, 6, (unsigned char *) &accel_data);

	// Assign axys !
	accel_hw_reg_data[0] = (accel_data[0] << 8) + accel_data[1];
	accel_hw_reg_data[1] = (accel_data[2] << 8) + accel_data[3];
	accel_hw_reg_data[2] = (accel_data[4] << 8) + accel_data[5];

	return result;
}

void invn_convert_quat_mult_fxp(const long *quat1_q30, const long *quat2_q30, long *quatProd_q30)
{
    quatProd_q30[0] = inv_icm20948_convert_mult_q30_fxp(quat1_q30[0], quat2_q30[0]) - inv_icm20948_convert_mult_q30_fxp(quat1_q30[1], quat2_q30[1]) -
               inv_icm20948_convert_mult_q30_fxp(quat1_q30[2], quat2_q30[2]) - inv_icm20948_convert_mult_q30_fxp(quat1_q30[3], quat2_q30[3]);

    quatProd_q30[1] = inv_icm20948_convert_mult_q30_fxp(quat1_q30[0], quat2_q30[1]) + inv_icm20948_convert_mult_q30_fxp(quat1_q30[1], quat2_q30[0]) +
               inv_icm20948_convert_mult_q30_fxp(quat1_q30[2], quat2_q30[3]) - inv_icm20948_convert_mult_q30_fxp(quat1_q30[3], quat2_q30[2]);

    quatProd_q30[2] = inv_icm20948_convert_mult_q30_fxp(quat1_q30[0], quat2_q30[2]) - inv_icm20948_convert_mult_q30_fxp(quat1_q30[1], quat2_q30[3]) +
               inv_icm20948_convert_mult_q30_fxp(quat1_q30[2], quat2_q30[0]) + inv_icm20948_convert_mult_q30_fxp(quat1_q30[3], quat2_q30[1]);

    quatProd_q30[3] = inv_icm20948_convert_mult_q30_fxp(quat1_q30[0], quat2_q30[3]) + inv_icm20948_convert_mult_q30_fxp(quat1_q30[1], quat2_q30[2]) -
               inv_icm20948_convert_mult_q30_fxp(quat1_q30[2], quat2_q30[1]) + inv_icm20948_convert_mult_q30_fxp(quat1_q30[3], quat2_q30[0]);
}

void invn_convert_quat_invert_fxp(const long *quat_q30, long *invQuat_q30)
{
    invQuat_q30[0] = quat_q30[0];
    invQuat_q30[1] = -quat_q30[1];
    invQuat_q30[2] = -quat_q30[2];
    invQuat_q30[3] = -quat_q30[3];
}

void inv_icm20948_q_mult_q_qi(const long *q1, const long *q2, long *qProd)
{
    qProd[0] = inv_icm20948_convert_mult_q30_fxp(q1[0], q2[0]) + inv_icm20948_convert_mult_q30_fxp(q1[1], q2[1]) +
               inv_icm20948_convert_mult_q30_fxp(q1[2], q2[2]) + inv_icm20948_convert_mult_q30_fxp(q1[3], q2[3]);

    qProd[1] = -inv_icm20948_convert_mult_q30_fxp(q1[0], q2[1]) + inv_icm20948_convert_mult_q30_fxp(q1[1], q2[0]) -
               inv_icm20948_convert_mult_q30_fxp(q1[2], q2[3]) + inv_icm20948_convert_mult_q30_fxp(q1[3], q2[2]);

    qProd[2] = -inv_icm20948_convert_mult_q30_fxp(q1[0], q2[2]) + inv_icm20948_convert_mult_q30_fxp(q1[1], q2[3]) +
               inv_icm20948_convert_mult_q30_fxp(q1[2], q2[0]) - inv_icm20948_convert_mult_q30_fxp(q1[3], q2[1]);

    qProd[3] = -inv_icm20948_convert_mult_q30_fxp(q1[0], q2[3]) - inv_icm20948_convert_mult_q30_fxp(q1[1], q2[2]) +
               inv_icm20948_convert_mult_q30_fxp(q1[2], q2[1]) + inv_icm20948_convert_mult_q30_fxp(q1[3], q2[0]);
}

void inv_icm20948_convert_quat_rotate_fxp(const long *quat_q30, const long *in, long *out)
{
    long q_temp1[4], q_temp2[4];
    long in4[4], out4[4];

    // Fixme optimize
    in4[0] = 0;
    memcpy(&in4[1], in, 3 * sizeof(long));
    invn_convert_quat_mult_fxp(quat_q30, in4, q_temp1);
    invn_convert_quat_invert_fxp(quat_q30, q_temp2);
    invn_convert_quat_mult_fxp(q_temp1, q_temp2, out4);
    memcpy(out, &out4[1], 3 * sizeof(long));
}

/** Set the transformation used for chip to body frame
*/
void inv_icm20948_set_chip_to_body(struct inv_icm20948 * s, long *quat)
{
    memcpy(s->s_quat_chip_to_body, quat, sizeof(s->s_quat_chip_to_body));
}

/** Convert fixed point DMP rotation vector to floating point android notation
* @param[in] quat 3 element rotation vector from DMP, missing the scalar part. Converts from Chip frame to World frame
* @param[out] values 4 element quaternion in Android format
*/
void inv_icm20948_convert_rotation_vector(struct inv_icm20948 * s, const long *quat, float *values)
{
    long quat4[4];
    long quat_body_to_world[4];

    inv_icm20948_convert_compute_scalar_part_fxp(quat, quat4);
    inv_icm20948_q_mult_q_qi(quat4, s->s_quat_chip_to_body, quat_body_to_world);
    if (quat_body_to_world[0] >= 0) {
        values[0] = quat_body_to_world[1] * INV_TWO_POWER_NEG_30;
        values[1] = quat_body_to_world[2] * INV_TWO_POWER_NEG_30;
        values[2] = quat_body_to_world[3] * INV_TWO_POWER_NEG_30;
        values[3] = quat_body_to_world[0] * INV_TWO_POWER_NEG_30;
    } else {
        values[0] = -quat_body_to_world[1] * INV_TWO_POWER_NEG_30;
        values[1] = -quat_body_to_world[2] * INV_TWO_POWER_NEG_30;
        values[2] = -quat_body_to_world[3] * INV_TWO_POWER_NEG_30;
        values[3] = -quat_body_to_world[0] * INV_TWO_POWER_NEG_30;
    }
}

/** Convert 3 element fixed point DMP rotation vector to 4 element rotation vector in world frame
* @param[in] quat 3 element rotation vector from DMP, missing the scalar part. Converts from Chip frame to World frame
* @param[out] values 4 element quaternion
*/
void inv_icm20948_convert_rotation_vector_2(struct inv_icm20948 * s, const long *quat, long *quat4_world)
{
    long quat4[4];
    long quat_body_to_world[4];

    inv_icm20948_convert_compute_scalar_part_fxp(quat, quat4);
    inv_icm20948_q_mult_q_qi(quat4, s->s_quat_chip_to_body, quat_body_to_world);
    memcpy(quat4_world, quat_body_to_world, 4*sizeof(long));
}

/** Convert 4 element rotation vector in world frame to floating point android notation
* @param[in] quat 4 element rotation vector in World frame
* @param[out] values in Android format
*/
void inv_icm20948_convert_rotation_vector_3(const long *quat4_world, float *values)
{
    if (quat4_world[0] >= 0) {
        values[0] = quat4_world[1] * INV_TWO_POWER_NEG_30;
        values[1] = quat4_world[2] * INV_TWO_POWER_NEG_30;
        values[2] = quat4_world[3] * INV_TWO_POWER_NEG_30;
        values[3] = quat4_world[0] * INV_TWO_POWER_NEG_30;
    } else {
        values[0] = -quat4_world[1] * INV_TWO_POWER_NEG_30;
        values[1] = -quat4_world[2] * INV_TWO_POWER_NEG_30;
        values[2] = -quat4_world[3] * INV_TWO_POWER_NEG_30;
        values[3] = -quat4_world[0] * INV_TWO_POWER_NEG_30;
    }
}

void inv_rotation_to_quaternion(float Rcb[9], long Qcb_fp[4]) {	
	float q[4]; 
	inv_icm20948_convert_matrix_to_quat_flt(Rcb, q); 
	INVN_CONVERT_FLT_TO_FXP(q, Qcb_fp, 4, 30); 
}

void inv_icm20948_set_chip_to_body_axis_quaternion(struct inv_icm20948 * s, signed char *accel_gyro_matrix, float angle)
{
    int i;
    float rot[9];
    long qcb[4],q_all[4];
    long q_adjust[4];
    for (i=0; i<9; i++) {
        rot[i] = (float)accel_gyro_matrix[i];
    }
    // Convert Chip to Body transformation matrix to quaternion
    // inv_icm20948_convert_matrix_to_quat_fxp(rot, qcb);
	inv_rotation_to_quaternion(rot, qcb);
	
    // The quaterion generated is the inverse, take the inverse again.
    qcb[1] = -qcb[1];
    qcb[2] = -qcb[2];
    qcb[3] = -qcb[3];

    // Now rotate by angle, negate angle to rotate other way
    q_adjust[0] = (long)((1L<<30) * cosf(-angle*(float)M_PI/180.f/2.f));
    q_adjust[1] = 0;
    q_adjust[2] = (long)((1L<<30) * sinf(-angle*(float)M_PI/180.f/2.f));
    q_adjust[3] = 0;
    invn_convert_quat_mult_fxp(q_adjust, qcb, q_all);
    inv_icm20948_set_chip_to_body(s, q_all);
}

void inv_icm20948_convert_dmp3_to_body(struct inv_icm20948 * s, const long *vec3, float scale, float *values)
{
    long out[3];
    inv_icm20948_convert_quat_rotate_fxp(s->s_quat_chip_to_body, vec3, out);
    values[0] = out[0] * scale;
    values[1] = out[1] * scale;
    values[2] = out[2] * scale;
}

/** Converts a 32-bit long to a little endian byte stream */
unsigned char *inv_icm20948_int32_to_little8(long x, unsigned char *little8)
{
    little8[3] = (unsigned char)((x >> 24) & 0xff);
    little8[2] = (unsigned char)((x >> 16) & 0xff);
    little8[1] = (unsigned char)((x >> 8) & 0xff);
    little8[0] = (unsigned char)(x & 0xff);
    return little8;
}

float inv_icm20948_convert_deg_to_rad(float deg_val)
{
	float rad_val;
    rad_val = deg_val*(float)M_PI / 180.f;
	return rad_val;
}

long inv_icm20948_convert_mult_q30_fxp(long a_q30, long b_q30)
{
	long long temp;
	long result;
	temp = (long long)a_q30 * b_q30;
	result = (long)(temp >> 30);
	return result;
}

int inv_icm20948_convert_compute_scalar_part_fxp(const long * inQuat_q30, long* outQuat_q30)
{
    long scalarPart = 0;

    scalarPart = inv_icm20948_convert_fast_sqrt_fxp((1L<<30) - inv_icm20948_convert_mult_q30_fxp(inQuat_q30[0], inQuat_q30[0])
                                        - inv_icm20948_convert_mult_q30_fxp(inQuat_q30[1], inQuat_q30[1])
                                        - inv_icm20948_convert_mult_q30_fxp(inQuat_q30[2], inQuat_q30[2]) );
    outQuat_q30[0] = scalarPart;
    outQuat_q30[1] = inQuat_q30[0];
    outQuat_q30[2] = inQuat_q30[1];
    outQuat_q30[3] = inQuat_q30[2];

    return 0;
}

long inv_icm20948_convert_fast_sqrt_fxp(long x0_q30)
{

	//% Square-Root with NR in the neighborhood of 1.3>x>=0.65 (log(2) <= x <= log(4) )
    // Two-variable NR iteration:
    // Initialize: a=x; c=x-1;  
    // 1st Newton Step:  a=a-a*c/2; ( or: a = x - x*(x-1)/2  )
    // Iterate: c = c*c*(c-3)/4
    //          a = a - a*c/2    --> reevaluating c at this step gives error of approximation

	//% Seed equals 1. Works best in this region.
	//xx0 = int32(1*2^30);

	long sqrt2, oneoversqrt2, one_pt5;
	long xx, cc;
	int pow2, sq2scale, nr_iters;

	// Return if input is zero. Negative should really error out. 
	if (x0_q30 <= 0L) {
		return 0L;
	}

	sqrt2 =1518500250L;
	oneoversqrt2=759250125L;
	one_pt5=1610612736L;

	nr_iters = inv_icm20948_convert_test_limits_and_scale_fxp(&x0_q30, &pow2);
	
	sq2scale = 0;
	if (pow2 > 0) 
		sq2scale=pow2%2;  // Find remainder. Is it even or odd?
	pow2 = pow2-sq2scale; // Now pow2 is even. Note we are adding because result is scaled with sqrt(2)

	// Sqrt 1st NR iteration
	cc = x0_q30 - (1L<<30);
	xx = x0_q30 - (inv_icm20948_convert_mult_q30_fxp(x0_q30, cc)>>1);
 	if ( nr_iters>=2 ) {
		// Sqrt second NR iteration
		// cc = cc*cc*(cc-3)/4; = cc*cc*(cc/2 - 3/2)/2;
		// cc = ( cc*cc*((cc>>1) - onePt5) ) >> 1
		cc = inv_icm20948_convert_mult_q30_fxp( cc, inv_icm20948_convert_mult_q30_fxp(cc, (cc>>1) - one_pt5) ) >> 1;
		xx = xx - (inv_icm20948_convert_mult_q30_fxp(xx, cc)>>1);
		if ( nr_iters==3 ) {
			// Sqrt third NR iteration
			cc = inv_icm20948_convert_mult_q30_fxp( cc, inv_icm20948_convert_mult_q30_fxp(cc, (cc>>1) - one_pt5) ) >> 1;
			xx = xx - (inv_icm20948_convert_mult_q30_fxp(xx, cc)>>1);
		}
	}
	if (sq2scale)
		xx = inv_icm20948_convert_mult_q30_fxp(xx,oneoversqrt2);
	// Scale the number with the half of the power of 2 scaling
	if (pow2>0)
		xx = (xx >> (pow2>>1)); 
	else if (pow2 == -1)
		xx = inv_icm20948_convert_mult_q30_fxp(xx,sqrt2);
	return xx;
}

int inv_icm20948_convert_test_limits_and_scale_fxp(long *x0_q30, int *pow)
{
    long lowerlimit, upperlimit, oneiterlothr, oneiterhithr, zeroiterlothr, zeroiterhithr;

    // Lower Limit: ll = int32(log(2)*2^30);
    lowerlimit = 744261118L;
    //Upper Limit ul = int32(log(4)*2^30);
    upperlimit = 1488522236L;
    //  int32(0.9*2^30)
    oneiterlothr = 966367642L;
    // int32(1.1*2^30)
    oneiterhithr = 1181116006L;
    // int32(0.99*2^30)
    zeroiterlothr=1063004406L;
    //int32(1.01*2^30)
    zeroiterhithr=1084479242L;

    // Scale number such that Newton Raphson iteration works best:
    // Find the power of two scaling that leaves the number in the optimal range,
    // ll <= number <= ul. Note odd powers have special scaling further below
	if (*x0_q30 > upperlimit) {
		// Halving the number will push it in the optimal range since largest value is 2
		*x0_q30 = *x0_q30>>1;
		*pow=-1;
	} else if (*x0_q30 < lowerlimit) {
		// Find position of highest bit, counting from left, and scale number 
		*pow=inv_icm20948_convert_get_highest_bit_position((uint32_t*)x0_q30);
		if (*x0_q30 >= upperlimit) {
			// Halving the number will push it in the optimal range
			*x0_q30 = *x0_q30>>1;
			*pow=*pow-1;
		}
		else if (*x0_q30 < lowerlimit) {
			// Doubling the number will push it in the optimal range
			*x0_q30 = *x0_q30<<1;
			*pow=*pow+1;
		}
	} else {
		*pow = 0;
	}
    
    if ( *x0_q30<oneiterlothr || *x0_q30>oneiterhithr )
        return 3; // 3 NR iterations
    if ( *x0_q30<zeroiterlothr || *x0_q30>zeroiterhithr )
        return 2; // 2 NR iteration

    return 1; // 1 NR iteration
}

/** Auxiliary function used by testLimitsAndScale()
* Find the highest nonzero bit in an unsigned 32 bit integer:
* @param[in] value operand Dimension is 1.
* @return highest bit position.
* \note This function performs the log2 of an interger as well. 
* \ingroup binary
**/
int16_t inv_icm20948_convert_get_highest_bit_position(uint32_t *value)
{
    int16_t position;
    position = 0;
    if (*value == 0) return 0;

    if ((*value & 0xFFFF0000) == 0) {
        position += 16;
        *value=*value<<16;
    }
    if ((*value & 0xFF000000) == 0) {
        position += 8;
        *value=*value<<8;
    }
    if ((*value & 0xF0000000) == 0) {
        position += 4;
        *value=*value<<4;
    }
    if ((*value & 0xC0000000) == 0) {
        position += 2;
        *value=*value<<2;
    }

    // If we got too far into sign bit, shift back. Note we are using an
    // unsigned long here, so right shift is going to shift all the bits.
    if ((*value & 0x80000000)) { 
        position -= 1;
        *value=*value>>1;
    }
    return position;
}

void inv_icm20948_convert_matrix_to_quat_fxp(long *Rcb_q30, long *Qcb_q30)
{
         long r11,r12,r13, r21,r22,r23, r31,r32,r33;
         long temp[3];
         long tmp;
         int pow2, shift;

         r11 = Rcb_q30[0]>>1; //assume matrix is stored row wise first, that is rot[1] is row 1, col 2
         r12 = Rcb_q30[1]>>1;
         r13 = Rcb_q30[2]>>1;

         r21 = Rcb_q30[3]>>1;
         r22 = Rcb_q30[4]>>1;
         r23 = Rcb_q30[5]>>1;

         r31 = Rcb_q30[6]>>1;
         r32 = Rcb_q30[7]>>1;
         r33 = Rcb_q30[8]>>1;

         //Qcb[0] = (1.f + r11 + r22 + r33) / 4.f;
         //Qcb[1] = (1.f + r11 - r22 - r33) / 4.f;
         //Qcb[2] = (1.f - r11 + r22 - r33) / 4.f;
         //Qcb[3] = (1.f - r11 - r22 + r33) / 4.f;
         Qcb_q30[0] = (268435456L + (r11>>1) + (r22>>1) + (r33>>1)); // Effectively shifted by 2 bits, one above, one here
         Qcb_q30[1] = (268435456L + (r11>>1) - (r22>>1) - (r33>>1));
         Qcb_q30[2] = (268435456L - (r11>>1) + (r22>>1) - (r33>>1));
         Qcb_q30[3] = (268435456L - (r11>>1) - (r22>>1) + (r33>>1));

         if(Qcb_q30[0] < 0L) Qcb_q30[0] = 0L;
         if(Qcb_q30[1] < 0L) Qcb_q30[1] = 0L;
         if(Qcb_q30[2] < 0L) Qcb_q30[2] = 0L;
         if(Qcb_q30[3] < 0L) Qcb_q30[3] = 0L;
         if (Qcb_q30[0] == 0L && Qcb_q30[1] == 0L && Qcb_q30[2] == 0L && Qcb_q30[3] == 0L) {
             Qcb_q30[0] = 1L<<30;
             return;
         }
         //Qcb[0] = sqrt(Qcb[0]);
         //Qcb[1] = sqrt(Qcb[1]);
         //Qcb[2] = sqrt(Qcb[2]);
         //Qcb[3] = sqrt(Qcb[3]);
         Qcb_q30[0] = inv_icm20948_convert_sqrt_q30_fxp(Qcb_q30[0]);
         Qcb_q30[1] = inv_icm20948_convert_sqrt_q30_fxp(Qcb_q30[1]);
         Qcb_q30[2] = inv_icm20948_convert_sqrt_q30_fxp(Qcb_q30[2]);
         Qcb_q30[3] = inv_icm20948_convert_sqrt_q30_fxp(Qcb_q30[3]);

         if(Qcb_q30[0] >= Qcb_q30[1] && Qcb_q30[0] >= Qcb_q30[2] && Qcb_q30[0] >= Qcb_q30[3]) //Qcb[0] is max
         {
                tmp = inv_icm20948_convert_inverse_q30_fxp(Qcb_q30[0], &pow2);
                shift = 30 - pow2 + 1;
                Qcb_q30[1] = (long)(((long long)(r23 - r32) * tmp) >> shift) ;
                Qcb_q30[2] = (long)(((long long)(r31 - r13) * tmp) >> shift) ;
                Qcb_q30[3] = (long)(((long long)(r12 - r21) * tmp) >> shift) ;
                 //Qcb[1] = (r23 - r32)/(4.f*Qcb[0]);
                 //Qcb[2] = (r31 - r13)/(4.f*Qcb[0]);
                 //Qcb[3] = (r12 - r21)/(4.f*Qcb[0]);
         }
         else if(Qcb_q30[1] >= Qcb_q30[0] && Qcb_q30[1] >= Qcb_q30[2] && Qcb_q30[1] >= Qcb_q30[3]) //Qcb[1] is max
         {
                tmp = inv_icm20948_convert_inverse_q30_fxp(Qcb_q30[1], &pow2);
                shift = 30 - pow2 + 1;
		        Qcb_q30[0] = (long)(((long long)(r23 - r32) * tmp) >> shift) ;
		        Qcb_q30[2] = (long)(((long long)(r12 + r21) * tmp) >> shift) ;
		        Qcb_q30[3] = (long)(((long long)(r31 + r13) * tmp) >> shift) ;
                // Qcb[0] = (r23 - r32)/(4.f*Qcb[1]);
                // Qcb[1] = Qcb[1];
                // Qcb[2] = (r12 + r21)/(4.f*Qcb[1]);
                // Qcb[3] = (r31 + r13)/(4.f*Qcb[1]);
         }
         else if(Qcb_q30[2] >= Qcb_q30[0] && Qcb_q30[2] >= Qcb_q30[1] && Qcb_q30[2] >= Qcb_q30[3]) //Qcb[2] is max
         {
                tmp = inv_icm20948_convert_inverse_q30_fxp(Qcb_q30[2], &pow2);
                shift = 30 - pow2 + 1;
		        Qcb_q30[0] = (long)(((long long)(r31 - r13) * tmp) >> shift) ;
		        Qcb_q30[1] = (long)(((long long)(r12 + r21) * tmp) >> shift) ;
		        Qcb_q30[3] = (long)(((long long)(r23 + r32) * tmp) >> shift) ;
                 //Qcb[0] = (r31 - r13)/(4.f*Qcb[2]);
                 //Qcb[1] = (r12 + r21)/(4.f*Qcb[2]);
                 //Qcb[2] = Qcb[2];
                 //Qcb[3] = (r23 + r32)/(4.f*Qcb[2]);
         }
         else if(Qcb_q30[3] >= Qcb_q30[0] && Qcb_q30[3] >= Qcb_q30[1] && Qcb_q30[3] >= Qcb_q30[2]) //Qcb[3] is max
         {
                tmp = inv_icm20948_convert_inverse_q30_fxp(Qcb_q30[3], &pow2);
                shift = 30 - pow2 + 1;
		        Qcb_q30[0] = (long)(((long long)(r12 - r21) * tmp) >> shift) ;
		        Qcb_q30[1] = (long)(((long long)(r31 + r13) * tmp) >> shift) ;
		        Qcb_q30[2] = (long)(((long long)(r23 + r32) * tmp) >> shift) ;
                 //Qcb[0] = (r12 - r21)/(4.f*Qcb[3]);
                 //Qcb[1] = (r31 + r13)/(4.f*Qcb[3]);
                 //Qcb[2] = (r23 + r32)/(4.f*Qcb[3]);
                 //Qcb[3] = Qcb[3];
         }
         else
         {
                // printf('coding error\n'); //error
             Qcb_q30[0] = 1L<<30;
             Qcb_q30[1] = 0L;
             Qcb_q30[2] = 0L;
             Qcb_q30[3] = 0L;
             return;
         }

        // Normalize
        // compute inverse square root, using first order taylor series
        // Here temp aligns with row 8
        temp[1] = (long)(((long long)Qcb_q30[0] * Qcb_q30[0] +
                          (long long)Qcb_q30[1] * Qcb_q30[1] +
                          (long long)Qcb_q30[2] * Qcb_q30[2] +
                          (long long)Qcb_q30[3] * Qcb_q30[3]) >> 30);
        temp[2] = temp[1] >> 1; // Multiply by 2^29
        temp[0] = (1L<<30) + (1L<<29) - temp[2];

        // Normalize
        Qcb_q30[0] = inv_icm20948_convert_mult_q30_fxp(temp[0], Qcb_q30[0]);
        Qcb_q30[1] = inv_icm20948_convert_mult_q30_fxp(temp[0], Qcb_q30[1]);
        Qcb_q30[2] = inv_icm20948_convert_mult_q30_fxp(temp[0], Qcb_q30[2]);
        Qcb_q30[3] = inv_icm20948_convert_mult_q30_fxp(temp[0], Qcb_q30[3]);
}

long inv_icm20948_convert_sqrt_q30_fxp(long x_q30)
{
    long sqrtx;
    int pow2;

    if (x_q30 <= 0L) {
        sqrtx = 0L;
        return sqrtx;
    }
    sqrtx = inv_icm20948_convert_inv_sqrt_q30_fxp(x_q30, &pow2); // invsqrtx

    sqrtx = inv_icm20948_convert_mult_q30_fxp(x_q30, sqrtx);

power_up:
    if (pow2 > 0) {
        sqrtx = 2*sqrtx;
        pow2=pow2-1;
        goto power_up;
    }
power_down:
    if (pow2 < 0) {
        sqrtx = sqrtx/2;
        pow2=pow2+1;
        goto power_down;
    }

    return sqrtx;
}

long inv_icm20948_convert_inv_sqrt_q30_fxp(long x_q30, int *pow2)
{
    long oneoversqrt2 = 759250125L; // int32(2^30*1/sqrt(2))
    long oneandhalf = 1610612736L; // int32(1.5*2^30);
    long upperlimit = 1488522236; // int32(log(4)*2^30);
    long lowerlimit = 744261118; // int32(log(2)*2^30); 
    long xx, x0_2, invsqrtx;

    *pow2 = 0;
	if (x_q30 <= 0) {
        return 1L<<30;
	}

    xx = x_q30;
    if (xx > upperlimit) {
downscale:
        if (xx > upperlimit) {
            xx = xx/2;
            *pow2 = *pow2 - 1;
            goto downscale;
        }
    }

    if (xx < lowerlimit) {
upscale:
        if (xx < lowerlimit) {
            xx = xx*2;
            *pow2 = *pow2 + 1;
            goto upscale;
        }
    }

    // 3 NR iterations. In some cases second and/or third iteration may not be needed, however
    // for code simplicity always iterate three times. Fourth iteration is below bit precision.
    x0_2 = xx >>1;
    xx = oneandhalf - x0_2;
    xx = inv_icm20948_convert_mult_q30_fxp( xx, ( oneandhalf - inv_icm20948_convert_mult_q30_fxp(x0_2, inv_icm20948_convert_mult_q30_fxp(xx,xx) ) ) );
    xx = inv_icm20948_convert_mult_q30_fxp( xx, ( oneandhalf - inv_icm20948_convert_mult_q30_fxp(x0_2, inv_icm20948_convert_mult_q30_fxp(xx,xx) ) ) );

    if (*pow2 & 1) { // This checks if the number is even or odd.
        *pow2 = (*pow2>>1) + 1; // Account for sqrt(2) in denominator
        invsqrtx = (inv_icm20948_convert_mult_q30_fxp(xx,oneoversqrt2));
    }
    else {
        *pow2 = *pow2>>1;
        invsqrtx =  xx;
    }

    return invsqrtx;
}

long inv_icm20948_convert_inverse_q30_fxp(long x_q30, int *pow2)
{
    long y;
    int negx;

	if (x_q30 == 0) {
		y = 0L;
        *pow2 = 0;
		return y;
	}

    negx=0;
    if (x_q30 < 0 ) {
        if (x_q30 == INT32_MIN)
            x_q30 = INT32_MAX;
        else
            x_q30 = -x_q30;
        negx = 1;
    }

    y = inv_icm20948_convert_inv_sqrt_q30_fxp (x_q30, pow2); // sqrt(y)
    if (y > 1518500249L) // y > int32(sqrt(2) -1 : Largest number that won't overflow q30 multiplication of y*y
        y = INT32_MAX;
    else
        y = inv_icm20948_convert_mult_q30_fxp(y, y);
    *pow2 = *pow2*2;  // Must double exponent due to multiply 

    if (negx)
        y=-y;
    return y;
}

void inv_icm20948_convert_matrix_to_quat_flt(float *R, float *q)
{
	float r11,r12,r13, r21,r22,r23, r31,r32,r33;

	r11 = R[0]; //assume matrix is stored row wise first, that is rot[1] is row 1, col 2
	r12 = R[1];
	r13 = R[2];

	r21 = R[3];
	r22 = R[4];
	r23 = R[5];

	r31 = R[6];
	r32 = R[7];
	r33 = R[8];

	q[0] = (1.f + r11 + r22 + r33) / 4.f;
	q[1] = (1.f + r11 - r22 - r33) / 4.f;
	q[2] = (1.f - r11 + r22 - r33) / 4.f;
	q[3] = (1.f - r11 - r22 + r33) / 4.f;

	if(q[0] < 0.0f) q[0] = 0.0f;
	if(q[1] < 0.0f) q[1] = 0.0f;
	if(q[2] < 0.0f) q[2] = 0.0f;
	if(q[3] < 0.0f) q[3] = 0.0f;
	q[0] = sqrtf(q[0]);
	q[1] = sqrtf(q[1]);
	q[2] = sqrtf(q[2]);
	q[3] = sqrtf(q[3]);

	/* Above paragraph could be reduced in :
	q[0] =(q[0] < 0.0f) ? q[0] = 0.0f : sqrtf(q[0]);
	q[1] =(q[1] < 0.0f) ? q[1] = 0.0f : sqrtf(q[1]);
	q[2] =(q[2] < 0.0f) ? q[2] = 0.0f : sqrtf(q[2]);
	q[3] =(q[3] < 0.0f) ? q[3] = 0.0f : sqrtf(q[3]);
	*/
	
	if(q[0] >= q[1] && q[0] >= q[2] && q[0] >= q[3]) //q[0] is max
	{
		 q[1] = (r23 - r32)/(4.f*q[0]);
		 q[2] = (r31 - r13)/(4.f*q[0]);
		 q[3] = (r12 - r21)/(4.f*q[0]);
	}
	else if(q[1] >= q[0] && q[1] >= q[2] && q[1] >= q[3]) //q[1] is max
	{
		 q[0] = (r23 - r32)/(4.f*q[1]);
		 q[2] = (r12 + r21)/(4.f*q[1]);
		 q[3] = (r31 + r13)/(4.f*q[1]);
	}
	else if(q[2] >= q[0] && q[2] >= q[1] && q[2] >= q[3]) //q[2] is max
	{
		 q[0] = (r31 - r13)/(4.f*q[2]);
		 q[1] = (r12 + r21)/(4.f*q[2]);
		 q[3] = (r23 + r32)/(4.f*q[2]);
	}
	else if(q[3] >= q[0] && q[3] >= q[1] && q[3] >= q[2]) //q[3] is max
	{
		 q[0] = (r12 - r21)/(4.f*q[3]);
		 q[1] = (r31 + r13)/(4.f*q[3]);
		 q[2] = (r23 + r32)/(4.f*q[3]);
	}
}

long inv_icm20948_convert_mult_qfix_fxp(long a, long b, unsigned char qfix)
{
    long long temp;
    long result;
    temp = (long long)a * b;
    result = (long)(temp >> qfix);
    return result;
}

long invn_convert_mult_q29_fxp(long a_q29, long b_q29)
{
	long long temp;
	long result;
	temp = (long long)a_q29 * b_q29;
	result = (long)(temp >> 29);
	return result;

}

void inv_icm20948_convert_quat_to_col_major_matrix_fxp(const long *quat_q30, long *rot_q30)
{
	//Use q29 in order to skip a multiplication by 2
    rot_q30[0] =
        invn_convert_mult_q29_fxp(quat_q30[1], quat_q30[1]) + invn_convert_mult_q29_fxp(quat_q30[0], quat_q30[0]) - 1073741824L;
    rot_q30[1] =
        invn_convert_mult_q29_fxp(quat_q30[1], quat_q30[2]) - invn_convert_mult_q29_fxp(quat_q30[3], quat_q30[0]);
    rot_q30[2] =
        invn_convert_mult_q29_fxp(quat_q30[1], quat_q30[3]) + invn_convert_mult_q29_fxp(quat_q30[2], quat_q30[0]);
    rot_q30[3] =
        invn_convert_mult_q29_fxp(quat_q30[1], quat_q30[2]) + invn_convert_mult_q29_fxp(quat_q30[3], quat_q30[0]);
    rot_q30[4] =
        invn_convert_mult_q29_fxp(quat_q30[2], quat_q30[2]) + invn_convert_mult_q29_fxp(quat_q30[0], quat_q30[0]) - 1073741824L;
    rot_q30[5] =
        invn_convert_mult_q29_fxp(quat_q30[2], quat_q30[3]) - invn_convert_mult_q29_fxp(quat_q30[1], quat_q30[0]);
    rot_q30[6] =
        invn_convert_mult_q29_fxp(quat_q30[1], quat_q30[3]) - invn_convert_mult_q29_fxp(quat_q30[2], quat_q30[0]);
    rot_q30[7] =
        invn_convert_mult_q29_fxp(quat_q30[2], quat_q30[3]) + invn_convert_mult_q29_fxp(quat_q30[1], quat_q30[0]);
    rot_q30[8] =
        invn_convert_mult_q29_fxp(quat_q30[3], quat_q30[3]) + invn_convert_mult_q29_fxp(quat_q30[0], quat_q30[0]) - 1073741824L;
}

long invn_convert_mult_q15_fxp(long a_q15, long b_q15)
{
	long out = (long)(((long long)a_q15 * (long long)b_q15) >> 15);
	return out;
}

long invn_convert_inv_sqrt_q15_fxp(long x_q15)
{
    long oneoversqrt2 = 23170L; // int32(2^15*1/sqrt(2))
    long oneandhalf = 49152L; // int32(1.5*2^15);
    long upperlimit = 45426; // int32(log(4)*2^15);
    long lowerlimit = 22713; // int32(log(2)*2^15); 
    long xx, x0_2, invsqrtx;
    int pow2;

    if (x_q15 <= 0)
        return 0L;

    pow2 = 0;
    xx = x_q15;
    if (xx > upperlimit) {
downscale:
        if (xx > upperlimit) {
            xx = xx/2;
            pow2 = pow2 - 1;
            goto downscale;
        }
        goto newton_raphson;
    }

    if (xx < lowerlimit) {
upscale:
        if (xx < lowerlimit) {
            xx = xx*2;
            pow2 = pow2 + 1;
            goto upscale;
        }
        goto newton_raphson;
    }

newton_raphson:
    // 3 NR iterations. In some cases second and/or third iteration may not be needed, however
    // for code simplicity always iterate three times. Fourth iteration is below bit precision.
    x0_2 = xx >>1;
    xx = oneandhalf - x0_2;
    xx = invn_convert_mult_q15_fxp( xx, ( oneandhalf - invn_convert_mult_q15_fxp(x0_2, invn_convert_mult_q15_fxp(xx,xx) ) ) );
    xx = invn_convert_mult_q15_fxp( xx, ( oneandhalf - invn_convert_mult_q15_fxp(x0_2, invn_convert_mult_q15_fxp(xx,xx) ) ) );

    if (pow2 & 1) { // This checks if the number is even or odd.
        pow2 = (pow2>>1) + 1; // Account for sqrt(2) in denominator
        invsqrtx = (invn_convert_mult_q15_fxp(xx,oneoversqrt2));
    }
    else {
        pow2 = pow2>>1;
        invsqrtx =  xx;
    }

    if (pow2 < 0)
        invsqrtx = invsqrtx>>ABS(pow2);
    else if (pow2>0)
        invsqrtx = invsqrtx <<pow2;

    return invsqrtx;
}

long invn_convert_inverse_q15_fxp(long x_q15)
{
    long y;
    int negx;

	if (x_q15 == 0) {
		y = 0L;
		return y;
	}

    negx=0;
    if (x_q15 < 0 ) {
        x_q15 = -x_q15;
        negx = 1;
    }

	if(x_q15 >= 1073741824L) { // 2^15 in Q15; underflow number
        if (negx)
            y=-1L;
        else
            y = 1L;
		return y;
	}

    y = invn_convert_inv_sqrt_q15_fxp(x_q15); // sqrt(y)
    y = invn_convert_mult_q15_fxp(y, y);

    if (negx)
        y=-y;
    return y;
}

long inv_icm20948_math_atan2_q15_fxp(long y_q15, long x_q15)
{
    long absy, absx, maxABS, tmp, tmp2, tmp3, Z, angle;
    static long constA7[4] = {32740, -10503,  4751, -1254}; // int32(2^15*[0.999133448222780 -0.320533292381664 0.144982490144465,-0.038254464970299]); %7th order
    static long PI15 = 102944; // int32(2^15*pi): pi in Q15

    absx=ABS(x_q15);
    absy=ABS(y_q15);

    maxABS=MAX(absx, absy);
    // SCALE arguments down to protect from roundoff loss due to 1/x operation.
    //% Threshold for scaling found by numericaly simulating arguments
    //% to yield optimal (minimal) error of less than 0.01 deg through
    //% entire range (for Chebycheff order 7).
//    while ( maxABS >> 13) {  --> Or it can be done this way if DMP code is more efficient
    while ( maxABS > 8192L) {
            maxABS=maxABS/2;
            absx=absx/2;
            absy=absy/2;
    }

    {
        if (absx >= absy) // (0, pi/4]: tmp = abs(y)/abs(x);
            tmp = invn_convert_mult_q15_fxp(absy, invn_convert_inverse_q15_fxp(absx));
        else             // (pi/4, pi/2): tmp = abs(x)/abs(y);
            tmp = invn_convert_mult_q15_fxp(absx, invn_convert_inverse_q15_fxp(absy));

        tmp2=invn_convert_mult_q15_fxp(tmp, tmp);
         // Alternatively:
        tmp3 = invn_convert_mult_q15_fxp(constA7[3], tmp2);
        tmp3 = invn_convert_mult_q15_fxp(constA7[2] + tmp3, tmp2);
        tmp3 = invn_convert_mult_q15_fxp(constA7[1] + tmp3, tmp2);
        Z    = invn_convert_mult_q15_fxp(constA7[0] + tmp3, tmp);

        if (absx < absy)
            Z = PI15/2 - Z;

        if (x_q15 < 0) { // second and third quadrant
            if (y_q15 < 0)
                Z = -PI15 + Z;
            else
                Z = PI15 - Z;
        }
        else { // fourth quadrant
            if (y_q15 < 0)
                Z = -Z;
        }
        angle = Z; // Note the result is angle in radians, expressed in Q15.
    }
    return angle;
}

uint8_t *inv_icm20948_convert_int16_to_big8(int16_t x, uint8_t *big8)
{
    big8[0] = (uint8_t)((x >> 8) & 0xff);
    big8[1] = (uint8_t)(x & 0xff);
    return big8;
}

uint8_t *inv_icm20948_convert_int32_to_big8(int32_t x, uint8_t *big8)
{
    big8[0] = (uint8_t)((x >> 24) & 0xff);
    big8[1] = (uint8_t)((x >> 16) & 0xff);
    big8[2] = (uint8_t)((x >> 8) & 0xff);
    big8[3] = (uint8_t)(x & 0xff);
    return big8;
}

int32_t inv_icm20948_convert_big8_to_int32(const uint8_t *big8)
{
    int32_t x;
    x = ((int32_t)big8[0] << 24) | ((int32_t)big8[1] << 16) | ((int32_t)big8[2] << 8)
        | ((int32_t)big8[3]);
    return x;
}

int inv_icm20948_mpu_set_FIFO_RST_Diamond(struct inv_icm20948 * s, unsigned char value)
{
	int result = 0;
	unsigned char reg;

	result |= inv_icm20948_read_mems_reg(s, REG_FIFO_RST, 1, &reg);
    
	reg &= 0xe0;
	reg |= value;
	result |= inv_icm20948_write_mems_reg(s, REG_FIFO_RST, 1, &reg);
    
	return result;
}

int inv_icm20948_identify_interrupt(struct inv_icm20948 * s, short *int_read)
{
	unsigned char int_status;
    int result=0 ;
    
    if(int_read)
        *int_read = 0;
    
    result = inv_icm20948_read_mems_reg(s, REG_INT_STATUS, 1, &int_status);
    if(int_read)
        *int_read = int_status;

    result = inv_icm20948_read_mems_reg(s, REG_DMP_INT_STATUS, 1, &int_status); // DMP_INT_STATUS
	if(int_read)
		*int_read |= (int_status << 8);
    
    /*if(wake_on_motion_enabled) {
        result = inv_icm20948_read_mems_reg(s, REG_INT_STATUS, 1, &int_status);//INT_STATUS
        if(result)
            return result;
        *int_read |= reg_data[1];
    }*/
    /*
     * We do not need to handle FIFO overflow here. 
     * When we read FIFO_SIZE we can determine if FIFO overflow has occured.
     */
    //result = inv_icm20948_read_mems_reg(s, 0x1B, 1, &int_status);
    
	return result;
}

/**
* @internal
* @brief   Get the length from the fifo
*
* @param[out] len amount of data currently stored in the fifo.
*
* @return MPU_SUCCESS or non-zero error code.
**/
int dmp_get_fifo_length(struct inv_icm20948 * s, uint_fast16_t * len )
{
	unsigned char fifoBuf[2];
	int result = 0;
    
	if (NULL == len)
		return -1;
    
	/*---- read the 2 'count' registers and
	burst read the data from the FIFO ----*/
	result = inv_icm20948_read_mems_reg(s, REG_FIFO_COUNT_H, 2, fifoBuf);
	if (result) 
	{
		s->fifo_info.fifoError = -1;
		*len = 0;
		return result;
	}
    
	*len = (uint_fast16_t) (fifoBuf[0] << 8);
	*len += (uint_fast16_t) (fifoBuf[1]);

	return result;
}

/**
*  @internal
*  @brief  Clears the FIFO status and its content.
*  @note   Halt the DMP writing into the FIFO for the time
*          needed to reset the FIFO.
*  @return MPU_SUCCESS if successful, a non-zero error code otherwise.
*/
int dmp_reset_fifo(struct inv_icm20948 * s)
{
    uint_fast16_t len = HARDWARE_FIFO_SIZE;
	unsigned char tries = 0;
	int result = 0;
    
	while (len != 0 && tries < 6) 
	{ 
		s->base_state.user_ctrl &= (~BIT_FIFO_EN);
		s->base_state.user_ctrl &= (~BIT_DMP_EN);
		result |= inv_icm20948_write_single_mems_reg(s, REG_USER_CTRL, s->base_state.user_ctrl);
		result |= inv_icm20948_mpu_set_FIFO_RST_Diamond(s, 0x1f);
		result |= inv_icm20948_mpu_set_FIFO_RST_Diamond(s, 0x1e);
        
		// Reset overflow flag
		s->fifo_info.fifo_overflow = 0;
        
		result |= dmp_get_fifo_length(s, &len);
		if (result) 
			return result;
        
		tries++;
	}
    
	s->base_state.user_ctrl |= BIT_FIFO_EN;
	s->base_state.user_ctrl |= BIT_DMP_EN;
	result |= inv_icm20948_write_single_mems_reg(s, REG_USER_CTRL, s->base_state.user_ctrl);
    
	return result;
}

/**
*  @internal
*  @brief  Read data from the fifo
*
*  @param[out] data Location to store the date read from the fifo
*  @param[in] len   Amount of data to read out of the fifo
*
*  @return MPU_SUCCESS or non-zero error code
**/
int dmp_read_fifo(struct inv_icm20948 * s, unsigned char *data, uint_fast16_t len)
{
	int result;
    uint_fast16_t bytesRead = 0;

    while (bytesRead<len) 
    {
        unsigned short thisLen = MIN(INV_MAX_SERIAL_READ, len-bytesRead);
        
        result = inv_icm20948_read_mems_reg(s, REG_FIFO_R_W, thisLen, &data[bytesRead]);
        if (result)
		{
			dmp_reset_fifo(s);
			s->fifo_info.fifoError = -1;
			return result;
		}
        
        bytesRead += thisLen;
    }

	return result;
}

/**
*  @internal
*  @brief  used to get the FIFO data.
*  @param  length
*              Max number of bytes to read from the FIFO that buffer is still able to sustain.
*  @param  buffer Reads up to length into the buffer.
*
*  @return number of bytes of read.
**/
uint_fast16_t dmp_get_fifo_all(struct inv_icm20948 * s, uint_fast16_t length, unsigned char *buffer, int *reset)
{
	int result;
	uint_fast16_t in_fifo;
    
	if(reset)
		*reset = 0;
   
	result = dmp_get_fifo_length(s, &in_fifo);
	if (result) {
		s->fifo_info.fifoError = result;
		return 0;
	}
    
	// Nothing to read
	if (in_fifo == 0){
		if(reset)
			*reset = 1;
		return 0;
	}

	/* Check if buffer is able to be filled in with in_fifo bytes */
	if (in_fifo > length) {
		dmp_reset_fifo(s);
		s->fifo_info.fifoError = -1;
		if(reset)
			*reset = 1;
		return 0;
	}

	result = dmp_read_fifo(s, buffer, in_fifo);
	if (result) {
		s->fifo_info.fifoError = result;
		return 0;
	}
	return in_fifo;
}

/** Determines the packet size by decoding the header. Both header and header2 are set. header2 is set to zero
*   if it doesn't exist. sample_cnt_array is filled in if not null with number of samples expected for each sensor
*/
uint_fast16_t get_packet_size_and_samplecnt(unsigned char *data, unsigned short *header, unsigned short *header2, unsigned short * sample_cnt_array)
{
	int sz = HEADER_SZ; // 2 for header
    
	*header = (((unsigned short)data[0])<<8) | data[1];

	if (*header & ACCEL_SET) {
		sz += ACCEL_DATA_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_ACCELEROMETER]++;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_RAW_ACCELEROMETER]++;
	}
    
	if (*header & GYRO_SET) {
		sz += GYRO_DATA_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED]++;
		sz += GYRO_BIAS_DATA_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_GYROSCOPE]++;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_RAW_GYROSCOPE]++;
	}
 
	if (*header & CPASS_SET) {
		sz += CPASS_DATA_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED]++;
	}
    
	if (*header & ALS_SET) {
		sz += ALS_DATA_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_LIGHT]++;
	}

	if (*header & QUAT6_SET) {
		sz += QUAT6_DATA_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_GAME_ROTATION_VECTOR]++;
	}

	if (*header & QUAT9_SET) {
		sz += QUAT9_DATA_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_ROTATION_VECTOR]++;
	}

	if (*header & PQUAT6_SET) 
		sz += PQUAT6_DATA_SZ;
    
	if (*header & GEOMAG_SET) {
		sz += GEOMAG_DATA_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR]++;
	}
    
	if (*header & CPASS_CALIBR_SET) {
		sz += CPASS_CALIBR_DATA_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_GEOMAGNETIC_FIELD]++;
	}

	if (*header & PED_STEPDET_SET) {
		sz += PED_STEPDET_TIMESTAMP_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_STEP_DETECTOR]++;
	}

	if (*header & HEADER2_SET) {
		*header2 = (((unsigned short)data[2])<<8) | data[3];
		sz += HEADER2_SZ;
	} else {
		*header2 = 0;
	}
    
	if (*header2 & ACCEL_ACCURACY_SET) {
		sz += ACCEL_ACCURACY_SZ;
	}
	if (*header2 & GYRO_ACCURACY_SET) {
		sz += GYRO_ACCURACY_SZ;
	}
	if (*header2 & CPASS_ACCURACY_SET) {
		sz += CPASS_ACCURACY_SZ;
	}
	if (*header2 & FLIP_PICKUP_SET) {
		sz += FLIP_PICKUP_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_FLIP_PICKUP]++;
	}
	if (*header2 & ACT_RECOG_SET) {
		sz += ACT_RECOG_SZ;
		if (sample_cnt_array)
			sample_cnt_array[ANDROID_SENSOR_ACTIVITY_CLASSIFICATON]++;
	}
	sz += ODR_CNT_GYRO_SZ;

	return sz;
}

int check_fifo_decoded_headers(unsigned short header, unsigned short header2)
{
	unsigned short header_bit_mask = 0;
	unsigned short header2_bit_mask = 0;
	
	// at least 1 bit must be set
	if (header == 0)
		return -1;
	
	header_bit_mask |= ACCEL_SET;
	header_bit_mask |= GYRO_SET;
	header_bit_mask |= CPASS_SET;
	header_bit_mask |= ALS_SET;
	header_bit_mask |= QUAT6_SET;
	header_bit_mask |= QUAT9_SET;
	header_bit_mask |= PQUAT6_SET;
	header_bit_mask |= GEOMAG_SET;
	header_bit_mask |= GYRO_CALIBR_SET;
	header_bit_mask |= CPASS_CALIBR_SET;
	header_bit_mask |= PED_STEPDET_SET;
	header_bit_mask |= HEADER2_SET;
	
	if (header & ~header_bit_mask)
		return -1;
	
	// at least 1 bit must be set if header 2 is set
	if (header & HEADER2_SET) {
		header2_bit_mask |= ACCEL_ACCURACY_SET;
		header2_bit_mask |= GYRO_ACCURACY_SET;
		header2_bit_mask |= CPASS_ACCURACY_SET;
		header2_bit_mask |= FLIP_PICKUP_SET;
		header2_bit_mask |= ACT_RECOG_SET;
		if (header2 == 0)
			return -1;
		if (header2 & ~header2_bit_mask)
			return -1;
	}

    return 0;
}


    
/** Determine number of samples present in SW FIFO fifo_data containing fifo_size bytes to be analyzed. Total number
* of samples filled in total_sample_cnt, number of samples per sensor filled in sample_cnt_array array
*/
int extract_sample_cnt(struct inv_icm20948 * s, int fifo_size, unsigned short * total_sample_cnt, unsigned short * sample_cnt_array)
{
	// Next SW FIFO index to be parsed
	int fifo_idx = 0;
	
	while (fifo_idx < fifo_size) {
		unsigned short header;
		unsigned short header2;
		int need_sz = get_packet_size_and_samplecnt(&fifo_data[fifo_idx], &header, &header2, sample_cnt_array);
		
		// Guarantee there is a full packet before continuing to decode the FIFO packet
		if (fifo_size-fifo_idx < need_sz)
			goto endSuccess;
		
		// Decode any error
		if (check_fifo_decoded_headers(header, header2)) {
			// in that case, stop processing, we might have overflowed so following bytes are non sense
			dmp_reset_fifo(s);
			return -1;
		}
		
		fifo_idx += need_sz;
		
		// One sample found, increment total sample counter
		(*total_sample_cnt)++;
	}

endSuccess:
	// Augmented sensors are not part of DMP FIFO, they are computed by DMP driver based on GRV or RV presence in DMP FIFO
	// So their sample counts must rely on GRV and RV sample counts
	if (sample_cnt_array) {
		sample_cnt_array[ANDROID_SENSOR_GRAVITY] += sample_cnt_array[ANDROID_SENSOR_GAME_ROTATION_VECTOR];
		sample_cnt_array[ANDROID_SENSOR_LINEAR_ACCELERATION] += sample_cnt_array[ANDROID_SENSOR_GAME_ROTATION_VECTOR];
		sample_cnt_array[ANDROID_SENSOR_ORIENTATION] += sample_cnt_array[ANDROID_SENSOR_ROTATION_VECTOR];
	}

	return 0;
}

int inv_icm20948_fifo_swmirror(struct inv_icm20948 * s, int *fifo_sw_size, unsigned short * total_sample_cnt, unsigned short * sample_cnt_array)
{
	int reset=0; 

	*total_sample_cnt = 0;

	// Mirror HW FIFO into local SW FIFO, taking into account remaining *fifo_sw_size bytes still present in SW FIFO
	if (*fifo_sw_size < HARDWARE_FIFO_SIZE ) {
		*fifo_sw_size += dmp_get_fifo_all(s, (HARDWARE_FIFO_SIZE - *fifo_sw_size),&fifo_data[*fifo_sw_size],&reset);

		if (reset)
			goto error;
	}

	// SW FIFO is mirror, we can now parse it to extract total number of samples and number of samples per sensor
	if (extract_sample_cnt(s, *fifo_sw_size, total_sample_cnt, sample_cnt_array))
			goto error;

	return MPU_SUCCESS;
	
error:
	*fifo_sw_size = 0;
	return -1;
	
}

int inv_icm20948_fifo_pop(struct inv_icm20948 * s, unsigned short *user_header, unsigned short *user_header2, int *fifo_sw_size)  
{
	int need_sz=0; // size in bytes of packet to be analyzed from FIFO
	unsigned char *fifo_ptr = fifo_data; // pointer to next byte in SW FIFO to be parsed
    
	if (*fifo_sw_size > 3) {
		// extract headers and number of bytes requested by next sample present in FIFO
		need_sz = get_packet_size_and_samplecnt(fifo_data, &fd.header, &fd.header2, 0);

		// Guarantee there is a full packet before continuing to decode the FIFO packet
		if (*fifo_sw_size < need_sz) {
		    return s->fifo_info.fifoError;
		}

		fifo_ptr += HEADER_SZ;        
		if (fd.header & HEADER2_SET)
			fifo_ptr += HEADER2_SZ;        

		// extract payload data from SW FIFO
		fifo_ptr += inv_icm20948_inv_decode_one_ivory_fifo_packet(s, &fd, fifo_ptr);        

		// remove first need_sz bytes from SW FIFO
		*fifo_sw_size -= need_sz;
		if(*fifo_sw_size)
			memmove(fifo_data, &fifo_data[need_sz], *fifo_sw_size);// Data left in FIFO

		*user_header = fd.header;
		*user_header2 = fd.header2;
	}

	return MPU_SUCCESS;
}

/** Decodes one packet of data from Ivory FIFO
* @param[in] fd Structure to be filled out with data. Assumes header and header2 are already set inside.
* @param[in] fifo_ptr FIFO data, points to just after any header information
* @return Returns the number of bytes consumed in FIFO data.
*/
int inv_icm20948_inv_decode_one_ivory_fifo_packet(struct inv_icm20948 * s, struct inv_fifo_decoded_t *fd, const unsigned char *fifo_ptr)
{
    const unsigned char *fifo_ptr_start = fifo_ptr;  
	short odr_cntr;
    if (fd->header & ACCEL_SET) {
        // do not cast data here, do that when you use it
        inv_decode_3_16bit_elements(fd->accel_s, fifo_ptr);
        fd->accel[0] = fd->accel_s[0] << 15;
        fd->accel[1] = fd->accel_s[1] << 15;
        fd->accel[2] = fd->accel_s[2] << 15;
        fifo_ptr += ACCEL_DATA_SZ;
    }

    if (fd->header & GYRO_SET) {
        inv_decode_3_16bit_elements(fd->gyro, fifo_ptr);
        fifo_ptr += GYRO_DATA_SZ;
        inv_decode_3_16bit_elements(fd->gyro_bias, fifo_ptr);
        fifo_ptr += GYRO_BIAS_DATA_SZ;
    }

    if (fd->header & CPASS_SET) {
        inv_decode_3_16bit_elements(fd->cpass_raw_data, fifo_ptr);
        inv_icm20948_apply_raw_compass_matrix(s, fd->cpass_raw_data, fd->compass);
        memcpy( fd->cpass_calibr_6chars, fifo_ptr, 6*sizeof(unsigned char));
        fifo_ptr += CPASS_DATA_SZ;
    }

    if(fd->header & ALS_SET) {
        fifo_ptr += ALS_DATA_SZ;
    }

    if (fd->header & QUAT6_SET) {
        inv_decode_3_32bit_elements(fd->dmp_3e_6quat, fifo_ptr);
        fifo_ptr += QUAT6_DATA_SZ;
    }

    if (fd->header & QUAT9_SET) {
        inv_decode_3_32bit_elements(fd->dmp_3e_9quat, fifo_ptr);
        fd->dmp_rv_accuracyQ29 = ((0xff & fifo_ptr[12]) << 24) | ((0xff & fifo_ptr[13]) << 16);
        fifo_ptr += QUAT9_DATA_SZ;
    }

    if (fd->header & PED_STEPDET_SET) {
        fd->ped_step_det_ts = ((0xff & fifo_ptr[0]) << 24) | ((0xff & fifo_ptr[1]) << 16) | ((0xff & fifo_ptr[2]) << 8) | (0xff & fifo_ptr[3]);
        fifo_ptr += PED_STEPDET_TIMESTAMP_SZ;
    }

    if (fd->header & GEOMAG_SET) {
        inv_decode_3_32bit_elements(fd->dmp_3e_geomagquat, fifo_ptr);
        fd->dmp_geomag_accuracyQ29 = ((0xff & fifo_ptr[12]) << 24) | ((0xff & fifo_ptr[13]) << 16);
        fifo_ptr += GEOMAG_DATA_SZ;
    }

    if(fd->header & PRESSURE_SET) {
        fifo_ptr += PRESSURE_DATA_SZ;
    }
    if (fd->header & CPASS_CALIBR_SET) {
        inv_decode_3_32bit_elements(fd->cpass_calibr, fifo_ptr);
        memcpy( fd->cpass_calibr_12chars, fifo_ptr, 12*sizeof(unsigned char));
        fifo_ptr += CPASS_CALIBR_DATA_SZ;
    }

    if (fd->header2 & ACCEL_ACCURACY_SET) {
        fd->accel_accuracy = ((0xff & fifo_ptr[0]) << 8) | (0xff & fifo_ptr[1]);
        fifo_ptr += ACCEL_ACCURACY_SZ;
    }
        
    if (fd->header2 & GYRO_ACCURACY_SET) {
        fd->gyro_accuracy = ((0xff & fifo_ptr[0]) << 8) | (0xff & fifo_ptr[1]);
        fifo_ptr += GYRO_ACCURACY_SZ;
    }
 
    if (fd->header2 & CPASS_ACCURACY_SET) {
        fd->cpass_accuracy = ((0xff & fifo_ptr[0]) << 8) | (0xff & fifo_ptr[1]);
        fifo_ptr += CPASS_ACCURACY_SZ;
    }

	if (fd->header2 & FLIP_PICKUP_SET) {
		fd->flip_pickup = ((0xff & fifo_ptr[0]) << 8) | (0xff & fifo_ptr[1]);
		fifo_ptr += FLIP_PICKUP_SZ;
	}
	
	if (fd->header2 & ACT_RECOG_SET) {
		fd->bac_state = ((0xff & fifo_ptr[0]) << 8) | (0xff & fifo_ptr[1]);
		fd->bac_ts     = ((0xff & fifo_ptr[2]) << 24) | ((0xff & fifo_ptr[3]) << 16) | ((0xff & fifo_ptr[4]) << 8) | (0xff & fifo_ptr[5]);
		fifo_ptr += ACT_RECOG_SZ;
	}

	odr_cntr = ((0xff & fifo_ptr[0]) << 8) | (0xff & fifo_ptr[1]);
	// odr_cntr_gyro is odr_cntr & 0xfff
	// 9KHz cnt is odr_cntr >> 12
	// not used for now, needed only for FSYNC purpose
	(void)odr_cntr;
	fifo_ptr += FOOTER_SZ;

    fd->new_data = 1; // Record a new data set

    return fifo_ptr-fifo_ptr_start;
}

int inv_icm20948_dmp_process_fifo(struct inv_icm20948 * s, int *left_in_fifo, unsigned short *user_header, unsigned short *user_header2, long *time_stamp)  
{
    int result = MPU_SUCCESS;
    int reset=0; 
    int need_sz=0;
    unsigned char *fifo_ptr = fifo_data;

    long long ts=0;

    if(!left_in_fifo)
        return -1;
    
    if (*left_in_fifo < HARDWARE_FIFO_SIZE ) 
    {
        *left_in_fifo += dmp_get_fifo_all(s, (HARDWARE_FIFO_SIZE - *left_in_fifo),&fifo_data[*left_in_fifo],&reset);
        //sprintf(test_str, "Left in FIFO: %d\r\n",*left_in_fifo);
        //print_command_console(test_str);
        if (reset) 
        {
            *left_in_fifo = 0;
            return -1;
        }
    }
    
    if (*left_in_fifo > 3) {
	// no need to extract number of sample per sensor for current function, so provide 0 as last parameter
        need_sz = get_packet_size_and_samplecnt(fifo_data, &fd.header, &fd.header2, 0);
        
        // Guarantee there is a full packet before continuing to decode the FIFO packet
        if (*left_in_fifo < need_sz) {
            result = s->fifo_info.fifoError;
            s->fifo_info.fifoError = 0;
            return result;
        }

        if(user_header)
            *user_header = fd.header;
        
        if(user_header2)
            *user_header2 = fd.header2;
        
        if (check_fifo_decoded_headers(fd.header, fd.header2)) { 
            // Decode error
            dmp_reset_fifo(s);
            *left_in_fifo = 0;
            return -1;
        }
        
        fifo_ptr += HEADER_SZ;
        
        if (fd.header & HEADER2_SET)
            fifo_ptr += HEADER2_SZ;        
        
        //time stamp 
        ts = inv_icm20948_get_tick_count();
        
        fifo_ptr += inv_icm20948_inv_decode_one_ivory_fifo_packet(s, &fd, fifo_ptr);

        if(time_stamp)
            *time_stamp = ts;
        
        /* Parse the data in the fifo, in the order of the data control register, starting with the MSB(accel)
        */
        
        
        *left_in_fifo -= need_sz;
        if (*left_in_fifo) 
            memmove(fifo_data, &fifo_data[need_sz], *left_in_fifo);// Data left in FIFO
    }

    return result;
}

void inv_decode_3_32bit_elements(long *out_data, const unsigned char *in_data)
{
    out_data[0] = ((long)(0xff & in_data[0]) << 24) | ((long)(0xff & in_data[1]) << 16) | ((long)(0xff & in_data[2]) << 8) | (0xff & in_data[3]);
    out_data[1] = ((long)(0xff & in_data[4]) << 24) | ((long)(0xff & in_data[5]) << 16) | ((long)(0xff & in_data[6]) << 8) | (0xff & in_data[7]);
    out_data[2] = ((long)(0xff & in_data[8]) << 24) | ((long)(0xff & in_data[9]) << 16) | ((long)(0xff & in_data[10]) << 8) | (0xff & in_data[11]);
}

void inv_decode_3_16bit_elements(short *out_data, const unsigned char *in_data)
{
    out_data[0] = ((short)(0xff & in_data[0]) << 8) | (0xff & in_data[1]);
    out_data[1] = ((short)(0xff & in_data[2]) << 8) | (0xff & in_data[3]);
    out_data[2] = ((short)(0xff & in_data[4]) << 8) | (0xff & in_data[5]);
}

int inv_icm20948_dmp_get_accel(long acl[3])
{
    if(!acl) return -1;
    memcpy( acl, fd.accel, 3*sizeof(long));
    return MPU_SUCCESS;
} 

int inv_icm20948_dmp_get_raw_gyro(short raw_gyro[3])
{
    if(!raw_gyro) return -1;
    raw_gyro[0] = fd.gyro[0];
    raw_gyro[1] = fd.gyro[1];
    raw_gyro[2] = fd.gyro[2];
    return MPU_SUCCESS;
}


int inv_icm20948_dmp_get_gyro_bias(short gyro_bias[3])
{
    if(!gyro_bias) return -1;  
    memcpy(gyro_bias, fd.gyro_bias, 3*sizeof(short)); 
    return MPU_SUCCESS;
}


int inv_icm20948_dmp_get_calibrated_gyro(signed long calibratedData[3], signed long raw[3], signed long bias[3])
{
    if(!calibratedData) return -1;  
    if(!raw) return -1;  
    if(!bias) return -1;  
    
    calibratedData[0] = raw[0] - bias[0];
    calibratedData[1] = raw[1] - bias[1];
    calibratedData[2] = raw[2] - bias[2];
    
    return MPU_SUCCESS;
}

int inv_icm20948_dmp_get_6quaternion(long quat[3])
{
    if(!quat) return -1;
    memcpy( quat, fd.dmp_3e_6quat, sizeof(fd.dmp_3e_6quat));            
    return MPU_SUCCESS;
}

int inv_icm20948_dmp_get_9quaternion(long quat[3])
{
    if(!quat) return -1;
    memcpy( quat, fd.dmp_3e_9quat, sizeof(fd.dmp_3e_9quat));            
    return MPU_SUCCESS;
}

int inv_icm20948_dmp_get_gmrvquaternion(long quat[3])
{
    if(!quat) return -1;
    memcpy( quat, fd.dmp_3e_geomagquat, sizeof(fd.dmp_3e_geomagquat));            
    return MPU_SUCCESS;
}

int inv_icm20948_dmp_get_raw_compass(long raw_compass[3])
{
    if(!raw_compass) return -1;
    memcpy( raw_compass, fd.compass, 3*sizeof(long)); 
    return MPU_SUCCESS;
}

int inv_icm20948_dmp_get_calibrated_compass(long cal_compass[3])
{
    if(!cal_compass) return -1;
    memcpy( cal_compass, fd.cpass_calibr, 3*sizeof(long));  
    return MPU_SUCCESS;
}

int inv_icm20948_dmp_get_bac_state(uint16_t *bac_state)
{
	if(!bac_state) return -1;
	*bac_state = fd.bac_state;
	return 0;
}

int inv_icm20948_dmp_get_bac_ts(long *bac_ts)
{
	if(!bac_ts) return -1;
	*bac_ts = fd.bac_ts;
	return 0;
}

int inv_icm20948_dmp_get_flip_pickup_state(uint16_t *flip_pickup)
{
	if(!flip_pickup) return -1;
	*flip_pickup = fd.flip_pickup;
	return 0;
}

/** Returns accuracy of accel.
 * @return Accuracy of accel with 0 being not accurate, and 3 being most accurate.
*/
int inv_icm20948_get_accel_accuracy(void)
{
	return fd.accel_accuracy;
}

/** Returns accuracy of gyro.
 * @return Accuracy of gyro with 0 being not accurate, and 3 being most accurate.
*/
int inv_icm20948_get_gyro_accuracy(void)
{
	return fd.gyro_accuracy;
}

/** Returns accuracy of compass.
 * @return Accuracy of compass with 0 being not accurate, and 3 being most accurate.
*/
int inv_icm20948_get_mag_accuracy(void)
{
	return fd.cpass_accuracy;
}

/** Returns accuracy of geomagnetic rotation vector.
 * @return Accuracy of GMRV in Q29.
*/
int inv_icm20948_get_gmrv_accuracy(void)
{
	return fd.dmp_geomag_accuracyQ29;
}

/** Returns accuracy of rotation vector.
 * @return Accuracy of RV in Q29.
*/
int inv_icm20948_get_rv_accuracy(void)
{
	return fd.dmp_rv_accuracyQ29;
}


/** @brief Set of flags for BAC state */
#define BAC_DRIVE   0x01
#define BAC_WALK    0x02
#define BAC_RUN     0x04
#define BAC_BIKE    0x08
#define BAC_TILT    0x10
#define BAC_STILL   0x20

/** @brief Conversion from DMP units to float format for compass scale */
#define DMP_UNIT_TO_FLOAT_COMPASS_CONVERSION      (1/(float)(1UL<<16))
//! Convert the \a value from QN value to float. \ingroup invn_macro
#define INVN_FXP_TO_FLT(value, shift)	( (float)  (int32_t)(value) / (float)(1ULL << (shift)) )

uint8_t sensor_type_2_android_sensor(enum inv_icm20948_sensor sensor)
{
	switch(sensor) {
	case INV_ICM20948_SENSOR_ACCELEROMETER:                 return ANDROID_SENSOR_ACCELEROMETER;
	case INV_ICM20948_SENSOR_GYROSCOPE:                     return ANDROID_SENSOR_GYROSCOPE;
	case INV_ICM20948_SENSOR_RAW_ACCELEROMETER:             return ANDROID_SENSOR_RAW_ACCELEROMETER;
	case INV_ICM20948_SENSOR_RAW_GYROSCOPE:                 return ANDROID_SENSOR_RAW_GYROSCOPE;
	case INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED:   return ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED;
	case INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED:        return ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED;
	case INV_ICM20948_SENSOR_ACTIVITY_CLASSIFICATON:        return ANDROID_SENSOR_ACTIVITY_CLASSIFICATON;
	case INV_ICM20948_SENSOR_STEP_DETECTOR:                 return ANDROID_SENSOR_STEP_DETECTOR;
	case INV_ICM20948_SENSOR_STEP_COUNTER:                  return ANDROID_SENSOR_STEP_COUNTER;
	case INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR:          return ANDROID_SENSOR_GAME_ROTATION_VECTOR;
	case INV_ICM20948_SENSOR_ROTATION_VECTOR:               return ANDROID_SENSOR_ROTATION_VECTOR;
	case INV_ICM20948_SENSOR_GEOMAGNETIC_ROTATION_VECTOR:   return ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR;
	case INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD:             return ANDROID_SENSOR_GEOMAGNETIC_FIELD;
	case INV_ICM20948_SENSOR_WAKEUP_SIGNIFICANT_MOTION:     return ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION;
	case INV_ICM20948_SENSOR_FLIP_PICKUP:                   return ANDROID_SENSOR_FLIP_PICKUP;
	case INV_ICM20948_SENSOR_WAKEUP_TILT_DETECTOR:          return ANDROID_SENSOR_WAKEUP_TILT_DETECTOR;
	case INV_ICM20948_SENSOR_GRAVITY:                       return ANDROID_SENSOR_GRAVITY;
	case INV_ICM20948_SENSOR_LINEAR_ACCELERATION:           return ANDROID_SENSOR_LINEAR_ACCELERATION;
	case INV_ICM20948_SENSOR_ORIENTATION:                   return ANDROID_SENSOR_ORIENTATION;
	case INV_ICM20948_SENSOR_B2S:                           return ANDROID_SENSOR_B2S;
	default:                                                return ANDROID_SENSOR_NUM_MAX;
	}
}

enum inv_icm20948_sensor inv_icm20948_sensor_android_2_sensor_type(int sensor)
{
	switch(sensor) {
	case ANDROID_SENSOR_ACCELEROMETER:                    return INV_ICM20948_SENSOR_ACCELEROMETER;
	case ANDROID_SENSOR_GYROSCOPE:                        return INV_ICM20948_SENSOR_GYROSCOPE;
	case ANDROID_SENSOR_RAW_ACCELEROMETER:                return INV_ICM20948_SENSOR_RAW_ACCELEROMETER;
	case ANDROID_SENSOR_RAW_GYROSCOPE:                    return INV_ICM20948_SENSOR_RAW_GYROSCOPE;
	case ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED:      return INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED;
	case ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED:           return INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED;
	case ANDROID_SENSOR_ACTIVITY_CLASSIFICATON:           return INV_ICM20948_SENSOR_ACTIVITY_CLASSIFICATON;
	case ANDROID_SENSOR_STEP_DETECTOR:                    return INV_ICM20948_SENSOR_STEP_DETECTOR;
	case ANDROID_SENSOR_STEP_COUNTER:                     return INV_ICM20948_SENSOR_STEP_COUNTER;
	case ANDROID_SENSOR_GAME_ROTATION_VECTOR:             return INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR;
	case ANDROID_SENSOR_ROTATION_VECTOR:                  return INV_ICM20948_SENSOR_ROTATION_VECTOR;
	case ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR:      return INV_ICM20948_SENSOR_GEOMAGNETIC_ROTATION_VECTOR;
	case ANDROID_SENSOR_GEOMAGNETIC_FIELD:                return INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD;
	case ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION:        return INV_ICM20948_SENSOR_WAKEUP_SIGNIFICANT_MOTION;
	case ANDROID_SENSOR_FLIP_PICKUP:                      return INV_ICM20948_SENSOR_FLIP_PICKUP;
	case ANDROID_SENSOR_WAKEUP_TILT_DETECTOR:             return INV_ICM20948_SENSOR_WAKEUP_TILT_DETECTOR;
	case ANDROID_SENSOR_GRAVITY:                          return INV_ICM20948_SENSOR_GRAVITY;
	case ANDROID_SENSOR_LINEAR_ACCELERATION:              return INV_ICM20948_SENSOR_LINEAR_ACCELERATION;
	case ANDROID_SENSOR_ORIENTATION:                      return INV_ICM20948_SENSOR_ORIENTATION;
	case ANDROID_SENSOR_B2S:                              return INV_ICM20948_SENSOR_B2S;
	default:                                              return INV_ICM20948_SENSOR_MAX;
	}
}

int skip_sensor(struct inv_icm20948 * s, unsigned char androidSensor)
{
	enum inv_icm20948_sensor icm20948_sensor_id = inv_icm20948_sensor_android_2_sensor_type(androidSensor);
	uint8_t skip_sample = s->skip_sample[icm20948_sensor_id];

	if (s->skip_sample[icm20948_sensor_id])
		s->skip_sample[icm20948_sensor_id]--;

	return skip_sample;
}

/* Identification related functions */
int inv_icm20948_get_whoami(struct inv_icm20948 * s, uint8_t * whoami)
{
	return inv_icm20948_read_reg_one(s, REG_WHO_AM_I, whoami);
}

void inv_icm20948_init_matrix(struct inv_icm20948 * s)
{
	// initialize chip to body
	s->s_quat_chip_to_body[0] = (1L<<30);
	s->s_quat_chip_to_body[1] = 0;
	s->s_quat_chip_to_body[2] = 0;
	s->s_quat_chip_to_body[3] = 0;
	//initialize mounting matrix
	memset(s->mounting_matrix, 0, sizeof(s->mounting_matrix));
	s->mounting_matrix[0] = 1;
	s->mounting_matrix[4] = 1;
	s->mounting_matrix[8] = 1;
	//initialize soft iron matrix
	s->soft_iron_matrix[0] = (1L<<30);
	s->soft_iron_matrix[4] = (1L<<30);
	s->soft_iron_matrix[8] = (1L<<30);

	inv_icm20948_set_chip_to_body_axis_quaternion(s, s->mounting_matrix, 0.0);
}

int inv_icm20948_init_structure(struct inv_icm20948 * s)
{
	int i;
	inv_icm20948_base_control_init(s);
	inv_icm20948_transport_init(s);
	inv_icm20948_augmented_init(s);
	//Init state
	s->set_accuracy = 0;
	s->new_accuracy = 0;
	for(i = 0; i < GENERAL_SENSORS_MAX; i ++)
		s->timestamp[inv_icm20948_sensor_android_2_sensor_type(i)] = 0;

	return 0;
}

int inv_icm20948_initialize(struct inv_icm20948 * s, const uint8_t *dmp3_image, uint32_t dmp3_image_size)
{
	if(s->serif.is_spi) {
		/* Hardware initialization */
		// No image to be loaded from flash, no pointer to pass.
		if (inv_icm20948_initialize_lower_driver(s, SERIAL_INTERFACE_SPI, dmp3_image, dmp3_image_size)) { 
			return -1;
		}
	}
	else {
		/* Hardware initialization */
		// No image to be loaded from flash, no pointer to pass.
		int rc = inv_icm20948_initialize_lower_driver(s, SERIAL_INTERFACE_I2C, dmp3_image, dmp3_image_size);
		if (rc) {
			return rc;
		}
	}
	return 0;
}

int inv_icm20948_init_scale(struct inv_icm20948 * s)
{
	/* Force accelero fullscale to 4g and gyr to 200dps */
	inv_icm20948_set_accel_fullscale(s, MPU_FS_4G);
	inv_icm20948_set_gyro_fullscale(s, MPU_FS_2000dps);

	return 0;
}

int inv_icm20948_set_fsr(struct inv_icm20948 * s, enum inv_icm20948_sensor sensor, const void * fsr)
{
	int result = 0;
	int * castedvalue = (int*) fsr;
	if((sensor == INV_ICM20948_SENSOR_RAW_ACCELEROMETER) ||
		(sensor == INV_ICM20948_SENSOR_ACCELEROMETER)){
			enum mpu_accel_fs afsr;
			if(*castedvalue == 2)
				afsr = MPU_FS_2G;
			else if(*castedvalue == 4)
				afsr = MPU_FS_4G;
			else if(*castedvalue == 8)
				afsr = MPU_FS_8G;
			else if(*castedvalue == 16)
				afsr = MPU_FS_16G;
			else
				return -1;
			result |= inv_icm20948_set_accel_fullscale(s, afsr);
	}
	else if((sensor == INV_ICM20948_SENSOR_GYROSCOPE) ||
		(sensor == INV_ICM20948_SENSOR_RAW_GYROSCOPE) ||
		(sensor == INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED)) {
			enum mpu_gyro_fs gfsr;
			if(*castedvalue == 250)
				gfsr = MPU_FS_250dps;
			else if(*castedvalue == 500)
				gfsr = MPU_FS_500dps;
			else if(*castedvalue == 1000)
				gfsr = MPU_FS_1000dps;
			else if(*castedvalue == 2000)
				gfsr = MPU_FS_2000dps;
			else
				return -1;
			result |= inv_icm20948_set_gyro_fullscale(s, gfsr);
	}
	return result;
}

int inv_icm20948_get_fsr(struct inv_icm20948 * s, enum inv_icm20948_sensor sensor, const void * fsr)
{

	if((sensor == INV_ICM20948_SENSOR_RAW_ACCELEROMETER) ||
	(sensor == INV_ICM20948_SENSOR_ACCELEROMETER)){
		unsigned char * castedvalue = (unsigned char*) fsr;
		int afsr = inv_icm20948_get_accel_fullscale(s);
		if(afsr == MPU_FS_2G)
			* castedvalue = 2;
		else if(afsr == MPU_FS_4G)
			* castedvalue = 4;
		else if(afsr == MPU_FS_8G)
			* castedvalue = 8;
		else if(afsr == MPU_FS_16G)
			* castedvalue = 16;
		else
			return -1;

		return 1;
	}
	else if((sensor == INV_ICM20948_SENSOR_GYROSCOPE) ||
		(sensor == INV_ICM20948_SENSOR_RAW_GYROSCOPE) ||
		(sensor == INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED)) {
			unsigned short * castedvalue = (unsigned short*) fsr;
			int gfsr = inv_icm20948_get_gyro_fullscale(s);
			if(gfsr == MPU_FS_250dps)
				* castedvalue = 250;
			else if(gfsr == MPU_FS_500dps)
				* castedvalue = 500;
			else if(gfsr == MPU_FS_1000dps)
				* castedvalue = 1000;
			else if(gfsr == MPU_FS_2000dps)
				* castedvalue = 2000;
			else
				return -1;

			return 2;
	}

	return 0;
}

int inv_icm20948_set_bias(struct inv_icm20948 * s, enum inv_icm20948_sensor sensor, const void * bias)
{
	int bias_q16[3];
	int bias_in[3];
	int rc = 0;
	short shift;
	switch(sensor) {
	case INV_ICM20948_SENSOR_ACCELEROMETER :
		memcpy(bias_q16, bias, sizeof(bias_q16));
		//convert from q16 to q25
		bias_in[0] = bias_q16[0] << (25 - 16);
		bias_in[1] = bias_q16[1] << (25 - 16);
		bias_in[2] = bias_q16[2] << (25 - 16);
		rc |= inv_icm20948_ctrl_set_acc_bias(s, bias_in);
		break;
	case INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED:
	case INV_ICM20948_SENSOR_GYROSCOPE:
		memcpy(bias_q16, bias, sizeof(bias_q16));
		//convert from q16 to :
		//Q19 => 2000dps
		//Q20 => 1000dps
		//Q21 => 500dps
		//Q22 => 250dps
		shift = ((20 + (MPU_FS_1000dps - inv_icm20948_get_gyro_fullscale(s))) - 16);
		bias_in[0] = bias_q16[0] << shift;
		bias_in[1] = bias_q16[1] << shift;
		bias_in[2] = bias_q16[2] << shift;

		rc |= inv_icm20948_ctrl_set_gyr_bias(s, bias_in);
		break;
	case INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED:
	case INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD:
		memcpy(bias_q16, bias, sizeof(bias_q16));
		// bias is already in q16
		rc |= inv_icm20948_ctrl_set_mag_bias(s, bias_q16);
		break;
	default :
		rc = -1;
		break;
	}
	return (rc == 0) ? 1 : rc;
}

int inv_icm20948_get_bias(struct inv_icm20948 * s, enum inv_icm20948_sensor sensor, void * bias)
{
	int bias_qx[3];
	int bias_out[3];
	int rc = 0;
	short shift;
	switch(sensor) {
	case INV_ICM20948_SENSOR_ACCELEROMETER :
		rc |= inv_icm20948_ctrl_get_acc_bias(s, bias_qx);
		//convert from q25 to q16
		bias_out[0] = bias_qx[0] >> (25 - 16);
		bias_out[1] = bias_qx[1] >> (25 - 16);
		bias_out[2] = bias_qx[2] >> (25 - 16);
		memcpy(bias, bias_out, sizeof(bias_out));
		break;
	case INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED:
	case INV_ICM20948_SENSOR_GYROSCOPE:
		rc |= inv_icm20948_ctrl_get_gyr_bias(s, bias_qx);
		//convert from qn to q16:
		//Q19 => 2000dps
		//Q20 => 1000dps
		//Q21 => 500dps
		//Q22 => 250dps
		shift = ((20 + (MPU_FS_1000dps - inv_icm20948_get_gyro_fullscale(s))) - 16);
		bias_out[0] = bias_qx[0] >> shift;
		bias_out[1] = bias_qx[1] >> shift;
		bias_out[2] = bias_qx[2] >> shift;

		memcpy(bias, bias_out, sizeof(bias_out));
		break;
	case INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED:
	case INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD:
		rc |= inv_icm20948_ctrl_get_mag_bias(s, bias_qx);
		// bias is already in q16
		memcpy(bias, bias_qx, sizeof(bias_qx));
		break;
	default:
		rc = -1;
		break;
	}
	return (rc == 0) ? 3*(int)sizeof(float) : rc;
}

int inv_icm20948_set_lowpower_or_highperformance(struct inv_icm20948 * s, uint8_t lowpower_or_highperformance)
{
	s->go_back_lp_when_odr_low = 0;
	if(lowpower_or_highperformance)
		return inv_icm20948_enter_low_noise_mode(s);
	else
		return inv_icm20948_enter_duty_cycle_mode(s);
}


int inv_icm20948_get_lowpower_or_highperformance(struct inv_icm20948 * s, uint8_t * lowpower_or_highperformance)
{
	(void)s;
	*lowpower_or_highperformance = CHIP_LOW_NOISE_ICM20948;
	return 1;
}

void DmpDriver_convertion(signed char transformedtochar[9],
	const int32_t MatrixInQ30[9])
{
	// To convert Q30 to signed char value
	uint8_t iter;
	for (iter = 0; iter < 9; ++iter)
		transformedtochar[iter] = MatrixInQ30[iter] >> 30;
}

int inv_icm20948_set_matrix(struct inv_icm20948 * s, const float matrix[9], enum inv_icm20948_sensor sensor)
{
	int32_t mounting_mq30[9];
	int result = 0;
	int i;

	for(i = 0; i < 9; ++i)
		mounting_mq30[i] = (int32_t)(matrix[i] * (1 << 30));
	// Convert mounting matrix in char
	DmpDriver_convertion(s->mounting_matrix, mounting_mq30);
	//Apply new matrix
	inv_icm20948_set_chip_to_body_axis_quaternion(s, s->mounting_matrix, 0.0);

	if ((sensor == INV_ICM20948_SENSOR_RAW_ACCELEROMETER) ||
		(sensor == INV_ICM20948_SENSOR_ACCELEROMETER) ||
		(sensor == INV_ICM20948_SENSOR_RAW_GYROSCOPE) ||
		(sensor == INV_ICM20948_SENSOR_GYROSCOPE) ||
		(sensor == INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED)) {
			//Update Dmp B2S according to new mmatrix in q30
			result |= dmp_icm20948_set_B2S_matrix(s, (int*)mounting_mq30);
	}

	return result;
}

int inv_icm20948_initialize_auxiliary(struct inv_icm20948 * s)
{
	if (inv_icm20948_set_slave_compass_id(s, s->secondary_state.compass_slave_id) )
		return -1;
	return 0;
}

int inv_icm20948_soft_reset(struct inv_icm20948 * s)
{

	//soft reset like
	int rc = inv_icm20948_write_single_mems_reg(s, REG_PWR_MGMT_1, BIT_H_RESET);
	// max start-up time is 100 msec
	inv_icm20948_sleep_us(100000);
	return rc;
}

int inv_icm20948_enable_sensor(struct inv_icm20948 * s, enum inv_icm20948_sensor sensor, inv_bool_t state)
{
	uint8_t androidSensor = sensor_type_2_android_sensor(sensor);

	if(0!=inv_icm20948_ctrl_enable_sensor(s, androidSensor, state))
		return -1;

	//In case we disable a sensor, we reset his timestamp
	if(state == 0)
		s->timestamp[sensor] = 0;

	return 0;
}

int inv_icm20948_set_sensor_period(struct inv_icm20948 * s, enum inv_icm20948_sensor sensor, uint32_t period)
{
	uint8_t androidSensor = sensor_type_2_android_sensor(sensor);

	if(0!=inv_icm20948_set_odr(s, androidSensor, period))
		return -1;

	// reset timestamp value and save current odr
	s->timestamp[sensor] = 0;
	s->sensorlist[sensor].odr_us = period * 1000;
	return 0;
}

int inv_icm20948_enable_batch_timeout(struct inv_icm20948 * s, unsigned short batchTimeoutMs)
{
	int rc;
	/* Configure batch timeout */
	if (inv_icm20948_ctrl_set_batch_timeout_ms(s, batchTimeoutMs) == 0) {
		/* If configuration was succesful then we enable it */
		if((rc = inv_icm20948_ctrl_enable_batch(s, 1)) != 0)
			return rc;
	} else {
		/* Else we disable it */
		if((rc = inv_icm20948_ctrl_enable_batch(s, 0)) != 0)
			return rc;
	}
	return 0;
}

int inv_icm20948_load(struct inv_icm20948 * s, const uint8_t * image, unsigned short size)
{
	return inv_icm20948_firmware_load(s, image, size, DMP_LOAD_START);
}

/** @brief Returns 1 if the sensor id is a streamed sensor and not an event-based sensor */
int inv_icm20948_is_streamed_sensor(uint8_t id)
{
	switch(id)
	{
	case ANDROID_SENSOR_WAKEUP_TILT_DETECTOR :
	case ANDROID_SENSOR_ACTIVITY_CLASSIFICATON :
	case ANDROID_SENSOR_FLIP_PICKUP :
	case ANDROID_SENSOR_B2S :
	case ANDROID_SENSOR_STEP_COUNTER:
	case ANDROID_SENSOR_WAKEUP_SIGNIFICANT_MOTION :
	case ANDROID_SENSOR_STEP_DETECTOR :
		return 0;
	default :
		return 1;
	}
}

/** @brief Preprocess all timestamps so that they either contain very last time at which MEMS IRQ was fired
* or last time sent for the sensor + ODR */
uint8_t inv_icm20948_updateTs(struct inv_icm20948 * s, int * data_left_in_fifo,
	unsigned short * total_sample_cnt, uint64_t * lastIrqTimeUs)
{
	/** @brief Very last time in us at which IRQ was fired since flushing FIFO process was started */
	unsigned short sample_cnt_array[GENERAL_SENSORS_MAX] = {0};
	uint8_t i;

	memset(sample_cnt_array, 0, sizeof(sample_cnt_array));
	if (inv_icm20948_fifo_swmirror(s, data_left_in_fifo, total_sample_cnt, sample_cnt_array)) {
		for(i = 0; i< GENERAL_SENSORS_MAX; i++) {
			if (inv_icm20948_is_streamed_sensor(i)) {
				s->timestamp[inv_icm20948_sensor_android_2_sensor_type(i)] = *lastIrqTimeUs;
			}
		}
		return -1;
	}
	// we parse all senosr according to android type
	for (i = 0; i < GENERAL_SENSORS_MAX; i++) {
		if (inv_icm20948_is_streamed_sensor(i)) {
			if (sample_cnt_array[i]) {
				/** Number of samples present in MEMS FIFO last time we mirrored it */
				unsigned short fifo_sample_cnt = sample_cnt_array[i];

				/** In case of first batch we have less than the expected number of samples in the batch */
				/** To avoid a bad timestamping we recompute the startup time based on the theorical ODR and the number of samples */
				if (s->sFirstBatch[inv_icm20948_sensor_android_2_sensor_type(i)]) {
					s->timestamp[inv_icm20948_sensor_android_2_sensor_type(i)] += *lastIrqTimeUs-s->timestamp[inv_icm20948_sensor_android_2_sensor_type(i)]
					- fifo_sample_cnt*s->sensorlist[inv_icm20948_sensor_android_2_sensor_type(i)].odr_us;
					s->sFirstBatch[inv_icm20948_sensor_android_2_sensor_type(i)] = 0;
				}

				/** In case it's the first time timestamp is set we create a factice one,
				In other cases, update timestamp for all streamed sensors depending on number of samples available in FIFO
				first time to be printed is t1+(t2-t1)/N
				- t1 is last time we sent data
				- t2 is when IRQ was fired so that we pop the FIFO
				- N is number of samples */

				if(s->timestamp[inv_icm20948_sensor_android_2_sensor_type(i)] == 0) {
					s->timestamp[inv_icm20948_sensor_android_2_sensor_type(i)] = *lastIrqTimeUs;
					s->timestamp[inv_icm20948_sensor_android_2_sensor_type(i)] -= s->sensorlist[inv_icm20948_sensor_android_2_sensor_type(i)].odr_us*(fifo_sample_cnt);
					s->sensorlist[inv_icm20948_sensor_android_2_sensor_type(i)].odr_applied_us = s->sensorlist[inv_icm20948_sensor_android_2_sensor_type(i)].odr_us;
				}
				else {
					s->sensorlist[inv_icm20948_sensor_android_2_sensor_type(i)].odr_applied_us = (*lastIrqTimeUs-s->timestamp[inv_icm20948_sensor_android_2_sensor_type(i)])/fifo_sample_cnt;
				}
			}
		} else {
			/** update timestamp for all event sensors with time at which MEMS IRQ was fired */
			s->timestamp[inv_icm20948_sensor_android_2_sensor_type(i)] = *lastIrqTimeUs;
		}
	}

	return 0;
}

int inv_icm20948_poll_sensor(struct inv_icm20948 * s, void * context,
	std::function<int(enum inv_icm20948_sensor sensor, uint64_t timestamp, const void * data, const void *arg)> handler)
	//void (*handler)(void * context, enum inv_icm20948_sensor sensor, uint64_t timestamp, const void * data, const void *arg))
{
	short int_read_back=0;
	unsigned short header=0, header2 = 0;
	int data_left_in_fifo=0;
	short short_data[3] = {0};
	signed long  long_data[3] = {0};
	signed long  long_quat[3] = {0};
	float gyro_raw_float[3];
	float gyro_bias_float[3];
	int gyro_accuracy = 0;
	int dummy_accuracy = 0;
	int accel_accuracy = 0;
	int compass_accuracy = 0;
	float rv_accuracy = 0;
	float gmrv_accuracy = 0;
	float accel_float[3];
	float grv_float[4];
	float gyro_float[3];
	float compass_float[3] = {0};
	float compass_raw_float[3];
	float rv_float[4];
	float gmrv_float[4];
	uint16_t pickup_state = 0;
	uint64_t lastIrqTimeUs;

	inv_icm20948_identify_interrupt(s, &int_read_back);

	if (int_read_back & (BIT_MSG_DMP_INT | BIT_MSG_DMP_INT_0)) {
		lastIrqTimeUs = inv_icm20948_get_time_us();
		do {
			unsigned short total_sample_cnt = 0;

			/* Mirror FIFO contents and stop processing FIFO if an error was detected*/
			if(inv_icm20948_updateTs(s, &data_left_in_fifo, &total_sample_cnt, &lastIrqTimeUs))
				break;
			while(total_sample_cnt--) {
				/* Read FIFO contents and parse it, and stop processing FIFO if an error was detected*/
				if (inv_icm20948_fifo_pop(s, &header, &header2, &data_left_in_fifo))
					break;

				/* Gyro sample available from DMP FIFO */
				if (header & GYRO_SET) {
					float lScaleDeg = (1 << inv_icm20948_get_gyro_fullscale(s)) * 250.f; // From raw to dps to degree per seconds
					float lScaleDeg_bias = 2000.f; // Gyro bias from FIFO is always in 2^20 = 2000 dps regardless of fullscale
					signed long  lRawGyroQ15[3] = {0};
					signed long  lBiasGyroQ20[3] = {0};

					/* Read raw gyro out of DMP FIFO and convert it from Q15 raw data format to radian per seconds in Android format */
					inv_icm20948_dmp_get_raw_gyro(short_data);
					lRawGyroQ15[0] = (long) short_data[0];
					lRawGyroQ15[1] = (long) short_data[1];
					lRawGyroQ15[2] = (long) short_data[2];
					inv_icm20948_convert_dmp3_to_body(s, lRawGyroQ15, lScaleDeg/(1L<<15), gyro_raw_float);

					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_RAW_GYROSCOPE) && !skip_sensor(s, ANDROID_SENSOR_RAW_GYROSCOPE)) {
						long out[3];
						inv_icm20948_convert_quat_rotate_fxp(s->s_quat_chip_to_body, lRawGyroQ15, out);
						s->timestamp[INV_ICM20948_SENSOR_RAW_GYROSCOPE] += s->sensorlist[INV_ICM20948_SENSOR_RAW_GYROSCOPE].odr_applied_us;
						handler(INV_ICM20948_SENSOR_RAW_GYROSCOPE, s->timestamp[INV_ICM20948_SENSOR_RAW_GYROSCOPE], out, &dummy_accuracy);
					}

					/* Read bias gyro out of DMP FIFO and convert it from Q20 raw data format to radian per seconds in Android format */
					inv_icm20948_dmp_get_gyro_bias(short_data);
					lBiasGyroQ20[0] = (long) short_data[0];
					lBiasGyroQ20[1] = (long) short_data[1];
					lBiasGyroQ20[2] = (long) short_data[2];
					inv_icm20948_convert_dmp3_to_body(s, lBiasGyroQ20, lScaleDeg_bias/(1L<<20), gyro_bias_float);

					/* Extract accuracy and calibrated gyro data based on raw/bias data if calibrated gyro sensor is enabled */
					gyro_accuracy = inv_icm20948_get_gyro_accuracy();
					/* If accuracy has changed previously we update the new accuracy the same time as bias*/
					if(s->set_accuracy){
						s->set_accuracy = 0;
						s->new_accuracy = gyro_accuracy;
					}
					/* gyro accuracy has changed, we will notify it the next time*/
					if(gyro_accuracy != s->new_accuracy){
						s->set_accuracy = 1;
					}
					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GYROSCOPE) && !skip_sensor(s, ANDROID_SENSOR_GYROSCOPE)) {
						// shift to Q20 to do all calibrated gyrometer operations in Q20
						// Gyro bias from FIFO is always in 2^20 = 2000 dps regardless of fullscale
						// Raw gyro from FIFO is in 2^15 = gyro fsr (250/500/1000/2000).
						lRawGyroQ15[0] <<= 5 - (MPU_FS_2000dps - inv_icm20948_get_gyro_fullscale(s));
						lRawGyroQ15[1] <<= 5 - (MPU_FS_2000dps - inv_icm20948_get_gyro_fullscale(s));
						lRawGyroQ15[2] <<= 5 - (MPU_FS_2000dps - inv_icm20948_get_gyro_fullscale(s));
						/* Compute calibrated gyro data based on raw and bias gyro data and convert it from Q20 raw data format to radian per seconds in Android format */
						inv_icm20948_dmp_get_calibrated_gyro(long_data, lRawGyroQ15, lBiasGyroQ20);
						inv_icm20948_convert_dmp3_to_body(s, long_data, lScaleDeg_bias/(1L<<20), gyro_float);
						s->timestamp[INV_ICM20948_SENSOR_GYROSCOPE] += s->sensorlist[INV_ICM20948_SENSOR_GYROSCOPE].odr_applied_us;
						handler(INV_ICM20948_SENSOR_GYROSCOPE, s->timestamp[INV_ICM20948_SENSOR_GYROSCOPE], gyro_float, &s->new_accuracy);
					}
					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED)  && !skip_sensor(s, ANDROID_SENSOR_GYROSCOPE_UNCALIBRATED)) {
						float raw_bias_gyr[6];
						raw_bias_gyr[0] = gyro_raw_float[0];
						raw_bias_gyr[1] = gyro_raw_float[1];
						raw_bias_gyr[2] = gyro_raw_float[2];
						raw_bias_gyr[3] = gyro_bias_float[0];
						raw_bias_gyr[4] = gyro_bias_float[1];
						raw_bias_gyr[5] = gyro_bias_float[2];
						s->timestamp[INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED] += s->sensorlist[INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED].odr_applied_us;
						/* send raw float and bias for uncal gyr*/
						handler(INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED, s->timestamp[INV_ICM20948_SENSOR_GYROSCOPE_UNCALIBRATED], raw_bias_gyr, &s->new_accuracy);
					}
				}
				/* Calibrated accel sample available from DMP FIFO */
				if (header & ACCEL_SET) {
					float scale;
					/* Read calibrated accel out of DMP FIFO and convert it from Q25 raw data format to m/s² in Android format */
					inv_icm20948_dmp_get_accel(long_data);

					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_RAW_ACCELEROMETER) && !skip_sensor(s, ANDROID_SENSOR_RAW_ACCELEROMETER)) {
						long out[3];
						inv_icm20948_convert_quat_rotate_fxp(s->s_quat_chip_to_body, long_data, out);
						
						/* convert to raw data format to Q12/Q11/Q10/Q9 depending on full scale applied,
						so that it fits on 16bits so that it can go through any protocol, even the one which have raw data on 16b */
						out[0] = out[0] >> 15;
						out[1] = out[1] >> 15;
						out[2] = out[2] >> 15;
						s->timestamp[INV_ICM20948_SENSOR_RAW_ACCELEROMETER] += s->sensorlist[INV_ICM20948_SENSOR_RAW_ACCELEROMETER].odr_applied_us;
						handler(INV_ICM20948_SENSOR_RAW_ACCELEROMETER, s->timestamp[INV_ICM20948_SENSOR_RAW_ACCELEROMETER], out, &dummy_accuracy);
					}
					if((inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_ACCELEROMETER) && !skip_sensor(s, ANDROID_SENSOR_ACCELEROMETER)) ||
						(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_LINEAR_ACCELERATION))) {
							accel_accuracy = inv_icm20948_get_accel_accuracy();
							scale = (1 << inv_icm20948_get_accel_fullscale(s)) * 2.f / (1L<<30); // Convert from raw units to g's

							inv_icm20948_convert_dmp3_to_body(s, long_data, scale, accel_float);

							if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_ACCELEROMETER)) {
								s->timestamp[INV_ICM20948_SENSOR_ACCELEROMETER] += s->sensorlist[INV_ICM20948_SENSOR_ACCELEROMETER].odr_applied_us;
								handler(INV_ICM20948_SENSOR_ACCELEROMETER, s->timestamp[INV_ICM20948_SENSOR_ACCELEROMETER], accel_float, &accel_accuracy);
							}
					}
				}
				/* Calibrated compass sample available from DMP FIFO */
				if (header & CPASS_CALIBR_SET) {
					float scale;

					/* Read calibrated compass out of DMP FIFO and convert it from Q16 raw data format to µT in Android format */
					inv_icm20948_dmp_get_calibrated_compass(long_data);

					compass_accuracy = inv_icm20948_get_mag_accuracy();
					scale = DMP_UNIT_TO_FLOAT_COMPASS_CONVERSION;
					inv_icm20948_convert_dmp3_to_body(s, long_data, scale, compass_float);
					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GEOMAGNETIC_FIELD) && !skip_sensor(s, ANDROID_SENSOR_GEOMAGNETIC_FIELD)) {
						s->timestamp[INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD] += s->sensorlist[INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD].odr_applied_us;
						handler(INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD, s->timestamp[INV_ICM20948_SENSOR_GEOMAGNETIC_FIELD], compass_float, &compass_accuracy);
					}
				}

				/* Raw compass sample available from DMP FIFO */
				if (header & CPASS_SET) {
					/* Read calibrated compass out of DMP FIFO and convert it from Q16 raw data format to µT in Android format */
					inv_icm20948_dmp_get_raw_compass(long_data);
					compass_raw_float[0] = long_data[0] * DMP_UNIT_TO_FLOAT_COMPASS_CONVERSION;
					compass_raw_float[1] = long_data[1] * DMP_UNIT_TO_FLOAT_COMPASS_CONVERSION;
					compass_raw_float[2] = long_data[2] * DMP_UNIT_TO_FLOAT_COMPASS_CONVERSION;
					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED) && !skip_sensor(s, ANDROID_SENSOR_MAGNETIC_FIELD_UNCALIBRATED)) {
						float raw_bias_mag[6];
						int mag_bias[3];

						raw_bias_mag[0] = compass_raw_float[0];
						raw_bias_mag[1] = compass_raw_float[1];
						raw_bias_mag[2] = compass_raw_float[2];
						inv_icm20948_ctrl_get_mag_bias(s, mag_bias);
						//calculate bias
						raw_bias_mag[3] = mag_bias[0] * DMP_UNIT_TO_FLOAT_COMPASS_CONVERSION;
						raw_bias_mag[4] = mag_bias[1] * DMP_UNIT_TO_FLOAT_COMPASS_CONVERSION;
						raw_bias_mag[5] = mag_bias[2] * DMP_UNIT_TO_FLOAT_COMPASS_CONVERSION;

						compass_accuracy = inv_icm20948_get_mag_accuracy();
						s->timestamp[INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED] += s->sensorlist[INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED].odr_applied_us;
						/* send raw float and bias for uncal mag*/
						handler(INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED, s->timestamp[INV_ICM20948_SENSOR_MAGNETIC_FIELD_UNCALIBRATED],
							raw_bias_mag, &compass_accuracy);
					}
				}
				/* 6axis AG orientation quaternion sample available from DMP FIFO */
				if (header & QUAT6_SET) {
					long gravityQ16[3];
					float ref_quat[4];
					/* Read 6 axis quaternion out of DMP FIFO in Q30 */
					inv_icm20948_dmp_get_6quaternion(long_quat);
					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GAME_ROTATION_VECTOR) && !skip_sensor(s, ANDROID_SENSOR_GAME_ROTATION_VECTOR)) {
						/* and convert it from Q30 DMP format to Android format only if GRV sensor is enabled */
						inv_icm20948_convert_rotation_vector(s, long_quat, grv_float);
						ref_quat[0] = grv_float[3];
						ref_quat[1] = grv_float[0];
						ref_quat[2] = grv_float[1];
						ref_quat[3] = grv_float[2];
						s->timestamp[INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR] += s->sensorlist[INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR].odr_applied_us;
						handler(INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR, s->timestamp[INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR], ref_quat, 0);
					}

					/* Compute gravity sensor data in Q16 in g based on 6 axis quaternion in Q30 DMP format */
					inv_icm20948_augmented_sensors_get_gravity(s, gravityQ16, long_quat);
					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GRAVITY) && !skip_sensor(s, ANDROID_SENSOR_GRAVITY)) {
						float gravity_float[3];
						/* Convert gravity data from Q16 to float format in g */
						gravity_float[0] = INVN_FXP_TO_FLT(gravityQ16[0], 16);
						gravity_float[1] = INVN_FXP_TO_FLT(gravityQ16[1], 16);
						gravity_float[2] = INVN_FXP_TO_FLT(gravityQ16[2], 16);
						s->timestamp[INV_ICM20948_SENSOR_GRAVITY] += s->sensorlist[INV_ICM20948_SENSOR_GRAVITY].odr_applied_us;
						handler(INV_ICM20948_SENSOR_GRAVITY, s->timestamp[INV_ICM20948_SENSOR_GRAVITY], gravity_float, &accel_accuracy);
					}

					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_LINEAR_ACCELERATION) && !skip_sensor(s, ANDROID_SENSOR_LINEAR_ACCELERATION)) {
						float linacc_float[3];
						long linAccQ16[3];
						long accelQ16[3];

						/* Compute linear acceleration data based on accelerometer data in Q16 g and on gravity data in Q16 g */
						accelQ16[0] = (int32_t)  ((float)(accel_float[0])*(1ULL << 16) + ( (accel_float[0]>=0)-0.5f ));
						accelQ16[1] = (int32_t)  ((float)(accel_float[1])*(1ULL << 16) + ( (accel_float[1]>=0)-0.5f ));
						accelQ16[2] = (int32_t)  ((float)(accel_float[2])*(1ULL << 16) + ( (accel_float[2]>=0)-0.5f ));

						inv_icm20948_augmented_sensors_get_linearacceleration(linAccQ16, gravityQ16, accelQ16);
						linacc_float[0] = INVN_FXP_TO_FLT(linAccQ16[0], 16);
						linacc_float[1] = INVN_FXP_TO_FLT(linAccQ16[1], 16);
						linacc_float[2] = INVN_FXP_TO_FLT(linAccQ16[2], 16);
						s->timestamp[INV_ICM20948_SENSOR_LINEAR_ACCELERATION] += s->sensorlist[INV_ICM20948_SENSOR_LINEAR_ACCELERATION].odr_applied_us;
						handler(INV_ICM20948_SENSOR_LINEAR_ACCELERATION, s->timestamp[INV_ICM20948_SENSOR_LINEAR_ACCELERATION], linacc_float, &accel_accuracy);
					}
				}
				/* 9axis orientation quaternion sample available from DMP FIFO */
				if (header & QUAT9_SET) {
					float ref_quat[4];
					/* Read 9 axis quaternion out of DMP FIFO in Q30 */
					inv_icm20948_dmp_get_9quaternion(long_quat);
					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_ROTATION_VECTOR) && !skip_sensor(s, ANDROID_SENSOR_ROTATION_VECTOR)) {
						/* and convert it from Q30 DMP format to Android format only if RV sensor is enabled */
						inv_icm20948_convert_rotation_vector(s, long_quat, rv_float);
						/* Read rotation vector heading accuracy out of DMP FIFO in Q29*/
						{
							float rv_accur = inv_icm20948_get_rv_accuracy();
							rv_accuracy = rv_accur/(float)(1ULL << (29));
						}
						ref_quat[0] = rv_float[3];
						ref_quat[1] = rv_float[0];
						ref_quat[2] = rv_float[1];
						ref_quat[3] = rv_float[2];
						s->timestamp[INV_ICM20948_SENSOR_ROTATION_VECTOR] += s->sensorlist[INV_ICM20948_SENSOR_ROTATION_VECTOR].odr_applied_us;
						handler(INV_ICM20948_SENSOR_ROTATION_VECTOR, s->timestamp[INV_ICM20948_SENSOR_ROTATION_VECTOR], ref_quat, &rv_accuracy);
					}

					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_ORIENTATION) && !skip_sensor(s, ANDROID_SENSOR_ORIENTATION)) {
						long orientationQ16[3];
						float orientation_float[3];
						/* Compute Android-orientation sensor data based on rotation vector data in Q30 */
						inv_icm20948_augmented_sensors_get_orientation(orientationQ16, long_quat);
						orientation_float[0] = INVN_FXP_TO_FLT(orientationQ16[0], 16);
						orientation_float[1] = INVN_FXP_TO_FLT(orientationQ16[1], 16);
						orientation_float[2] = INVN_FXP_TO_FLT(orientationQ16[2], 16);
						s->timestamp[INV_ICM20948_SENSOR_ORIENTATION] += s->sensorlist[INV_ICM20948_SENSOR_ORIENTATION].odr_applied_us;
						handler(INV_ICM20948_SENSOR_ORIENTATION, s->timestamp[INV_ICM20948_SENSOR_ORIENTATION], orientation_float, 0);
					}
				}
				/* 6axis AM orientation quaternion sample available from DMP FIFO */
				if (header & GEOMAG_SET) {
					float ref_quat[4];
					/* Read 6 axis quaternion out of DMP FIFO in Q30 and convert it to Android format */
					inv_icm20948_dmp_get_gmrvquaternion(long_quat);
					if(inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR) && !skip_sensor(s, ANDROID_SENSOR_GEOMAGNETIC_ROTATION_VECTOR)) {
						inv_icm20948_convert_rotation_vector(s, long_quat, gmrv_float);
						/* Read geomagnetic rotation vector heading accuracy out of DMP FIFO in Q29*/
						{
							float gmrv_acc = inv_icm20948_get_gmrv_accuracy();
							gmrv_accuracy = gmrv_acc/(float)(1ULL << (29));
						}
						ref_quat[0] = gmrv_float[3];
						ref_quat[1] = gmrv_float[0];
						ref_quat[2] = gmrv_float[1];
						ref_quat[3] = gmrv_float[2];
						s->timestamp[INV_ICM20948_SENSOR_GEOMAGNETIC_ROTATION_VECTOR] += s->sensorlist[INV_ICM20948_SENSOR_GEOMAGNETIC_ROTATION_VECTOR].odr_applied_us;
						handler(INV_ICM20948_SENSOR_GEOMAGNETIC_ROTATION_VECTOR, s->timestamp[INV_ICM20948_SENSOR_GEOMAGNETIC_ROTATION_VECTOR],
							ref_quat, &gmrv_accuracy);
					}
				}
				/* Activity recognition sample available from DMP FIFO */
				if (header2 & ACT_RECOG_SET) {
					uint16_t bac_state = 0;
					long bac_ts = 0;
					int bac_event = 0;
					struct bac_map{
						uint8_t act_id;
						enum inv_sensor_bac_event sensor_bac;
					} map[] = {
						{ BAC_DRIVE, INV_SENSOR_BAC_EVENT_ACT_IN_VEHICLE_BEGIN},
						{ BAC_WALK, INV_SENSOR_BAC_EVENT_ACT_WALKING_BEGIN},
						{ BAC_RUN, INV_SENSOR_BAC_EVENT_ACT_RUNNING_BEGIN},
						{ BAC_BIKE, INV_SENSOR_BAC_EVENT_ACT_ON_BICYCLE_BEGIN},
						{ BAC_STILL, INV_SENSOR_BAC_EVENT_ACT_STILL_BEGIN},
						{ BAC_TILT, INV_SENSOR_BAC_EVENT_ACT_TILT_BEGIN},
					};
					int i = 0;
					/* Read activity type and associated timestamp out of DMP FIFO
					activity type is a set of 2 bytes :
					- high byte indicates activity start
					- low byte indicates activity end */
					inv_icm20948_dmp_get_bac_state(&bac_state);
					inv_icm20948_dmp_get_bac_ts(&bac_ts);
					//Map according to dmp bac events
					for(i = 0; i < 6; i++) {
						if ((bac_state >> 8) & map[i].act_id){
							//Check if BAC is enabled
							if (inv_icm20948_ctrl_get_activitiy_classifier_on_flag(s)) {
								/* Start detected */
								bac_event = map[i].sensor_bac;
								handler(INV_ICM20948_SENSOR_ACTIVITY_CLASSIFICATON, s->timestamp[INV_ICM20948_SENSOR_ACTIVITY_CLASSIFICATON], &bac_event, 0);
							}
							//build event TILT only if enabled
							if((map[i].act_id == BAC_TILT) && inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_WAKEUP_TILT_DETECTOR))
								handler(INV_ICM20948_SENSOR_WAKEUP_TILT_DETECTOR, s->timestamp[INV_ICM20948_SENSOR_WAKEUP_TILT_DETECTOR], 0, 0);
						}
						/* Check if bit tilt is set for activity end byte */
						else if (bac_state & map[i].act_id) {
							//Check if BAC is enabled
							if (inv_icm20948_ctrl_get_activitiy_classifier_on_flag(s)) {
								/* End detected */
								bac_event = -map[i].sensor_bac;
								handler(INV_ICM20948_SENSOR_ACTIVITY_CLASSIFICATON, s->timestamp[INV_ICM20948_SENSOR_ACTIVITY_CLASSIFICATON], &bac_event, 0);
							}
						}
					}
				}
				/* Pickup sample available from DMP FIFO */
				if (header2 & FLIP_PICKUP_SET) {
					/* Read pickup type and associated timestamp out of DMP FIFO */
					inv_icm20948_dmp_get_flip_pickup_state(&pickup_state);
					handler(INV_ICM20948_SENSOR_FLIP_PICKUP, s->timestamp[INV_ICM20948_SENSOR_FLIP_PICKUP], &pickup_state, 0);
				}

				/* Step detector available from DMP FIFO and step counter sensor is enabled*/
				// If step detector enabled => step counter started too
				// So don't watch the step counter data if the user doesn't start the sensor
				if((header & PED_STEPDET_SET) && (inv_icm20948_ctrl_androidSensor_enabled(s, ANDROID_SENSOR_STEP_COUNTER))) {
					unsigned long steps;
					unsigned long lsteps;
					uint64_t stepc = 0;
					/* Read amount of steps counted out of DMP FIFO and notify them only if updated */
					dmp_icm20948_get_pedometer_num_of_steps(s, &lsteps);
					// need to subtract the steps accumulated while Step Counter sensor is not active.
					steps = lsteps - s->sStepCounterToBeSubtracted;
					stepc = steps;
					if(stepc != s->sOldSteps) {
						s->sOldSteps = steps;
						handler(INV_ICM20948_SENSOR_STEP_COUNTER, s->timestamp[INV_ICM20948_SENSOR_STEP_COUNTER], &stepc, 0);
					}
				}
			}
		} while(data_left_in_fifo);

		/* SMD detected by DMP */
		if (int_read_back & BIT_MSG_DMP_INT_2) {
			uint8_t event = 0;
			handler(INV_ICM20948_SENSOR_WAKEUP_SIGNIFICANT_MOTION, s->timestamp[INV_ICM20948_SENSOR_WAKEUP_SIGNIFICANT_MOTION], &event, 0);
		}
		/* Step detector triggered by DMP */
		if (int_read_back & BIT_MSG_DMP_INT_3) {
			uint8_t event = 0;
			handler(INV_ICM20948_SENSOR_STEP_DETECTOR, s->timestamp[INV_ICM20948_SENSOR_STEP_DETECTOR], &event, 0);
		}
		/* Bring to see detected by DMP */
		if (int_read_back & BIT_MSG_DMP_INT_5) {
			uint8_t event = 0;
			handler(INV_ICM20948_SENSOR_B2S, s->timestamp[INV_ICM20948_SENSOR_B2S], &event, 0);
		}
	}

	/* Sometimes, the chip can be put in sleep mode even if there is data in the FIFO. If we poll at this moment, the transport layer will wake-up the chip, but never put it back in sleep. */
	if (s->mems_put_to_sleep) {
		inv_icm20948_sleep_mems(s);
	}

	return 0;
}






















};

#endif /* _INV_ICM20948_MAIN_H_ */

/** @} */
