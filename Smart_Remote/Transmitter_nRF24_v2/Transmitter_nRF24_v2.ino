/*
 * **************SIMPLE TX- MASTER OR TRANSMITTER************

  CE pin is always an input with respect to the 24L01. It is used to control data transmission.
     and reception when in TX and RX modes, respectively.
  CSN stands for chip select not. This is the enable pin for the SPI bus, and it is active low

   nRF24L01 uses SPI interface with Atmega328p or any other microcontroller

   http://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/
   Date: 03 June 2019
*/



#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN  9
#define CSN_PIN 10

const uint64_t pipe01 = 0xE8E8F0F0A1LL;

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char txNum = '0';


unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 100; // send once per second
const int buttonA_pin = 8;
const int buttonB_pin = 7;
const int buttonC_pin = 6;
const int buttonD_pin = 5;
bool buttonA = 0, buttonB = 0, buttonC = 0, buttonD = 0;
bool lastButtonStateA = 0;
bool lastButtonStateB = 0;
bool lastButtonStateC = 0;
bool lastButtonStateD = 0;

void setup()
{
  //pinMode(A0, OUTPUT);
  Serial.begin(9600);
  pinMode(buttonA_pin, INPUT);
  pinMode(buttonB_pin, INPUT);
  pinMode(buttonC_pin, INPUT);
  pinMode(buttonD_pin, INPUT);
  Serial.println("SimpleTx Starting");

  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.setRetries(3, 5);                   // delay, count
  radio.openWritingPipe(pipe01);
  radio.setPALevel(RF24_PA_MIN);
}

//====================

void loop()
{
  delay(5);
  //radio.stopListening();

  currentMillis = millis();
  if (currentMillis - prevMillis >= txIntervalMillis)
  {
    send();
    prevMillis = millis();
  }
}

//====================

void send()
{
    String x[1];
    buttonA = digitalRead(buttonA_pin);
    buttonB = digitalRead(buttonB_pin);
    buttonC = digitalRead(buttonC_pin);
    buttonD = digitalRead(buttonD_pin);
    delay(50);
    if (buttonA != lastButtonStateA)           // to write the alphabet only when the state of the button changes
    {
      if (buttonA == HIGH)
      {
        x[0] = ('A');                        //delay(50);
      }
      lastButtonStateA = buttonA;
      radio.write(&buttonA,sizeof(buttonA) );  //sizeof(buttonA)
      delay(10);
      radio.write( &x, sizeof(x));
    }

    else if(buttonB != lastButtonStateB)
    {
      if(buttonB == HIGH)
        {x[0]= 'B';}
        lastButtonStateB = buttonB;
        radio.write(&buttonB, sizeof(buttonB));
         delay(10);
      radio.write( &x, sizeof(x));
    }
  
    else if(buttonC != lastButtonStateC)
    {
      if(buttonC == HIGH)
        {x[0]= 'C';}
        lastButtonStateC = buttonC;
        radio.write(&buttonC, sizeof(buttonC));
         delay(10);
      radio.write( &x, sizeof(x));
    }
  
     else if(buttonD != lastButtonStateD)
    {
      if(buttonD == HIGH)
        {x[0]= 'D';}
        lastButtonStateD = buttonD;
        radio.write(&buttonD, sizeof(buttonD));
         delay(10);
      radio.write( &x, sizeof(x));
    }

    bool rslt;
    rslt = radio.write( &x, sizeof(x));
    // Always use sizeof() as it gives the size as the number of bytes.
    // For example if dataToSend was an int sizeof() would correctly return 2
                                                                                
    Serial.print("Data Sent ");
    Serial.print(x[0]);
    //To check whether the data is sent or not
    if (rslt == true)
    {
      Serial.println("  Acknowledge received");
    }
    else
    {
      Serial.println("  Tx failed");
    }
}

//============
