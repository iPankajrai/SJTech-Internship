/*
  ***************** WATER DETECTION IN HAND PUMP *******************
  Description:
               This project aims to detect the water inside the Hand Pump By analog reading from the sensor
               and then the Sensor Reading is sent to the Server(https://colonymaintenance.com/77/IOT/Project1/api.php?action=view)
               by using GSM SIM900A module.
  Prerequisites:
               1.  Rain Sensor(YL-83 or FC-37)  - 1 (Quantity)
               2.  ATmega328p microcontroller   - 1
               3.  GSM Module (SIM900A)         - 1
               4.  LM7805 voltage regulator     - 1
               5.  capacitor (10uF, 22pF)       - 2, 2
               6.  Oscillator (16 MHz)          - 1
               7.  Push Button Switch           - 1
               8.  Resistor(10k Ohm)            - 1
               9.  arduino board or USB to TTL  - 1       //For programming the standalone 328p, i used arduino board
               10. Breadboard or zero PCB       - 1
  Connections:
              Sensor           Atmega328p 
                vcc    ---->      vcc
                GND    ---->      GND
                A0     ---->      ADC0 (23rd Pin)
              SIM900A          Atmega328p 
                GND    ---->      GND
                TXD    ---->      14
                RXD    ---->      13 
              Arduino          Atmega328p 
                GND    ---->      GND
                5V     ---->      vcc
                RESET  ---->       1
                RX     ---->       2
                TX     ---->       3
              Oscillator       Atmega328p
                1st    ---->       9
                2nd    ---->       10    (with 22pF capacitors)
              
              Note: 1. power the GSM Module by 12V
                    2. While powering the Atemga 328p microcontroller use Output from the 3rd pin of 
                       LM7805 voltage regulator and Give 12V input to 1st pin of LM7805 (when lm7805 is seen from the written side or non plane side and count from left)
                    3. Watch-out for the network led pattern of GSM.
                        Status                               SIM900 behavior
                        Off                                    SIM900 is not running
                        64ms On/ 800ms Off       SIM900 not registered the network
                        64ms On/ 3000ms Off     SIM900 registered to the network
                        64ms On/ 300ms Off       GPRS communication is established
Attention :
            If the SAPBR (1,1) functoin or the HTTPINIT() function in Serial monitor returns ERROR then
            remove the power supply from the GSM and connect it again.

Output:
         It returns 4 parameters related to water Status in Pump
         unique_id, water_Intensity_in_pump, water_status, status
         unique_id tells about the pump id in String
         water_Intensity_in_pump tells about the intensity of water in INTEGER
         water_status tells whether the water is coming or not in String
         status gives Output in 0 and 1, 0 when water is NOT coming and 1 when Water is coming
        Go to https://colonymaintenance.com/77/IOT/Project1/api.php?action=view link  to view the OUTPUT

      Work by:
               Pankaj Rai
               Date: 02 july 2019

*/

#include <SoftwareSerial.h>   /* Create object named SIM900 of the class SoftwareSerial */  
SoftwareSerial SIM900(8, 7);  /* RX, TX...connect sim900 RX to 7 and TX to 8 th pin of arduino */
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define Host "colonymaintenance.com/77/IOT/Room_Temperature/api.php?action=temp"

//////////////////////////////////////setup code //////////////////////////////////////////////////
void setup() 
{
  pinMode(2, INPUT); /* Define pin 2 as INPUT pin for DHT11 sensor */
  dht.begin(); /* DHT11 initialization*/
  SIM900.begin(9600);  /* Define baud rate for software serial communication */
  Serial.begin(115200); /* Define baud rate for serial communication */
}


 //////////////////////////////////// void loop ////////////////////////////////////////////////////
void loop() 
{
  delay(50);
  float humid = dht.readHumidity();      /* Humidity obtained from this function is 'Relative Humidity' (NOT absolute Humidity) */ 
  float temp = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(humid) || isnan(temp) || isnan(f))  /* isnan ==> "is not a number"...returns 1 if " h  or t or f are not a number" */
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float hic = dht.computeHeatIndex(temp, humid, false);
  Serial.print("Temperature: ");
  Serial.print(temp );
  Serial.println(" *C ");
  //delay(50);
  Serial.print("Humidity(%): ");
  Serial.print(humid);
  Serial.println(" %");
  //delay(50);
  
   String temp2 = String (temp) +  ("C") ; 
   String Temp = temp2;   
   String humid2 = String (humid) +("Percent") ;  
   String Humid = humid2; 
  
  
  Serial.println("HTTP post method :");   
  Serial.print("AT\\r\\n");  /* initiates the GSM module, Gives OK for working GSM */
  SIM900.println("AT"); /* Check Communication */
  delay(500);
  ShowSerialData(); /* Print response on the serial monitor */
  delay(1000);

  /* Configure bearer profile 1 and initiates the data communication  */
  Serial.print("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\\r\\n");
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");  /* Connection type GPRS */
  delay(500);
  ShowSerialData();      
  delay(1000);
  Serial.print("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"\\r\\n");
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");  /* APN of the provider */
  delay(500);
  ShowSerialData();
  delay(1000);
  Serial.print("AT+SAPBR=1,1\\r\\n");
  SIM900.println("AT+SAPBR=1,1"); /* Open GPRS context */
  delay(500);
  ShowSerialData();
  delay(1000);
  Serial.print("AT+SAPBR=2,1\\r\\n");
  SIM900.println("AT+SAPBR=2,1"); /* Query the GPRS context */
  delay(500);
  ShowSerialData();
  delay(1000);

  /*Initiates the Internet connection*/
  Serial.print("AT+HTTPINIT\\r\\n");
  SIM900.println("AT+HTTPINIT");  /* Initialize HTTP service */
  delay(500); 
  ShowSerialData();
  delay(1000);
  Serial.print("AT+HTTPPARA=\"CID\",1\\r\\n");
  SIM900.println("AT+HTTPPARA=\"CID\",1");  /* Set parameters for HTTP session */
  delay(500);
  ShowSerialData();
  delay(1000);
  /*put your API key below*/
  Serial.print("AT+HTTPPARA=\"URL\",\"colonymaintenance.com/77/IOT/Room_Temperature/api.php?action=temp&Van_temp=\"\\r\\n");
  SIM900.println("AT+HTTPPARA=\"URL\",\"colonymaintenance.com/77/IOT/Room_Temperature/api.php?action=temp&device_id=" + String("1") + "&device_time=" + String("2")+ "&temperature=" + String(Temp)  + "&humidity=" +  String(Humid) + "\"");      /* Set parameters for HTTP session */
  delay(500);
  ShowSerialData();

  /*To send the data*/
  Serial.print("AT+HTTPDATA=33,10000\\r\\n");
  SIM900.println("AT+HTTPDATA=33,10000"); /* POST data of size 33 Bytes with maximum latency time of 10seconds for inputting the data*/ 
  delay(500);
  ShowSerialData();
  delay(1000);
  Serial.print("device_id:1/device_time:2/temperature:4/humidity:5=\\r\\n");  /* Data to be sent */  
  
  SIM900.println("device_id:1/device_time:2/temperature:4/humidity:5=" + String(temp) + String(humid));   
  delay(500);
  ShowSerialData();
  Serial.print("AT+HTTPACTION=1\\r\\n");
  SIM900.println("AT+HTTPACTION=1");  /* Start POST session */
  delay(1000);
  ShowSerialData();
  delay(1000);
  Serial.print("AT+HTTPTERM\\r\\n");  
  SIM900.println("AT+HTTPTERM");  /* Terminate HTTP service */
  delay(1000);
  ShowSerialData();
  delay(1000);
  Serial.print("AT+SAPBR=0,1\\r\\n");
  SIM900.println("AT+SAPBR=0,1"); /* Close GPRS context */
  delay(500);
  ShowSerialData();
  delay(1000);
}
/*  Sensor Data will be posted to server after delay of 20 seconds */


void ShowSerialData()
{
  while(SIM900.available()!=0)  /* If data is available on serial port */
  Serial.write(char (SIM900.read())); /* Print character received on to the serial monitor */
}
