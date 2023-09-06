#include <SoftwareSerial.h>
#include <avr/wdt.h>
#define pump 8
#define ring 12

SoftwareSerial gsm(2, 3);  // TX=2, RX=3

void setup()
{
  wdt_enable(WDTO_4S);  // Enable WDT For 4s
  
  for(int x=0;x<10;x++){wdt_reset(); delay(2000);}  //Time for connect GSM
  pinMode(pump, OUTPUT); pinMode(ring, INPUT_PULLUP);
  digitalWrite(pump, 0);
  gsm.begin(9600);  // Begin Soft Serial
  delay(200);
  sendSms2();  // Send Starting Message
  for(int x=0;x<5;x++){wdt_reset(); delay(2000);}  // Required after send SMS
}

void loop()
{
  int input = digitalRead(ring);
  if(input == 0)
  {
    giveWater();
  }
  digitalWrite(pump, 0);
  wdt_reset();
}

void giveWater()
{
  digitalWrite(pump , 1);
  for(int x=0;x<5;x++){wdt_reset(); delay(2000);}
  digitalWrite(pump, 0);
  delay(200);
  sendSms();
  for(int x=0;x<5;x++){wdt_reset(); delay(2000);}  // Required after send SMS
}

// 01798650959  01518633879  01714298406  01608424728
void sendSms()
{
  wdt_reset();
  gsm.println("AT+CMGF=1"); //Set the module to SMS mode
  delay(400);
  gsm.println("AT+CMGS=\"01632405851\"\r");
  delay(400);
  gsm.println("Water Irrigation Successfully!!!"); //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(400);
  gsm.println((char)26); //required according to the datasheet)
  delay(400);
}

void sendSms2()
{
  wdt_reset();
  gsm.println("AT+CMGF=1"); //Set the module to SMS mode
  delay(400);
  gsm.println("AT+CMGS=\"01632405851\"\r");
  delay(400);
  gsm.println("Power Reconnected!!!"); //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(400);
  gsm.println((char)26); //required according to the datasheet)
  delay(400);
}
