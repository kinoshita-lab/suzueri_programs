#define IN_A 2
#define IN_B 3
#define ENABLE_PIN 4

#define PulseWidth 2

void setup() {
  pinMode(IN_A, OUTPUT);
  pinMode(IN_B, OUTPUT);

}

void doDelay()
{
//  digitalWrite(ENABLE_PIN, LOW);  
  const auto ad = analogRead(0);
  delay(ad >> 4);
//  digitalWrite(ENABLE_PIN, HIGH);
}
void loop() {
  
  digitalWrite(IN_A, HIGH);
  digitalWrite(IN_B, HIGH);
  delay(PulseWidth);
  doDelay();
  
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, HIGH);
  delay(PulseWidth);
  doDelay();
  
  digitalWrite(IN_A, LOW);
  digitalWrite(IN_B, LOW);
  delay(PulseWidth);
  doDelay();
  
  digitalWrite(IN_A, HIGH);
  digitalWrite(IN_B, LOW);
  delay(PulseWidth);
  doDelay();
}
