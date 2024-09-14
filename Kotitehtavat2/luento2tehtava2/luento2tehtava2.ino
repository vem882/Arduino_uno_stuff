int ADnaytteet[10]; // tähän tallennetaan 10 näytettä

void setup() {
  Serial.begin(9600); // Sarjayhteys
}

void loop() {
  // Kutsu aliohjelmaa ja tulosta sen palauttama keskiarvo
  int keskiarvo = lue10ADmuuntimenArvoaJaLaskeKeskiarvo();
  Serial.print("Keskiarvo: ");
  Serial.println(keskiarvo);

  delay(1000); // Luodaan tauko
}

int lue10ADmuuntimenArvoaJaLaskeKeskiarvo(void) {
  int summa = 0; 
  
  // Luetaan 10 A/D-muuntimen arvoa ja tallennetaan ne taulukkoon ADnaytteet
  for (int i = 0; i < 10; i++) {
    ADnaytteet[i] = analogRead(A0); // Aktivoidaan portti analooginen portti A0.
    summa += ADnaytteet[i]; // Lisätään arvon summaan
    delay(10); // luodaan tauko/viive näytteiden ottamisen välillä.
  }

  // Lasketaan keskiarvo jakamalla summa 10:llä
  int keskiarvo = summa / 10;
  
  return keskiarvo; // Palautetaan keskiarvo kutsujalle
}
