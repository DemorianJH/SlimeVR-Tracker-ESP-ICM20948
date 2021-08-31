// Uses a high pass Butterworth filter with thresholding and delays between events
// Allows an arbitrary number of taps
// Uses https://github.com/adis300/filter-c

#include "TapDetector.h"

TapDetector::TapDetector(
		int tap_count, 
    	std::function<void()> tap_handler,
		int prevent_event_ms, 
    	int	event_repeat_ms, 
    	float cutoff_threshold,
		float cutoff_hz, 
		float sampling_hz) {
		
	this->tap_handler = tap_handler;
	this->prevent_event_ms = prevent_event_ms;
	this->event_repeat_ms = event_repeat_ms;
	this->tap_count = tap_count;	
	this->cutoff_threshold = cutoff_threshold;
  	bwFilter = create_bw_high_pass_filter(2, sampling_hz, cutoff_hz);
}

// True if tap count reached
bool TapDetector::update(float value) {
	float filtVal = bw_high_pass(bwFilter, value);
	
	if (millis() >= last_event + event_repeat_ms) {
		current_tap = 0;
	}
	
	//Serial.println(filtVal); // Use to plot data when tuning

	if (millis() >= last_event + prevent_event_ms) {

	  	if (filtVal > cutoff_threshold || filtVal < -cutoff_threshold)
	  	{
	  		current_tap++;
		  	if (current_tap == tap_count) {
				// Raise tap event
        		tap_handler();
			  	current_tap = 0;
				last_event = millis();
				return true;
		  	}
		
	    	last_event = millis();
	  	}  
	}

	return false;	
}
