#include "nrf.h"

RF24 radio(10, 9);
NRF::NRF()
{
}
void NRF::tx_data(const char *text)
{
  radio.openWritingPipe(rAddress[1]);
  radio.stopListening();
  radio.write(text, sizeof(text));
  radio.openReadingPipe(0, rAddress[0]);
  radio.startListening();
}
char NRF::rx_data()
{
  if (radio.available())
  {
    char text[2];
    radio.read(&text, sizeof(text));
    Serial.println(text);
    return text[0];
  }
  return 'X';
}