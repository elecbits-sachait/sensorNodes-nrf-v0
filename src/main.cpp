#include <Arduino.h>
#include "nrf.h"
#include "rgbled.h"
//#define SENSOR_PIN 3 //button  //pir
#define SENSOR_PIN A3 //door //vib
NRF nrf;
bool sensor_mode = false;

bool get_mode();
bool check_data();
bool send_data();

char data_recieved;

void setup()
{
  Serial.begin(9600);
  //pinMode(SENSOR_PIN, INPUT_PULLUP);
  Serial.println("GETTING MODE");
  radio.begin();
  radio.openReadingPipe(0, rAddress[0]);
  radio.startListening();
  rgb_mode.blue();
  while (!get_mode())
  {
    Serial.println("as");
  }
}

void loop()
{
  check_data();
  Serial.println("JI");
  if (sensor_mode)
  {
    if (analogRead(SENSOR_PIN) > 900)
    {
      rgb_mode.white();
      while (!send_data())
      {
        Serial.println("lk");
      }
    }
  }
}

bool get_mode()
{
  uint64_t m = millis();
  data_recieved = '\0';
  nrf.tx_data("?");
  Serial.println("trans?");
  while (millis() - m < 5000)
  {
    Serial.println("AWIK");
    if (check_data())
    {
      return true;
    }
  }
  return false;
}
bool send_data()
{
  uint64_t m = millis();
  nrf.tx_data("V");
  Serial.println("transS");
  rgb_mode.white();
  while (millis() - m < 5000)
  {
    data_recieved = '\0';
    data_recieved = nrf.rx_data();
    if (data_recieved == 'P')
    {
      rgb_mode.purple();
      while (1)
      {
        data_recieved = nrf.rx_data();
        if (data_recieved == 'A')
        {
          sensor_mode = true;
          rgb_mode.green();
          return true;
        }
        else if (data_recieved == 'M')
        {
          sensor_mode = false;
          rgb_mode.red();
          return true;
        }
      }
    }
  }
  return false;
}
bool check_data()
{
  data_recieved = '\0';
  data_recieved = nrf.rx_data();
  if (data_recieved == 'A')
  {
    sensor_mode = true;
    rgb_mode.green();
    return true;
  }
  else if (data_recieved == 'M')
  {
    sensor_mode = false;
    rgb_mode.red();
    return true;
  }
  else if (data_recieved == 'P')
  {
    rgb_mode.purple();
    while (1)
    {
      data_recieved = nrf.rx_data();
      if (data_recieved == 'A')
      {
        sensor_mode = true;
        rgb_mode.green();
        return true;
      }
      else if (data_recieved == 'M')
      {
        sensor_mode = false;
        rgb_mode.red();
        return true;
      }
    }
  }
  return false;
}