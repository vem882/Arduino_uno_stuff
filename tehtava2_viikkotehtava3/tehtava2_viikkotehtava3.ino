// Määritellään pinnit
#define PIN_1 4
#define PIN_2 5
#define PIN_3 6
#define PIN_4 7

// Muuttujat pinien tilan seuraamiseen
int lastState_PIN_1 = HIGH;
int lastState_PIN_2 = HIGH;
int lastState_PIN_3 = HIGH;
int lastState_PIN_4 = HIGH;

void setup() {
  Serial.begin(9600);  
  pinMode(PIN_1, INPUT_PULLUP);
  pinMode(PIN_2, INPUT_PULLUP);
  pinMode(PIN_3, INPUT_PULLUP);
  pinMode(PIN_4, INPUT_PULLUP);
}

void loop() {
  // Tarkistetaan PIN_1:n tila
  int currentState_PIN_1 = digitalRead(PIN_1);
  if (currentState_PIN_1 == LOW && lastState_PIN_1 == HIGH) {
    Serial.println("Pinni 4 triggeroitu");
  }
  lastState_PIN_1 = currentState_PIN_1;

  // Tarkistetaan PIN_2:n tila
  int currentState_PIN_2 = digitalRead(PIN_2);
  if (currentState_PIN_2 == LOW && lastState_PIN_2 == HIGH) {
    Serial.println("Pinni 5 triggeroitu");
  }
  lastState_PIN_2 = currentState_PIN_2;

  // Tarkistetaan PIN_3:n tila
  int currentState_PIN_3 = digitalRead(PIN_3);
  if (currentState_PIN_3 == LOW && lastState_PIN_3 == HIGH) {
    Serial.println("Pinni 6 triggeroitu");
  }
  lastState_PIN_3 = currentState_PIN_3;

  // Tarkistetaan PIN_4:n tila
  int currentState_PIN_4 = digitalRead(PIN_4);
  if (currentState_PIN_4 == LOW && lastState_PIN_4 == HIGH) {
    Serial.println("Pinni 7 triggeroitu");
  }
  lastState_PIN_4 = currentState_PIN_4;
}
