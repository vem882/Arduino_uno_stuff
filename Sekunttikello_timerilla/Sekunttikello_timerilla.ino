/*
Tehtävä: 
Tee sekuntikello käyttäen Loop-rakennetta ja Timeria. Sekuntikellon tulee laskea sekunnin kymmenyksiä, sekunteja ja minuutteja

- Sekuntikello käynnistetään maadoittamalla pinni 2 (voit käyttää keskeytyksiä apuna)

- Sekuntikello päivittää ajan sarjaportille sekunnin välein.

- Sekuntikello pysäytetään maadoittamalla pinni 3, jolloin tulostetaan tarkka aika kymmenyksineen, ja nollataan aika uutta ajanottoa varten.

*/
// Pinnit
const int startPin = 2;  // Pinni 2: Sekuntikellon käynistykseen
const int stopPin = 3;   // Pinni 3: Sekuntikellon pysäyttämiseen

volatile boolean running = false;
volatile boolean stopped = false;

// Ajan muuttujat
unsigned long previousMillis = 0;
unsigned long timeElapsed = 0;  // Aika millisekunneissa
unsigned long deciseconds = 0;  // Sekunnin kymmenykset
unsigned long seconds = 0;      // Sekunnit
unsigned long minutes = 0;      // Minuutit

void setup() {
  pinMode(startPin, INPUT_PULLUP);  // Start-pinni
  pinMode(stopPin, INPUT_PULLUP);   // Stop-pinni

  // Keskeytykset
  attachInterrupt(digitalPinToInterrupt(startPin), startTimer, FALLING);
  attachInterrupt(digitalPinToInterrupt(stopPin), stopTimer, FALLING);

  Serial.begin(9600);  // Sarjaportin alustus
}

void loop() {
  if (running) {
    unsigned long currentMillis = millis();
    
    // Tarkistetaan, onko 100 millisekuntia kulunut
    if (currentMillis - previousMillis >= 100) {
      previousMillis = currentMillis;
      timeElapsed += 100;
      
      deciseconds++;
      if (deciseconds >= 10) {
        deciseconds = 0;
        seconds++;
        
        if (seconds >= 60) {
          seconds = 0;
          minutes++;
        }
      }
      
      // Päivitetään aika sarjaporttiin sekunnin välein
      if (seconds % 1 == 0 && deciseconds == 0) {
        Serial.print("Aika: ");
        Serial.print(minutes);
        Serial.print(" min, ");
        Serial.print(seconds);
        Serial.println(" sek.");
      }
    }
  }

  if (stopped) {
    // Tulostetaan tarkka aika pysäytyksen yhteydessä
    Serial.print("Lopullinen aika: ");
    Serial.print(minutes);
    Serial.print(" min, ");
    Serial.print(seconds);
    Serial.print(" sek, ");
    Serial.print(deciseconds);
    Serial.println(" kymmenystä.");
    
    // Nollataan ajanottoa varten
    deciseconds = 0;
    seconds = 0;
    minutes = 0;
    timeElapsed = 0;
    stopped = false;
  }
}

void startTimer() {
  running = true;
}

void stopTimer() {
  running = false;
  stopped = true;
}
