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
               Date: 29 May 2019

*/

#include <SoftwareSerial.h>
/* Create object named SIM900 of the class SoftwareSerial */ 
SoftwareSerial SIM900(8, 7);  // RX, TX...connect sim900 RX to 7 and TX to 8 th pin of arduino 

#define waterSensor A0
int water, tellWater;

void setup() 
{
  
  SIM900.begin(9600);  /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
}
String TellWater()
{
  int readWater = analogRead(A0);
      water= map(analogRead(A0), 1024, 0, 0, 10);      //mapping the sensor output in range 0 to 10
  while(1)
  {
    if(water>=5)
      {
        return "Water_is_coming!!!";    
      }
     else
      {
        return "Water_is_NOT_COMING_or_it_is_NOT_adequate_Please_Check...";
      }
  }
}

int WaterStatus()
{
  int readWater = analogRead(A0);
      water= map(analogRead(A0), 1024, 0, 0, 10);      //mapping the sensor output in range 0 to 10
  while(1)
  {
    if(water>=5)
      {
        return 1;    
      }
     else
      {
        return 0;
      }
  }
}

void loop() 
{
  Serial.println("HTTP post method :");
  Serial.print("AT\\r\\n");
  SIM900.println("AT"); /* Check Communication */
  delay(5000);
  ShowSerialData(); /* Print response on the serial monitor */
  delay(5000);
  /* Configure bearer profile 1 */
  Serial.print("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\\r\\n");
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");  /* Connection type GPRS */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"\\r\\n");
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");  /* APN of the provider */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+SAPBR=1,1\\r\\n");
  SIM900.println("AT+SAPBR=1,1"); /* Open GPRS context */
  delay(2000);
  ShowSerialData();
 // delay(5000);
  Serial.print("AT+SAPBR=2,1\\r\\n");
  SIM900.println("AT+SAPBR=2,1"); /* Query the GPRS context */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+HTTPINIT\\r\\n");
  SIM900.println("AT+HTTPINIT");  /* Initialize HTTP service */
  delay(5000); 
  ShowSerialData();
  delay(5000);
  Serial.print("AT+HTTPPARA=\"CID\",1\\r\\n");
  SIM900.println("AT+HTTPPARA=\"CID\",1");  /* Set parameters for HTTP session */
  delay(5000);
  ShowSerialData();
  delay(5000);
  
  Serial.print("AT+HTTPPARA=\"URL\",\"colonymaintenance.com/77/IOT/Project1/api.php?action=signal&water_Intensity_in_pump=\"\\r\\n");
  SIM900.println("AT+HTTPPARA=\"URL\",\"colonymaintenance.com/77/IOT/Project1/api.php?action=signal&unique_id=" + String("Pump0") + "&water_Intensity_in_pump=" + String(map(analogRead(A0), 1024, 0, 0, 10))+ "&water_status=" +  String(TellWater()) + "&status=" + String(WaterStatus()) + "\"");      /* Set parameters for HTTP session */
  delay(5000);
  ShowSerialData();
  Serial.print("AT+HTTPDATA=33,10000\\r\\n");
  SIM900.println("AT+HTTPDATA=33,10000"); /* POST data of size 33 Bytes with maximum latency time of 10seconds for inputting the data*/ 
  delay(2000);
  ShowSerialData();
  delay(5000);
  Serial.print("pump_code:123456/latitude:567567/longitude:888888/status:3=TellWater()\\r\\n");  /* Data to be sent */  //QI8G7PVTC2BVIREC&field1
  
  SIM900.println("pump_code:123456/latitude:567567/longitude:888888/status:3="+ String(map(analogRead(A0), 1024, 0, 0, 10)) + String(TellWater()));   //+String( map(analogRead(A0), 1024, 0, 0, 10))
  delay(5000);
  //delay(5000);
  ShowSerialData();
  //delay(5000);
  Serial.print("AT+HTTPACTION=1\\r\\n");
  SIM900.println("AT+HTTPACTION=1");  /* Start POST session */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+HTTPTERM\\r\\n");  
  SIM900.println("AT+HTTPTERM");  /* Terminate HTTP service */
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+SAPBR=0,1\\r\\n");
  SIM900.println("AT+SAPBR=0,1"); /* Close GPRS context */
  delay(5000);
  ShowSerialData();
  delay(5000);
}

void ShowSerialData()
{
  while(SIM900.available()!=0)  /* If data is available on serial port */
  Serial.write(char (SIM900.read())); /* Print character received on to the serial monitor */
}
