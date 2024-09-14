/*
  Tee aliohjelma, joka lukee 10 A/D-näytettä taulukkoon ADnaytteet.
  Tämän jälkeen aliohjelma etsii näytteistä suurimman ja pienimmän alkion
  sekä laskee 10 näytteen keskiarvon. Lopuksi aliohjelma palauttaa
  laskemansa 3 arvoa kutsujalle.

  Vinkki: Koska C-aliohjelmasta voi return käskyllä palauttaa vain
          yhden paluuarvon voit tehdä tuosta paluuarvosta structin,
          joka sisältää nuo kolme arvoa. Tai voit välittää aliohjelmalle
          kolme pointteria, joiden avulla aliohjelma voi tallentaa tulokset
          pointtereiden osoittamiin muistipaikkoihin, jotka aliohjelman
          kutsuja on allokoinut.

  Vinkki2: Tehtävässä ei ole nyt annettu aliohjelman prototyyppiä = esittelyä
           eikä aliohjelman runkoa valmiina, mutta voit katsoa mallia edellisestä
           tehtävästä.
*/


int ADnaytteet[10]; // tallennetaan 10 näytettä

void setup() {
  Serial.begin(9600); // Sarjayhteys
}

void loop() {
  int suurin, pienin, keskiarvo; // Muuttujat johon tulee tulokset.
  
  // Kutsutaan  aliohjelmaa ja annetaan sille osoitteet muuttujista
  lue10ADmuuntimenArvot(&suurin, &pienin, &keskiarvo);

  // Printataan tulokset sarjamonitorille
  Serial.print("Suurin: ");
  Serial.println(suurin);
  Serial.print("Pienin: ");
  Serial.println(pienin);
  Serial.print("Keskiarvo: ");
  Serial.println(keskiarvo);

  delay(1000); // Luodaan viime mittauksien välillä
}

void lue10ADmuuntimenArvot(int *suurin, int *pienin, int *keskiarvo) {
  int summa = 0;
  
  // Luetaan 10 A/D-muuntimen arvoa ja tallennetaan tulokset taulukkoon ADnaytteet
  for (int i = 0; i < 10; i++) {
    ADnaytteet[i] = analogRead(A0); // Aktivoidaan portti A0
    summa += ADnaytteet[i]; // Lisätään arvot taulukkoon ADnaytteet
    
    if (i == 0) {
      // Alustetaan suurin ja pienin arvolla
      *suurin = ADnaytteet[i];
      *pienin = ADnaytteet[i];
    } else {
      // Tarkistetaan onko suurin ja pienin
      if (ADnaytteet[i] > *suurin) {
        *suurin = ADnaytteet[i];
      }
      if (ADnaytteet[i] < *pienin) {
        *pienin = ADnaytteet[i];
      }
    }
    
    delay(10); // Luodaan tauko 
  }
  
  // laksetaan keskiarvo
  *keskiarvo = summa / 10;
}
