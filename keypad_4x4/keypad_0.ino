/*
                             ****************4x4 KEYPAD in Arduino******************
                             
                                               '1','2','3','A'

                                               '4','5','6','B'

                                               '7','8','9','C'

                                               '*','0','#','D'
                                               
                                               | | | | | | | |
                                               | | | | | | | |  : First four for Rows and last four pins for columns
                            Arduino Pins -->   9 8 7 6 5 4 3 2  : CONNECTION TO ARDUINO PINS or TO EQUIVALENT ATMEGA328P PINSin case of STANDALONE 
                                                     
    
    --> '#' works as a equal Button
    
    --> Takes input as a multiple digit Number or single character Alphabet    
    --> returns:
            one or more digit Number and  an Alphabet (only one will come at a time and other will be coming as null or Zero)
    
    
 */

#include <Keypad.h> //Header file for Keypad from https://github.com/Chris--A/Keypad
//#include <stdlib.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns

// Define the Keymap
char keys[ROWS][COLS] = 
{

  {'1','2','3','A'},

  {'4','5','6','B'},

  {'7','8','9','C'},

  {'*','0','#','D'}

};

byte rowPins[ROWS] = { 9, 8, 7, 6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3, 2 }; // Connect keypad COL0, COL1,COL2 and COL3 to these Arduino pins.

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad


 long Num1,Num,Number;
 char key,action,x,alpha;
 boolean result = false;
 
void setup()
{ 
  Serial.begin(9600); 
  //We do not need to define the input and output for the pins because it's already there in keypad library
}



void DetectButtons()
{ 
    
    if (key=='*')            //If cancel Button is pressed
    {
      Serial.println ("Button Cancel");
      Number=Num1=0; 
      result=false;
    }
    
     if (key == '1') //If Button 1 is pressed
    {
      Serial.println ("Button 1"); 
      if (Number==0)
      {Number=1;}
      else
      {Number = (Number*10) + 1;}   //Pressed twice
    }
    
     if (key == '4') //If Button 4 is pressed
    {
      Serial.println ("Button 4"); 
      if (Number==0)
      {Number=4;}
      else
      {Number = (Number*10) + 4;} //Pressed twice
    }
    
     if (key == '7') //If Button 7 is pressed
      {
        Serial.println ("Button 7");
        if (Number==0)
        {Number=7;}
        else
        {Number = (Number*10) + 7; }//Pressed twice
    } 
  

    if (key == '0')
    {
      Serial.println ("Button 0"); //Button 0 is Pressed
      if (Number==0)
      {Number=0;}
      else
      {Number = (Number*10) + 0;} //Pressed twice
    }
    
     if (key == '2') //Button 2 is Pressed
    {
      Serial.println ("Button 2"); 
      if (Number==0)
      {Number=2;}
      else
      {Number = (Number*10) + 2;} //Pressed twice
    }
    
     if (key == '5')
    {
    Serial.println ("Button 5"); 
     if (Number==0)
    {Number=5;}
    else
    {Number = (Number*10) + 5;} //Pressed twice
    }
    
     if (key == '8')
    {
      Serial.println ("Button 8"); 
       if (Number==0)
      {Number=8;}
      else
      {Number = (Number*10) + 8;} //Pressed twice
    }   
    
     if (key == '3')
    {
      Serial.println ("Button 3"); 
       if (Number==0)
      {Number=3;}
      else
      {Number = (Number*10) + 3;} //Pressed twice
    }
    
     if (key == '6')
    {
      Serial.println ("Button 6"); 
      if (Number==0)
      {Number=6;}
      else
      {Number = (Number*10) + 6; }//Pressed twice
    }
    
     if (key == '9')
    {
      Serial.println ("Button 9");
      if (Number==0)
      {Number=9;}
      else
      {Number = (Number*10) + 9;} //Pressed twice
    }  

      if (key == 'A' || key == 'B' || key == 'C' || key == 'D') //Detecting Buttons on Column 4
      {
            Num1 = Number;     
            Number =0;
             if (key == 'A')
             { 
                x='A';
                alpha= char(x);
                //Serial.println(alpha);
             }
             if (key == 'B')
             {
                x='B';
                 alpha= char(x);
                 //Serial.println(alpha);   
             }
             if (key == 'C')
            {
                x='C';
                 alpha= char(x);
                 //Serial.println(alpha); 
             }
              if (key == 'D')
             {   
                x='D';
                alpha= char(x);
                //Serial.println(alpha); 
             }       
      }
         
     if (key == '#')
       {
           Serial.println ("Button Equal"); 
           Num1=Number; 
           result = true;        
       }
  
}

int DisplayResult()
{
      return (int(Number));
}

void loop() 
{
    
    key = kpd.getKey(); //storing pressed key value in a char
    
    if (key!=NO_KEY)
    {
      DetectButtons();
    }
    
    if (result==true)
    {  
          Serial.println(DisplayResult());
          Serial.println(alpha);
          Number=0;
    }  
    result= false;
        
}

 
