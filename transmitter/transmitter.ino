/*
 * NRF transmitter
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int xPin = A1;
int yPin = A0;
int buttonPin = 2; // Куда подключен триггер реле
int xPosition = 0;
int yPosition = 0;
int buttonState = 0;
int oldPositionX = 0;
int oldPositionY = 0;
int oldButtonState = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);

    pinMode(buttonPin, INPUT_PULLUP);

    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN); // @todo Нужно подкрутить уровень
    radio.stopListening();
}

void loop()
{
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    buttonState = digitalRead(buttonPin);

    char text[25]; // = "X: ";

    sprintf(text, "X: %d, Y: %d, Btn: %d", xPosition, yPosition, buttonState);

    Serial.println(text);

    // Передаем данные только если они изменились
    if (oldButtonState != buttonState || oldPositionX != xPosition || oldPositionY != yPosition)
    {
        radio.write(&text, sizeof(text));
        oldPositionX = xPosition;
        oldPositionY = yPosition;
        oldButtonState = buttonState
    }

    delay(250);
}
