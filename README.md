# SJTech-Internship
IoT development Intern          

/*
  ***************** WATER DETECTION IN HAND PUMP *******************      
        
  <b>Description:</b>
  
              <p> This project aims to detect the water inside the Hand Pump By analog reading from the sensor
               and then the Sensor Reading is sent to the Server(https://colonymaintenance.com/77/IOT/Project1/api.php?action=view)
               by using GSM SIM900A module. </p>                                      
 <b> Prerequisites: </b>  
 
                   <p>   1.  Rain Sensor(YL-83 or FC-37)  - 1 (Quantity)
                         2.  ATmega328p microcontroller   - 1
                         3.  GSM Module (SIM900A)         - 1
                         4.  LM7805 voltage regulator     - 1
                         5.  capacitor (10uF, 22pF)       - 2, 2
                         6.  Oscillator (16 MHz)          - 1
                         7.  Push Button Switch           - 1
                         8.  Resistor(10k Ohm)            - 1
                         9.  arduino board or USB to TTL  - 1       //For programming the standalone 328p, i used arduino board
                         10. Breadboard or zero PCB       - 1     </p>
 <b> Connections:</b>      
 
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
                                                          </p>
              Note: 1. power the GSM Module by 12V
                    2. While powering the Atemga 328p microcontroller use Output from the 3rd pin of 
                       LM7805 voltage regulator and Give 12V input to 1st pin of LM7805 (when lm7805 is seen from the written side or non plane side and count from left)
<b>Attention :</b>

            If the SAPBR (1,1) functoin or the HTTPINIT() function in Serial monitor returns ERROR then
            remove the power supply from the GSM and connect it again.
<b>Output:</b>

         It returns 4 parameters related to water Status in Pump
         unique_id, water_Intensity_in_pump, water_status, status
         unique_id tells about the pump id in String
         water_Intensity_in_pump tells about the intensity of water in INTEGER
         water_status tells whether the water is coming or not in String
         status gives Output in 0 and 1, 0 when water is NOT coming and 1 when Water is coming
         
        Go to https://colonymaintenance.com/77/IOT/Project1/api.php?action=view link  to view the OUTPUT
