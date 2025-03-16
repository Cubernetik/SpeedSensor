#include <Arduino.h>
#include "driver/rmt.h"
#include "driver/timer.h"

#define SENSOR_PIN_START 	GPIO_NUM_27
#define SENSOR_PIN_END 		GPIO_NUM_26

#define SENSOR_DISTANCE 	0.03 							// Distance between sensors in meters
#define TIMER_TICKS_PER_US 	1000000 						// 1µs per tick (make sure to use values which result in integer timer divider)
#define TIMER_DIVIDER 		80000000 / TIMER_TICKS_PER_US	// 80 MHz clock

volatile uint32_t timeStart = 0;
volatile uint32_t timeEnd = 0;
volatile uint32_t timeDiff = 0;
volatile bool timeIsValid = false;

// Capture start time
void IRAM_ATTR isrStartTime() 
{
	// Capture only once and ignore disturbances
	if (timeStart == 0)
	{
		timeStart = timer_group_get_counter_value_in_isr(TIMER_GROUP_0, TIMER_0);
	}
}

// Capture end time
void IRAM_ATTR isrEndTime() 
{
	// Do not capture if no start time which means opposite sensor triggered first
	if (timeStart > 0)
	{
		timeEnd = timer_group_get_counter_value_in_isr(TIMER_GROUP_0, TIMER_0);

		if (timeEnd > timeStart)
			timeDiff = timeEnd - timeStart;
		// Calculate with overflow
		else
			timeDiff = UINT32_MAX - timeStart + timeEnd;

		timeEnd = 0;
		timeStart = 0;
		timeIsValid = true;
	}
}

void setup() 
{
	Serial.begin(115200);

	// Configure GPIO pins as inputs
	pinMode(SENSOR_PIN_START, INPUT);
	pinMode(SENSOR_PIN_END, INPUT);

	// Attach interrupt handlers for both GPIOs
	attachInterrupt(SENSOR_PIN_START, isrStartTime, RISING);
	attachInterrupt(SENSOR_PIN_END, isrEndTime, RISING);

	// Initialize timer
	timer_config_t config = {
		.alarm_en = TIMER_ALARM_EN,
		.counter_en = TIMER_START,
		.counter_dir = TIMER_COUNT_UP,
		.auto_reload = TIMER_AUTORELOAD_EN,
		.divider = TIMER_DIVIDER
	};
	timer_init(TIMER_GROUP_0, TIMER_0, &config);
	timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0);  // Start timer at 0
}

void loop() 
{
	if (timeIsValid) 
	{
		float timeDiffSec = (float)timeDiff / TIMER_TICKS_PER_US;
		float speed = SENSOR_DISTANCE / timeDiffSec;

		Serial.printf("Time = %u µs, Speed = %.3f m/s (%.2f km/h)\n", timeDiff, speed, speed * 3.6);
		timeIsValid = false;
	}
}

