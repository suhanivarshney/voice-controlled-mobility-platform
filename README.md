# Voice-Controlled Wheelchair 

## Overview
An assistive technology project designed to enhance mobility for people with physical disabilities. The wheelchair is controlled via single-character Bluetooth commands (F/B/L/R/S) sent from a smartphone app. A servo-mounted ultrasonic sensor actively scans for obstacles — rotating left or right during turns to check the path — and automatically stops the wheelchair if an obstacle is detected within 15cm while moving forward.

## Features
- 🎙️ Voice command control via smartphone Bluetooth app
- ⬆️ ⬇️ ◀️ ▶️ Commands: Forward, Backward, Left, Right, Stop
- 🚧 Servo-mounted ultrasonic sensor — rotates to scan direction of travel during turns
- 📶 Wireless communication via HC-07 Bluetooth module (SoftwareSerial)
- ⚡ Real-time dual motor control using L298N motor driver
- ♿ Built to assist people with physical disabilities

- ## Hardware Components
| Component | Purpose |
|-----------|---------|
| Arduino Uno | Main microcontroller — processes commands and controls all modules |
| HC-07 Bluetooth Module | Receives commands wirelessly from smartphone |
| L298N Motor Driver | Drives Motor A and Motor B based on Arduino signals |
| HC-SR04 Ultrasonic Sensor | Mounted on servo — detects obstacles, triggers auto-stop at 15cm |
| Servo Motor | Rotates ultrasonic sensor to scan left/right during turns |
| DC Motors (×2) | Powers the wheelchair wheels (Motor A = Left, Motor B = Right) |
| 12V Battery | Power supply for motors and electronics |
| Smartphone | Sends voice commands via pre-built Bluetooth terminal app |

## System Architecture
Smartphone
(Bluetooth App — Voice to F/B/L/R/S)
        ↓  Bluetooth
   HC-07 Module (D10/D11)
        ↓  SoftwareSerial
   Arduino Uno
     ↙       ↓        ↘
L298N      Servo      Ultrasonic
Motor      (D3)       Sensor
Driver     rotates    (D12/D13)
(D4-D9)    sensor     auto-stop
   ↓                  at 15cm
DC Motors A & B

## Voice Commands
| App Input | Character Sent | Action | Servo Position |
|-----------|---------------|--------|----------------|
| "Forward" | `F` | Both motors forward | 90° (front) |
| "Backward" | `B` | Both motors backward | 90° (front) |
| "Left" | `L` | Stop → Left turn | 180° (scans left) |
| "Right" | `R` | Stop → Right turn | 0° (scans right) |
| "Stop" | `S` | Both motors stop | 90° (center) |

## Pin Connections
| Arduino Pin | Connected To | Purpose |
|-------------|-------------|---------|
| D3 | Servo Motor signal | Rotates ultrasonic sensor |
| D4 (IN1) | L298N IN1 | Motor A direction |
| D5 (IN2) | L298N IN2 | Motor A direction |
| D6 (IN3) | L298N IN3 | Motor B direction |
| D7 (IN4) | L298N IN4 | Motor B direction |
| D8 (ENA) | L298N ENA | Motor A enable (HIGH) |
| D9 (ENB) | L298N ENB | Motor B enable (HIGH) |
| D10 (RX) | HC-07 TX | Bluetooth receive |
| D11 (TX) | HC-07 RX | Bluetooth transmit |
| D12 | HC-SR04 TRIG | Ultrasonic trigger |
| D13 | HC-SR04 ECHO | Ultrasonic echo |
| 5V, GND | All modules | Power supply |
| External 12V Battery | L298N VCC | Motor power supply (direct, not via Arduino) |

## How It Works
1. User speaks a command into the smartphone Bluetooth app
2. App converts speech to text and sends a single character — `F`, `B`, `L`, `R`, or `S` — over Bluetooth
3. HC-07 receives the character and passes it to Arduino via SoftwareSerial (D10/D11)
4. Arduino reads the character and executes the corresponding motor function
5. For Left/Right turns — Arduino first stops motors, rotates servo to scan that direction (500ms delay), then turns
6. Ultrasonic sensor continuously measures distance every 50ms loop cycle
7. If moving forward and distance ≤ 15cm — Arduino immediately stops both motors as a safety override

## How to Run
1. Clone this repository
2. Open `wheelchair.ino` in Arduino IDE
3. Install **SoftwareSerial** and **Servo** libraries (both included with Arduino IDE by default)
4. Connect Arduino Uno to PC via USB
5. Select **Board:** Arduino Uno and correct **COM Port**
6. Upload the code
7. Disconnect USB — power via 12V battery
8. On smartphone, pair with HC-07 (default PIN: `1234`)
9. Open Bluetooth terminal app → enable voice input
10. Speak a command → wheelchair responds in real time

## Safety Features
- **Obstacle auto-stop** — ultrasonic sensor halts motors immediately if object ≤ 15cm while moving forward
- **Directional scanning** — servo rotates sensor toward the turn direction before executing left/right
- **Default stop state** — motors are OFF at startup, only activate on valid command
- **Backward override** — obstacle detection is intentionally disabled during reverse (avoids false triggers)

## Tools & Technologies
| Tool | Purpose |
|------|---------|
| Arduino IDE | Code development and uploading |
| C++ | Arduino programming language |
| SoftwareSerial Library | Bluetooth communication on D10/D11 |
| Servo Library | Servo motor control on D3 |
| Pre-built Bluetooth App | Voice command input via smartphone |

## Future Improvements
- Build a custom Android app with dedicated voice command buttons
- Add PWM speed control for variable motor speed
- Add LCD/OLED display to show current received command
- Integrate GPS module for location tracking
- Add gyroscope-based tilt safety cutoff
- Expand obstacle detection to backward movement as well

## Applications
This project directly addresses accessibility challenges for individuals with:
- Spinal cord injuries
- Muscular dystrophy
- ALS and other motor neuron diseases
- Any condition limiting lower limb mobility
