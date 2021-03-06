#define DEBUGLOG 0

#if DEBUGLOG
// definitions to log for debug when not to use 'keyboard.h'.
#define KEY_UP_ARROW    'U'
#define KEY_DOWN_ARROW  'D'
#define KEY_LEFT_ARROW  'L'
#define KEY_RIGHT_ARROW 'R'
#else
#include "Keyboard.h"
#endif

#define BIKE_PIN 4
#define LED_PIN 13

#define SW_PIN 7
#define X_PIN A0
#define Y_PIN A3

#define WAITING_MSEC 125

#define MAX_ROTATION 3
int rotation = 0;
boolean stat_p = false;

#define MAX_POS 1024
boolean stat_l = false;
boolean stat_r = false;
boolean stat_u = false;
boolean stat_d = false;

void printNumberOfRotation(int now, int max) {
  Serial.print("The pedal has rotated ");
  Serial.print(rotation);
  Serial.print("/");
  Serial.print(MAX_ROTATION);
  Serial.println(" times.");
}

void printKeyboardEvent(String event, char key) {
  Serial.print(event);
  Serial.print(" keyboard [");
  Serial.print(key);
  Serial.println("]");
}

boolean ctrlStick2KeySmall(int pos, boolean stat, char key) {
  if (pos < (MAX_POS / 5)) {
    if (!stat) {
      Keyboard.press(key);
      stat = true;
      printKeyboardEvent("Pressed", key);
    }
  } else {
    if (stat) {
      Keyboard.release(key);
      stat = false;
      printKeyboardEvent("Released", key);
    }
  }
  return stat;
}

boolean ctrlStick2KeyLarge(int pos, boolean stat, char key) {
  if (pos > (MAX_POS - MAX_POS / 5)) {
    if (!stat) {
      Keyboard.press(key);
      stat = true;
      printKeyboardEvent("Pressed", key);
    }
  } else {
    if (stat) {
      Keyboard.release(key);
      stat = false;
      printKeyboardEvent("Released", key);
    }
  }
  return stat;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Keyboard.begin();
  pinMode(BIKE_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pedal = digitalRead(BIKE_PIN);
  if (pedal == LOW) {
    if (!stat_p) {
      rotation++;
      printNumberOfRotation(rotation, MAX_ROTATION);
      if (rotation >= MAX_ROTATION) {
        Keyboard.press(KEY_UP_ARROW);
        Keyboard.release(KEY_UP_ARROW);
        digitalWrite(LED_PIN, HIGH);
        delay(WAITING_MSEC);
        digitalWrite(LED_PIN, LOW);
        rotation = 0;
      }
      stat_p = true;
    }
  } else {
    stat_p = false;
  }
  int x_pos = analogRead(X_PIN);
  int y_pos = analogRead(Y_PIN);
  stat_d = ctrlStick2KeySmall(x_pos, stat_d, KEY_DOWN_ARROW);
  stat_u = ctrlStick2KeyLarge(x_pos, stat_u, KEY_UP_ARROW);
  stat_l = ctrlStick2KeySmall(y_pos, stat_l, KEY_LEFT_ARROW);
  stat_r = ctrlStick2KeyLarge(y_pos, stat_r, KEY_RIGHT_ARROW);
}
