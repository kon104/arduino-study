
#define SW_PIN 2
#define X_PIN A0
#define Y_PIN A1

int sw_state = 0;
int x_pos = 0;
int y_pos = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sw_state = digitalRead(SW_PIN);
  x_pos = analogRead(X_PIN);
  y_pos = analogRead(Y_PIN);
    
  Serial.print("SW = ");
  Serial.print(sw_state);
  Serial.print(", X = ");
  Serial.print(x_pos);  
  Serial.print(", Y = ");
  Serial.print(y_pos);

  if (x_pos < 256) {
    Serial.print(" [LEFT]");
  } else
  if (x_pos > 768) {
    Serial.print(" [RIGHT]");
  }
  if (y_pos < 256) {
    Serial.print(" [UP]");
  } else
  if (y_pos > 768) {
    Serial.print(" [DOWN]");
  }

  Serial.println("");
  delay(500);
}
