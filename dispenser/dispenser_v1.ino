// brown  wire to ground
// red    wire to 5V power
// orange wire to servo_port definition (can be an analog or digital port)

#define servo_port 8
#define trigPin 10
#define echoPin 9
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
//twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(servo_port);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int dist = getDistance();   // distance from hand to sensor
  int pos = 0;    // position of the servo motor in degrees
  
  if(dist <= 30) {
    pos = (-4.5*dist) + 135;
  }
  else {
    pos = 0;
  }

  myservo.write(pos);
}

void dispense() {
  myservo.write(0);
  delay(500);
  myservo.write(90);
  delay(500);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}
