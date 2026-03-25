#define DIAL_PIN     1
#define JOYSTICK_PIN 2
#define ON_PIN       4
#define START_PIN    5

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(DIAL_PIN,     INPUT_PULLUP);
  pinMode(JOYSTICK_PIN, INPUT_PULLUP);
  pinMode(ON_PIN,       INPUT_PULLUP);
  pinMode(START_PIN,    INPUT_PULLUP);

  Serial.println("Ready - trigger each input");
}

void loop() {

  if (digitalRead(DIAL_PIN) == LOW)
    Serial.println("DIAL triggered");

  if (digitalRead(JOYSTICK_PIN) == LOW)
    Serial.println("JOYSTICK triggered");

  if (digitalRead(ON_PIN) == LOW)
    Serial.println("ON/OFF triggered");

  if (digitalRead(START_PIN) == LOW)
    Serial.println("START triggered");

  delay(1000);
}