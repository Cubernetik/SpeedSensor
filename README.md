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

  - Higher Precision: The system can be adapted for higher-speed measurements by increasing timer resolution or using more advanced techniques like      the RMT peripheral.

## Conclusion

## Model files
Model files for 3D printing are available here: https://makerworld.com/en/models/1217145-speed-sensor-tube#profileId-1233233

## Schematic
Schematic for the IR proximity sensor board. Schematic and board located in kicad folder.
![IR proximity sensor board](Speed-Sensor-Schematic.png)

## Example Measurements
The relative error shows room for improvement. Unfortunately lacking a RS flip flop to make a rising and a falling edge out of the two
rising edges. Once I have this done I will use RMT to count the distance of those two edges which can be done with 12.5 ns resolution
on hardware level. The precision should be sufficient after this change.
 - Time = 45332 µs, Speed = 0.662 m/s (2.38 km/h)
 - Time = 46816 µs, Speed = 0.641 m/s (2.31 km/h)
 - Time = 42106 µs, Speed = 0.712 m/s (2.56 km/h)
 - Time = 43452 µs, Speed = 0.690 m/s (2.49 km/h)
