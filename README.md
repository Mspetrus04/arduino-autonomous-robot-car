# Arduino Autonomous Robot Car 🤖

An autonomous two-wheel robot car built with Arduino Uno, featuring ultrasonic obstacle detection, servo-based environmental scanning, and PWM motor control.

This project provides an alternative implementation for the **Playknowlogy Arduino Robot Car Kit**, focusing on readable C++ code, configurable navigation behavior, and beginner-friendly documentation.

## Project Overview

The robot uses an ultrasonic sensor mounted on a servo motor to detect obstacles and navigate its surroundings.

When an obstacle is detected, the robot stops, scans both directions, and attempts to turn toward the direction with more available space.

The project was developed through hands-on experimentation, hardware troubleshooting, and iterative software improvements.

## Features

- Autonomous obstacle avoidance
- Ultrasonic distance measurement
- Servo-controlled left and right scanning
- Independent PWM control of two DC motors
- Adjustable motor calibration
- Configurable obstacle detection thresholds
- Reduced driving speed near obstacles
- Serial Monitor debugging output

## Hardware

The project is based on the Playknowlogy Arduino Robot Car Kit.

| Component | Description |
|---|---|
| Microcontroller | Arduino Uno R3 |
| Motor driver | L298N |
| Motors | 2 × DC geared motors |
| Distance sensor | Ultrasonic sensor (HC-SR04 compatible) |
| Servo | SG90 micro servo |
| Battery supply | 6 × AA batteries |
| Expansion board | Arduino Sensor Shield v5.0 |
| Chassis | Two-wheel acrylic robot chassis |

## Software

- Arduino IDE
- C++
- Arduino Servo library

## How It Works

1. The robot measures the distance directly ahead.
2. If the path is clear, it moves forward.
3. When an obstacle approaches, the robot reduces its speed.
4. If an obstacle is too close, the robot stops.
5. The servo rotates the ultrasonic sensor to scan both sides.
6. The robot compares the measurements and turns toward the clearer direction.
7. The process repeats continuously.

## Getting Started

1. Assemble the robot according to the kit instructions.
2. Verify the wiring and power supply before connecting batteries.
3. Open the firmware in Arduino IDE.
4. Select **Arduino Uno** and the correct serial port.
5. Upload the program.
6. Perform the first motor test with the wheels lifted off the ground.
7. Test autonomous navigation in a clear, controlled environment.

Detailed wiring and troubleshooting documentation will be added as the project develops.

## Project Status

**Experimental — active development**

The current firmware is version 2.1.

Core functionality has been demonstrated, including motor control, ultrasonic sensing, servo scanning, and autonomous obstacle avoidance.

Motor calibration and obstacle detection are still being improved.

## Future Improvements

- More accurate motor calibration
- Improved obstacle detection and filtering
- Non-blocking navigation using `millis()`
- Smoother acceleration and turning
- More robust recovery when surrounded by obstacles
- Additional testing and documentation

## Disclaimer

This is an independent, community-oriented project and is not officially affiliated with Playknowlogy or Kjell & Company.

Always verify your wiring, voltage, and polarity before applying power.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
