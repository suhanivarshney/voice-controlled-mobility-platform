# voice-controlled-mobility-platform
This project presents a voice controlled mobility platform designed to enhance independent navigation and accessibility using low-cost, open-source hardware. The system interprets voice commands from a mobile application and converts them into real-time motor control actions, while simultaneously ensuring user safety through obstacle detection.

The platform is built around an Arduino Uno, which runs continuously to manage command execution and safety monitoring in parallel. Voice inputs are transmitted via Bluetooth and translated into directional motor signals, allowing intuitive hands-free control.
To prevent collisions, an ultrasonic sensing-based safety algorithm is implemented. The system immediately overrides user commands and cuts motor power whenever an obstacle is detected within a critical distance threshold.

Key Components:

Arduino Uno
Acts as the central controller, executing firmware written in C/C++ to handle command processing and safety logic concurrently.

Bluetooth Module (HC-07)
Provides a wireless interface to receive voice-to-text commands from a mobile application and translate them into simplified motor control instructions.

Ultrasonic Sensor (HC-SR04)
Enables real-time obstacle detection. A custom safety algorithm halts motor operation instantly when objects are detected within 15 cm, ensuring collision avoidance.

Motor Driver (L298N Dual H-Bridge)
Drives the DC motors efficiently while electrically isolating low-voltage control logic from the high-current 12V motor power supply.
