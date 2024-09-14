#include <Arduino_FreeRTOS.h>

// Globaali muuttuja, joka tallentaa lukeman
volatile int sharedValue = 0;

// Määritellään kaksi tehtävää
void TaskReadSerial( void *pvParameters );
void TaskDecrement( void *pvParameters );

void setup() {
  // Aloita sarjayhteys
  Serial.begin(9600);
  
  // Odotetaan, että sarjaportti kytkeytyy (esim. Leonardo, Micro, jne.)
  while (!Serial) {
    ; // Odotetaan
  }

  // Luodaan tehtävät
  xTaskCreate(
    TaskReadSerial,  // Tehtävä, joka lukee sarjaporttia
    "ReadSerial",    // Tehtävän nimi
    128,             // Stack-koko
    NULL,            // Parametrit (ei käytössä tässä)
    2,               // Prioriteetti (2 korkeampi kuin TaskDecrement)
    NULL);           // Task-handle (ei tarvita tässä)

  xTaskCreate(
    TaskDecrement,   // Tehtävä, joka vähentää muuttujan arvoa
    "Decrement",     // Tehtävän nimi
    128,             // Stack-koko
    NULL,            // Parametrit (ei käytössä tässä)
    1,               // Prioriteetti (alhaisempi kuin TaskReadSerial)
    NULL);           // Task-handle (ei tarvita tässä)

  // FreeRTOS aloittaa tehtävien ajamisen automaattisesti
}

void loop() {
  // loop() jätetään tyhjäksi, koska FreeRTOS hoitaa tehtävien ajon
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

// Tehtävä 1: Lukee sarjaportista numeroita ja lisää ne sharedValue-muuttujaan
void TaskReadSerial(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    if (Serial.available() > 0) {
      int incomingValue = Serial.parseInt();  // Luetaan sarjaportista luku

      // Päivitetään sharedValue
      sharedValue += incomingValue;
      Serial.print("Added: ");
      Serial.println(incomingValue);
      Serial.print("New Value: ");
      Serial.println(sharedValue);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);  // Viive 10 ms seuraavaa tarkistusta varten
  }
}

// Tehtävä 2: Vähentää sharedValue-muuttujaa kerran sekunnissa, jos arvo on yli 0
void TaskDecrement(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    if (sharedValue > 0) {
      sharedValue--;  // Vähennetään arvoa
      Serial.print("Decremented Value: ");
      Serial.println(sharedValue);
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);  // Odotetaan 1 sekunti
  }
}