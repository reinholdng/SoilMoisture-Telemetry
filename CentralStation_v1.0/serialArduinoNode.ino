#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;

int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];

char sms_position;
char phone_number[20];
char sms_text[100];
int i;

int pin8(8); //Assigning integrer ID to pin #8


void setup() { //Setup Declaration
  // put your setup code here, to run once:

  //pinMode(pin8,OUTPUT);  //Configuring pin #8 to be an output pin, where pin 8 become a toggle 5 volt output.
  Serial.begin(9600);    //Telling Arduino to enable Serial communication at 9600 baud rate.
  if (gsm.begin(9600)) 
    {
        started=true;
    } 
}

void loop() { //Declaring looping script, which is what the Arduino will run continously.
  // put your main code here, to run repeatedly:

  int SerialData = Serial.read();  //Read Serial data given from the interacting computer.
  //Serial.println(SerialData);  //Telling Arduino to return the recieved Serial data back to the interacting computer.
  
  
  //Beginning Optional side of script, enabled by default. Can be disabled with a double slash or a /* MultiLine Comment Toggle */
  
  if (SerialData == 54) {  //Initializing if statement. In this case we are checking if the Serial value recieved earlier is equal to 54
    //digitalWrite(pin8,HIGH);  //Writing to Digital Pin #8 to turn on output at 5 volt
    if(started) 
    {
        if (sms.SendSMS("+50247880020", "TestBoton"))
        {
          //Serial.println("\nSMS sent OK.");
          Serial.println(10);
        }
        else
        {
          //Serial.println("\nError sending SMS.");
          Serial.println(5);
        }      
    }
  }
  else {  //Else statement for when the if statement isn't matched, in this case empty.
  }
  if (SerialData == 55) {  //Initializing another if statement, checking if Serial value is equal to 55
    digitalWrite(pin8,LOW);    //Writing to Digital Pin #8 to turn off output, 0 volt
  }
  else {  //Another else statement, empty again. Doesn't need to be here actually.
  }

delay(2000);  /*1 second delay to enable enough time for the user to see the Serial data that was sent back to learn the interactions. 
                Especially useful for learning how information is recieved when devices are sending information at different bits (Arduino Uno is 8 bit)*/
}
