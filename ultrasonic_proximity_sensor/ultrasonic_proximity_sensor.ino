#define spkrPin 7
#define trigPin 10
#define echoPin 9

long duration;
int distance;

void setup() {
  pinMode(spkrPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

void loop() {
  distance = getDistance();
  if(distance > 30) {
    distance = 30;
  }
  
  //1cm ==> 1Hz
  tone(spkrPin, 1760-(distance*20));
  delay(60);
  noTone(spkrPin);
  delay((31.33*distance) + 60);
}
