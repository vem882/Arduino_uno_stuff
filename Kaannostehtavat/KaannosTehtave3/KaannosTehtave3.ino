void setup() {
  Serial.begin(9600);
  Serial.println("Give number between 0-9");
}

void loop() {
  if (Serial.available() > 0) {
    int foo = Serial.parseInt(); 
    printFunction(foo);
    while (true) {} 
  }
}

void printFunction(int bar)
{
  Serial.print("You gave number = ");
  Serial.println(bar);
}
