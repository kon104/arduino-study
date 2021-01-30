
#define LED 13
#define BLINK_MSEC 1000

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("The LED turns on.");
  digitalWrite(LED, HIGH);
  delay(BLINK_MSEC);
  Serial.println("The LED turns off.");
  digitalWrite(LED, LOW);
  delay(BLINK_MSEC);
}
