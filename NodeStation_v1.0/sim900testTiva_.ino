#include <OneWire.h>
#include <string.h>
//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(9, 10);
int smsCount = 0;
char sms[250];
int flag = 0;
char first;
char second;
String s;
String code,number,date,hour,msj;
OneWire  ds(10);  // on pin 10 (a 4.7K resistor is necessary)
//const int PF4 = 31;     // the number of the pushbutton pin
//const int LED =  39;
//int buttonState = 0;
//int flag = 0;
int count = 0;
float grados[5];
float grado = 0;
String cadena;

void setup()
{

  Serial.begin(19200);
  delay(1000);
  Serial2.begin(19200);   // Setting the baud rate of GSM Module
  delay(1000);

  Serial.println("Shite");

  //Serial.begin(19200);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(1000);
  Serial2.println("AT+IPR=19200");
  delay(1000);
  Serial2.println("AT\r");
  delay(1000);
  //Serial.println("Test");
  Serial2.println("AT+CMGF=1\r");
  delay(1000);

  delay(1000);
  Serial2.println("AT+CNMI=1,2,0,0,0\r");
    // blurt out contents of new SMS upon receipt to the GSM shield's serial out
  delay(1000);
  //Serial2.println("AT+IPR?");
  delay(1000);
  flag = 1;
}


void loop()
{
  if (Serial2.available() > 0) {
        char incoming_char = Serial2.read();
        //Serial.println(incoming_char);
        s += incoming_char;
        //Serial.println(incoming_char);
  }
    if (s.charAt(s.length() - 1) == '\n') {
        Serial.println(s);
        smsCount++;
        if(smsCount ==1){
            code = s.substring(0,5);
            //Serial.println(s);
            //Serial.println(code);
            //if(code == "OK"){
              //  Serial.println(s);
            //}

            //if(code == "AT+CN"){
              //  Serial.println(s);
            //}
            if(code == "+CMT:"){
                flag = 1;
                number = s.substring(8,19);
                date = s.substring(25,33);
                hour = s.substring(34,42);
            }
            else{
                //flag = 0;
                smsCount = 0;
            }
        }
        if(flag == 1 && smsCount == 2){
            //flag = 0;
            msj = s;
            msj = msj.substring(0,9);
            smsCount = 0;
            Serial.print("Code: ");
            Serial.println(code);
            Serial.print("Number: ");
            Serial.println(number);
            Serial.print("Date: ");
            Serial.println(date);
            Serial.print("Hour: ");
            Serial.println(hour);
            Serial.print("Msj: ");
            Serial.println(msj);
            if(msj.equals("TestBoton")){
                Serial.println("Sendingtest");
                SendMessage();
            }else{
                Serial.println("ErrorTest");
            }
        }

        //Serial.println(s);
        //Serial.println(s.length());
        //sub1 = s.substring(8,18);
        //Serial.println(sub1);
        s="";
    }

  /*
  if (s.charAt(s.length() - 1) == '\n') {
  Serial.println(s);

  //Serial.println(s.substring(0,5));
  s = "";
  }*/

  //RecieveMessage();


}


 void SendMessage()
{
     Serial.println("Sending sms");

     for (count = 0; count <5; count++){
         byte i;
         byte present = 0;
         byte type_s;
         byte data[12];
         byte addr[8];
         float celsius, fahrenheit;


         ds.search(addr);

         if (OneWire::crc8(addr, 7) != addr[7]) {
             Serial.println("CRC is not valid!");
             return;
         }
         // the first ROM byte indicates which chip
         switch (addr[0]) {
         case 0x10:
             Serial.println("  Chip = DS18S20");  // or old DS1820
             type_s = 1;
             break;
         case 0x28:
             //Serial.println("  Chip = DS18B20");
             type_s = 0;
             break;
         case 0x22:
             Serial.println("  Chip = DS1822");
             type_s = 0;
             break;
         default:
             Serial.println("Device is not a DS18x20 family device.");
             return;
         }

         ds.reset();
         ds.select(addr);
         ds.write(0x44, 1);        // start conversion, with parasite power on at the end

         delay(1000);     // maybe 750ms is enough, maybe not
         // we might do a ds.depower() here, but the reset will take care of it.

         present = ds.reset();
         ds.select(addr);
         ds.write(0xBE);         // Read Scratchpad

         // Convert the data to actual temperature
         // because the result is a 16 bit signed integer, it should
         // be stored to an "int16_t" type, which is always 16 bits
         // even when compiled on a 32 bit processor.
         int16_t raw = (data[1] << 8) | data[0];
         if (type_s) {
             raw = raw << 3; // 9 bit resolution default
             if (data[7] == 0x10) {
                 // "count remain" gives full 12 bit resolution
                 raw = (raw & 0xFFF0) + 12 - data[6];
             }
         } else {
             byte cfg = (data[4] & 0x60);
             // at lower res, the low bits are undefined, so let's zero them
             if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
             else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
             else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
             //// default is 12 bit resolution, 750 ms conversion time
         }
         celsius = (float)raw / 16.0;
         fahrenheit = celsius * 1.8 + 32.0;
         grados[count] = celsius;

     }
         //Serial.println(celsius);
         //Serial.print("  Temperature = ");
         //Serial.print(celsius);
         //Serial.print(" Celsius, ");
         //Serial.print(fahrenheit);
         //Serial.println(" Fahrenheit");
         //Serial.println("END-ADDR");



         /*Serial.println("No more addressesX.");
                               Serial.println("END-NOADDR");
                               Serial.println();
                               ds.reset_search();
                               delay(250);
                               return;
             }*/

         for (count = 0; count < 5; count++){

             grado+= grados[count];
         }
         grado /= 5;

         //Serial.print("Grados: ");
         //Serial.println(grado);

         //SendMessage();
         //grado = 0;


         //Serial.print(grados[count]);


     //if (Serial2.available()>0)

     //Serial2.println("AT");
     //delay(1000);
     //Serial.write(Serial2.read());
     //}



     Serial2.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1000 milli seconds or 1 second
     Serial2.println("AT+CMGS=\"+50241679097\"\r"); // Replace x with mobile number
     delay(1000);
     String gradoStr = String(grado,DEC);
     cadena = "ID01,"+gradoStr+"C";
     Serial2.println(cadena);// The SMS text you want to send
     //Serial2.println("Probando SMS Sim900");// The SMS text you want to send
     delay(100);
     Serial2.println((char)26);// ASCII code of CTRL+Z
     delay(1000);
     RecieveMessage();
}


 void RecieveMessage()
{
  Serial.println("Test3");
  Serial2.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
