# Ultrasonic Sensor Project

This project uses an Arduino and an ultrasonic sensor to measure distances.

## Components

- Arduino Uno
- Ultrasonic Sensor (HC-SR04)
- Breadboard
- Jumper wires

## Circuit Diagram

![Circuit Diagram](path_to_circuit_diagram_image)

## Installation

1. Connect the ultrasonic sensor to the Arduino as follows:
    - VCC to 5V
    - GND to GND
    - Trig to Digital Pin 9
    - Echo to Digital Pin 10

2. Upload the following code to the Arduino:

```cpp
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(1000);
}
```

## Usage

1. Open the Serial Monitor in the Arduino IDE.
2. Observe the distance readings displayed in the Serial Monitor.

## License

This project is licensed under the MIT License.