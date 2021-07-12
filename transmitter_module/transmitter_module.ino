// interfacing NRF24L01 with SPI
// Arduino UNO

/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#define CE    7
#define CSN   8

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(CE, CSN); // CE, CSN
const byte address[6] = "00001";  // can be any 5 letter string to talk to different receivers

void setup() {
  Serial.begin(9600);
  Serial.println("setup() starting");
  radio.begin();
  radio.openWritingPipe(address);

  // if using a higher level than RF24_PA_MIN, HowToMechatronics recommends to use a bypass cap.
  // between 3V3 and GND. https://www.youtube.com/watch?v=7rcVeFFHcFM timestamp: 3:50
  radio.setPALevel(RF24_PA_MIN);
  
  radio.stopListening();
  Serial.println("setup() finished");
}

void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  Serial.println("wrote Hello World");
  delay(1000);
}
