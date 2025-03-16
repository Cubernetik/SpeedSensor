# ESP32 Timer-Based Pulse Distance Measurement

This is the source code to test an optical sensor to measure speed by time and distance. I use it for my experimental rail gun,
specifically for auto tuning the coil timing to maximize speed. This is an experiment and will not result in a rail gun with
notable projectile energy and is a mere physics experiment.

This implementation demonstrates how to measure the distance (time difference) between two GPIO pulses using the ESP32. It uses
hardware-level timers for precise measurement and ensures correct handling of timer overflows. The solution accounts for GPIO interrupts,
timer configurations, and overflow management.

## How It Works

  - GPIO Setup: The two GPIO pins (26 and 27) are set as inputs, and interrupts are attached to both to trigger on the rising edge of the signal.
  - Interrupt Service Routines (ISRs): The ISRs capture the current time (using the timer's counter) when a rising edge is detected.
  - Timer Configuration: A timer is configured to run with 1 µs resolution, allowing precise time tracking for the pulse measurement.
  - Time Difference Calculation: When both GPIO pins trigger, the time difference is calculated using the stored timer values. The calculation
    handles the potential timer overflow, ensuring the result remains accurate.

## Future Improvements

  - Higher Precision: The system can be adapted for higher-speed measurements by increasing timer resolution or using more advanced techniques like the RMT peripheral.
  - Add a schematic for the sensor circuit.

## Conclusion

This implementation provides a robust solution for measuring the time difference between two GPIO pulses on the ESP32. It leverages the hardware timers for high precision,
handles overflow gracefully, and uses interrupts for real-time processing. This solution can be expanded further depending on the specific requirements of your project.

## Model files
Model files for 3D printing are available here: https://makerworld.com/en/models/1217145-speed-sensor-tube#profileId-1233233
