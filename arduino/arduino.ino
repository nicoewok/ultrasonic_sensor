const int triggerP1 = 9;
const int echoP1 = 10;
const int triggerP2 = 12;
const int echoP2 = 13;


void setup() {
  pinMode(triggerP1, OUTPUT);
  pinMode(echoP1, INPUT);
  pinMode(triggerP2, OUTPUT);
  pinMode(echoP2, INPUT);
  Serial.begin(9600);
}

void triggerFun(triggerP, time1, time2) {
  digitalWrite(triggerP, LOW);
  delayMicroseconds(time1);
  digitalWrite(triggerP, HIGH);
  delayMicroseconds(time2);
  digitalWrite(triggerP, LOW);
}

void distReadOut(echoP) {
  float duration = pulseIn(echoP, HIGH);
  float distance = duration * 0.00034 / 2;  //340 m/s, 0.34 m/ms, 0.00034m/microsecond
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" m on pin");
  Serial.print(echoP);
  Serial.println(" m");
}

void loop() {
  writeTrigger(triggerP1, 2, 10);
  distReadOut(echoP1);
  writeTrigger(triggerP2, 2, 10);
  distReadOut(echoP2);
  
  delay(1000);
}