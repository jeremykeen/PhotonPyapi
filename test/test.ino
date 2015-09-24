void setup(){
  pinMode(D7,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(D7, !digitalRead(D7));
  Serial.println("test");
  delay(200);
}
