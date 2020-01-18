#ifndef nrf_h
#define nrf_h
#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
///A -> AUTO_MODE
//B -> MANUAL_MODE
//P -> PAUSE ON
//I-> PIR
//D->DOOR
//B-> BUTTON
//V -> VIBRATION
//O -> ACKNOWLEDGEMENT
//? -> ASK_MODE
//X -> NULL

extern RF24 radio;
//const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL}; //button
//const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F2LL}; //PIR
const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F9LL};//VIB
//const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F4LL}; //DOOR

class NRF
{
public:
  NRF();
  static void tx_data(const char *);
  static char rx_data();
};

#endif
