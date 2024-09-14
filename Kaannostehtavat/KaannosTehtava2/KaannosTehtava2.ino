#include "esimerkkiheader.h"

int foo = 0;  
int bar = 0;

void setup() {
  Serial.begin(BAUDINOPEUS); 
}

void loop() {
  while (1)
  {
    Serial.println("Give first number");
    while (Serial.available() == 0)
    {
    }
    foo = Serial.parseInt();

    Serial.println("And give now second number");
    while (Serial.available() == 0)
    {
    }
    bar = Serial.parseInt();  

    Serial.print(foo);
    Serial.print(" + ");
    Serial.print(bar);
    Serial.print(" = ");
    Serial.println(summa_aliohjelma(foo, bar));  
  }
} 
