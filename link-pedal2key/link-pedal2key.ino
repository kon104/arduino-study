

#define BIKE 7
#define LED 13
#define WAITING_MSEC 500
#define MAX_ROTATION 3
int HighLow = LOW;
int rotation = 0;

void printNumberOfRotation(int now, int max) {
  Serial.print("The pedal has rotated ");
  Serial.print(rotation);
  Serial.print("/");
  Serial.print(MAX_ROTATION);
  Serial.println(" times.");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BIKE, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  HighLow = digitalRead(BIKE);
  if (HighLow == LOW) {
    rotation++;
    printNumberOfRotation(rotation, MAX_ROTATION);
    if (rotation >= MAX_ROTATION) {
      digitalWrite(LED, HIGH);
      delay(WAITING_MSEC);
      digitalWrite(LED, LOW);
      rotation = 0;
    } else {
      delay(WAITING_MSEC);     
    }    
  }
}
