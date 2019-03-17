/*
 * NRF receiver
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup()
{
    pinMode(4, OUTPUT);
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN); // @todo Нужно подкрутить уровень, RF24_PA_MIN, есть не проверенная инфа, что с этим уровнем глюки
    radio.startListening();
}

void loop()
{
    if (radio.available())
    {
        char text[32] = "";
        radio.read(&text, sizeof(text));
        int xPosition, yPosition, buttonPosition;
        char junk[1];
        char xJunk[3];
        char yJunk[6];
        char btnJunk[7];

        sscanf(text, "%s%d,%s%d,%s%d",
               &xJunk, &xPosition,
               &yJunk, &yPosition,
               &btnJunk, &buttonPosition);

        // В этой версии просто зажигаем лампочку, если на передатчике нажата кнопка джойстика
        if (buttonPosition == 0)
        {
            digitalWrite(4, LOW);
        }
        else
        {
            digitalWrite(4, HIGH);
        }

        Serial.println(text);
    }
}
