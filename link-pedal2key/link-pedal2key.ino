#include "Keyboard.h"

#define BIKE_PIN 7
#define LED_PIN 13

#define SW_PIN 2
#define X_PIN A0
#define Y_PIN A1

#define WAITING_MSEC 500

#define MAX_ROTATION 3
int pedal = LOW;
int rotation = 0;

int sw_state = 0;
int x_pos = 0;
int y_pos = 0;
int flg_left = 0;
int flg_right = 0;
int flg_up = 0;
int flg_down = 0;

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
  Keyboard.begin();
  pinMode(BIKE_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  pedal = digitalRead(BIKE_PIN);
  x_pos = analogRead(X_PIN);
  y_pos = analogRead(Y_PIN);

  if (pedal == LOW) {
    rotation++;
    printNumberOfRotation(rotation, MAX_ROTATION);
    if (rotation >= MAX_ROTATION) {
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.release(KEY_UP_ARROW);
      digitalWrite(LED_PIN, HIGH);
      delay(WAITING_MSEC);
      digitalWrite(LED_PIN, LOW);
      rotation = 0;
    } else {
      delay(WAITING_MSEC);     
    }    
  } else {
    if (y_pos < 26) {
      if (flg_left == 0) {
        Keyboard.press(KEY_LEFT_ARROW);
        flg_left = 1;
      }
    } else {
      if (flg_left != 0) {
        Keyboard.release(KEY_LEFT_ARROW);
        flg_left = 0;
      }
    }
    if (y_pos > 80) {
      if (flg_right == 0) {
        Keyboard.press(KEY_RIGHT_ARROW);
        flg_right = 1;
      }
    } else {
      if (flg_right != 0) {
        Keyboard.release(KEY_RIGHT_ARROW);
        flg_right = 0;
      }
    }

    if (x_pos > 80) {
      if (flg_up == 0) {
        Keyboard.press(KEY_UP_ARROW);
        flg_up = 1;
      }
    } else {
      if (flg_up != 0) {
        Keyboard.release(KEY_UP_ARROW);
        flg_up = 0;
      }
    }
    if (x_pos < 26) {
      if (flg_down == 0) {
        Keyboard.press(KEY_DOWN_ARROW);
        flg_down = 1;
      }
    } else {
      if (flg_down != 0) {
        Keyboard.release(KEY_DOWN_ARROW);
        flg_down = 0;
      }
    }
  }
}
