const float distSensors = 10.0f;

const int triggerP1 = 11;
const int echoP1 = 10;
const int triggerP2 = 3;
const int echoP2 = 2;

float lastDist1 = 0.0f;
float lastDist2 = 0.0f;
int change1 = 0;
int change2 = 0;

float startTime = 0.0f;
float endTime = 0.0f;

void setup() {
  pinMode(triggerP1, OUTPUT);
  pinMode(echoP1, INPUT);
  pinMode(triggerP2, OUTPUT);
  pinMode(echoP2, INPUT);
  Serial.begin(9600);
}

void writeTrigger(int triggerP, int time1, int time2) {
  digitalWrite(triggerP, LOW);
  delayMicroseconds(time1);
  digitalWrite(triggerP, HIGH);
  delayMicroseconds(time2);
  digitalWrite(triggerP, LOW);
  return;
}

float distReadOut(int echoP) {
  float duration = pulseIn(echoP, HIGH);
  float distance = duration * 0.034 / 2;  //340 m/s, 0.34 m/ms, 0.00034m/microsecond 0.034cm/microsecond
  return distance;
}

float getDistance(int triggerP, int echoP) {
  writeTrigger(triggerP, 2, 10);
  return distReadOut(echoP);
}

int detectChange(int triggerP, int echoP, float *lastDist) {
  float dist = getDistance(triggerP, echoP);
  //if starting
  float diff = 0.0f;
  if (*lastDist != 0.0f)
    diff = dist - *lastDist;
  *lastDist = dist;

  //check if negative
  diff = (diff < 0.0f) ? diff * -1 : diff;
  //check if it changed a lot
  return (diff > 20.0f) ? 1 : 0;
}


void loop() {

  //If no starttime, look at first sensor
  if (startTime == 0.0f) {
    change1 += detectChange(triggerP1, echoP1, &lastDist1);
    delay(100);
    //We want object to enter and exit
    if (change1 >= 2) {
      change1 = 0;
      Serial.println("Starting timer..");
      startTime = micros();
      return;
    }
  }
  
  //Look at second sensor only if timer started
  if (startTime > 0.0f) {
    change2 += detectChange(triggerP2, echoP2, &lastDist2);
    delay(100);
    if (change2 >= 2) {
      change2 = 0;
      Serial.println("End timer..");
      endTime = micros();

      unsigned long elapsedTime = endTime - startTime; // Time in microseconds
      startTime = 0.0f;
      endTime = 0.0f;
      float speed = (distSensors / elapsedTime) * 1000000.0; // cm/s
      Serial.print("Speed: ");
      Serial.print(speed);
      Serial.print("cm/s or ");
      Serial.print(speed*0.036f);
      Serial.print(" km/h ");
      Serial.print("(elapsed time: ");
      Serial.print(elapsedTime/1000000.0f);
      Serial.println(" s)");
      return;
    }
  }
}