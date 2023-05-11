//VERİCİ
//http://arduino.esp8266.com/stable/package_esp8266com_index.json     /ESP8266
//http://dan.drown.org/stm32duino/package_STM32duino_index.json       /STM32
//KODU YAPIŞTIRDIKTAN SONRA SERİ HABERLEŞME YAPARAK YÜKLEMEN GEREKİYOR VE ÖNCESİNDE STM32 KARTINI TANIMLADIĞINA
//KART YÖNETİCİSİNDEN EMİN OL
#include <SPI.h>
#include <nRF24L01.h>             //Downlaod it here: https://www.electronoobs.com/eng_arduino_NRF24.php
#include <RF24.h>              


//Inputs/outputs
#define buton PA0

int butondurumu=0;
RF24 radio(PB4, PB5); // select  CSN  pin
const uint64_t pipeOut = 0xE8E8F0F0E1LL; //IMPORTANT: The same as in the receiver!!!




void setup() {
  pinMode(buton,INPUT);
  Serial.begin(9600);

  //Start everything up
  radio.begin();        
  radio.setAutoAck(false);                    // Ensure autoACK is enabled
  radio.setChannel(0x2F);
  radio.setPALevel(RF24_PA_MAX);  
  radio.setDataRate(RF24_2MBPS);
  radio.openWritingPipe(pipeOut);
  
}

void loop() {
  butondurumu=digitalRead(buton);
  
  if (butondurumu == 1){
    butondurumu = 1;
  }
  else  if (butondurumu == 0){
    butondurumu = 0;
  }
  Serial.println(butondurumu);

  radio.write(&butondurumu, sizeof(butondurumu));
}
