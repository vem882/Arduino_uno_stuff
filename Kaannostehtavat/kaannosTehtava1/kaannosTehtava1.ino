void printSubroutine(String s);

void setup() {
  Serial.begin(9600);
}

void loop() {
  printSubroutine("This works fine");
  delay(1000);  
}

void printSubroutine(String s)
{
  Serial.println(s);
}

