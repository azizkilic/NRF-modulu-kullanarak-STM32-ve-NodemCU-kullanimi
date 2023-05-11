//ALICI
//http://arduino.esp8266.com/stable/package_esp8266com_index.json     /ESP8266
//http://dan.drown.org/stm32duino/package_STM32duino_index.json       /STM32
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define led D0

int butonstate = 0;
RF24 radio(D4,D2); // CE, CSN
const uint64_t pipeIn = 0xE8E8F0F0E1LL; //Remember that this code is the same as in the transmitter





void setup()
{
  Serial.begin(9600); //Set the speed to 9600 bauds if you want.
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  radio.begin();
  radio.setAutoAck(false);                    // Ensure autoACK is enabled
  radio.setChannel(0x2F);
  radio.setDataRate(RF24_2MBPS);

  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}

/**************************************************/

/*unsigned long lastRecvTime = 0;

void recvData()
{
  while ( radio.available() ) {
    radio.read(&data, sizeof(MyData));  
    lastRecvTime = millis(); //here we receive the data
  }
}*/

void loop() {
  radio.startListening();
  while(!radio.available());
  radio.read(&butonstate,sizeof(butonstate));
  Serial.println(butonstate);
  if(butonstate==1){
    digitalWrite(led,HIGH);
  }
  else if(butonstate==0){
    digitalWrite(led,LOW);
  }
}
/**************************************************/
