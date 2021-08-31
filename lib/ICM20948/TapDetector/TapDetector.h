#ifndef _TAP_DETECTOR_H_
#define _TAP_DETECTOR_H_ 

#include <Arduino.h>
#include <functional>
#include "filter.h"

// May require tuning for different IMUs
// - set imu accel polling fast (ie 200hz)
// - call update() using the value from the axis to detect taps on (ie z)
// - tweak sampling_hz and cutoff_hz and add serial printout (in update()) to plot values, there should be prominent spikes on taps and not movement
// - slowly raise the cutoff_threshold until it only prints when the minimum tap force you want is reached
// - tweak prevent_event_ms as desired to make sure only a single tap is raised per physical tap

class TapDetector {
	public:
    TapDetector() {};
		TapDetector(	
					int tap_count, // Number of sequential taps to listen for
			    	std::function<void()> tap_handler, // Callback used when [tap_count] number of taps is received (in timeframe)
					int prevent_event_ms = 25, // ms after an accelerometer event to prevent additional events for (debouncing)
					int event_repeat_ms = 400, // for multi-tap events, next tap must follow within this ms period
					float cutoff_threshold = 0.4f, // filtered value must be over this to register as a tap
					float cutoff_hz = 1.0f, // suppress accell data over this frequency
					float sampling_hz = 5.0f); // How fast to sample (should be at least double cutoff_hz)
					
		bool update(float value);
	
	private:
		int prevent_event_ms;
		int event_repeat_ms;
    float cutoff_threshold;
		int tap_count;
		int current_tap = 0;
		std::function<void()> tap_handler;
    unsigned long last_event = 0;
    BWHighPass* bwFilter;
};

#endif // _TAP_DETECTOR_H_
