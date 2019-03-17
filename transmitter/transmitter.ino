/*
NRF transmitter
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int xPin = A1;
int yPin = A0;
int buttonPin = 2;
int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

void setup() {
  Serial.begin(9600);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP);

  // For versions prior to Arduino 1.0.1
  // pinMode(buttonPin, INPUT);
  // digitalWrite(buttonPin, HIGH);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

  //Serial.print("X: ");
  //Serial.print(xPosition);
  //Serial.print(" | Y: ");
  //Serial.print(yPosition);
  //Serial.print(" | Button: ");
  //Serial.println(buttonState);

  char text[25]; // = "X: ";
  //strcat(text, (char)xPosition); //xPosition + " Y: " + yPosition + "BTN: " + buttonState;
  //strcat(text, " Y: ");
  //strcat(text, (char)yPosition);
  //strcat(text, " Btn: ");
  //strcat(text, (char)buttonState);
  
  sprintf(text, "X: %d, Y: %d, Btn: %d", xPosition,  yPosition,buttonState );

  Serial.println(text);

  //const char chars[text.length];
  //str_cpy(chars, text.c_str());

  radio.write(&text, sizeof(text));
  delay(500);
}
