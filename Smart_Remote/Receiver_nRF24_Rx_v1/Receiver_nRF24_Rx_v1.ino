/*
 * SimpleRx - the slave or the receiver
 * https://forum.arduino.cc/index.php?topic=421081
 * 
 * https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/
 * 
 */


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN 9
#define CSN_PIN 10

const uint64_t pipe01 = 0xE8E8F0F0A1LL;         //for 1st remote
const uint64_t pipe02 = 0xA2LL;                 
const uint64_t pipe03 = 0xA3LL;
const uint64_t pipe04 = 0xA4LL;
const uint64_t pipe05 = 0xA5LL;
const uint64_t pipe06 = 0xA6LL;
RF24 radio(CE_PIN, CSN_PIN);

//String dataReceived[1];                      // this must match dataToSend in the TX
//bool newData = false;
bool buttonA=0, buttonB=0, buttonC=0, buttonD=0;

//===========

void setup() 
{
    Serial.begin(9600);                                     
    pinMode(A0, OUTPUT);                                                           
    Serial.println("SimpleRx Starting");     
    
    radio.begin();
    radio.setDataRate( RF24_250KBPS ); 
    radio.openReadingPipe(1, pipe01);   //Setting the address at which we will receive the data
    radio.setPALevel(RF24_PA_MIN);      //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
    radio.startListening();             //This sets the module as receiver   
}

//=============

void loop()
{   
    Serial.println("receiver - loop");                      //Saving the incoming data
    delay(500);
    uint8_t tellPipe;
    while( radio.available(&tellPipe))                      //Looking for the data.
    {
        Serial.print("pipe number ");
        Serial.println(tellPipe);  
        char x[1]={};                                                                                                          
        bool done= false; 
        while (!done)
        {
            radio.read(&x,sizeof(x));               //Reading the data   sizeof(x)                                                              //radio.read( &((dataReceived[0])), sizeof(((dataReceived[0]))) );
            delay(50);
            Serial.println(x[0]);
                                                                                                                                                // radio.read(&buttonA, sizeof(buttonA));    //Reading the data
        }
             
    }
     
    {
       Serial.println("Error: No Radio Transmission");
    }
}
