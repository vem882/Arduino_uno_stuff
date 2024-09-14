volatile int counter = 0;  
void setup() {
  pinMode(2, INPUT_PULLUP);  
  pinMode(3, INPUT_PULLUP);  

  attachInterrupt(digitalPinToInterrupt(2), increaseCounter, FALLING);  
  attachInterrupt(digitalPinToInterrupt(3), decreaseCounter, FALLING);  

  Serial.begin(9600);
}

void loop() {
  Serial.println(counter);
  delay(1000);
  }


void increaseCounter() {
  counter++;  // Kasvatetaan muuttujaa napin painalluksesta (pinni 2)
}

void decreaseCounter() {
  counter--;  // Vähennetään muuttujaa napin painalluksesta (pinni 3)
}
