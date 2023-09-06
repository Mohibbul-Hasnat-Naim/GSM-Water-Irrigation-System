#include <SoftwareSerial.h>
#define pump 8
#define ring 12

SoftwareSerial gsm(2, 3);  // TX=2, RX=3

void setup()
{
  delay(20000);  //Time for connect GSM
  pinMode(pump, OUTPUT); pinMode(ring, INPUT_PULLUP);
  digitalWrite(pump, 0);
  gsm.begin(9600);  // Begin Soft Serial
  delay(200);
  sendSms2();  // Send Starting Message
  delay(10000);  // Required time for proper commiunication
}

void loop()
{
  int input = digitalRead(ring);
  if(input == 0)
  {
    giveWater();
  }
  digitalWrite(pump, 0);
}

void giveWater()
{
  digitalWrite(pump , 1);
  //for(int x=0;x<5;x++){delay(20000);}
  delay(10000);
  digitalWrite(pump, 0);
  delay(200);
  sendSms();  
  delay(10000);  // Required after send SMS
}

// 01798650959  01518633879  01714298406  01608424728
void sendSms()
{
  gsm.println("AT+CMGF=1"); //Set the module to SMS mode
  delay(500);
  gsm.println("AT+CMGS=\"01632405851\"\r");
  delay(500);
  gsm.println("Water Irrigation Successfully!!!"); //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  gsm.println((char)26); //required according to the datasheet)
  delay(500);
}

void sendSms2()
{
  gsm.println("AT+CMGF=1"); //Set the module to SMS mode
  delay(500);
  gsm.println("AT+CMGS=\"01632405851\"\r");
  delay(500);
  gsm.println("Power Reconnect!!!"); //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  gsm.println((char)26); //required according to the datasheet)
  delay(500);
}
