#include "config.h"
#include <LiquidCrystal_I2C.h>
/************************ Example Starts Here *******************************/
#define RXD2 16
#define TXD2 17
#define TXD1 19
#define RXD1 18
// Use Serial1 for UART communication
HardwareSerial rfid1Serial(1);
#define rfid2_BAUD 9600
// Create an instance of the HardwareSerial class for Serial 2
HardwareSerial rfid2Serial(2);

const int red1 = 23;
const int green1 = 19;
const int red2 = 18;
const int green2 = 5;
// set up the 'temperature' and 'humidity' feeds
AdafruitIO_Feed *slot1 = io.feed("slot1");//akshayreddy085,pwd:Nmrec@123
AdafruitIO_Feed *slot2 = io.feed("slot2");
LiquidCrystal_I2C lcd(0x27, 16, 2);
int count = 0;
char input[13];
String rfid;
String rfid1;
String rfid2;
char temp;
String c1="550001D6D557";
String c2="5500021484C7";
String name1 = "None";
String name2= "None";
int ps1=0,ps2=0,as,card1=0,card2=0;
int rs =2,sec1 = 0,sec2 = 0,price = 0,cnt1=0,cnt2=0,x;
void setup() {
  lcd.init();         // initialize the lcd
  lcd.backlight();  
  Serial.begin(9600);
  rfid2Serial.begin(rfid2_BAUD, SERIAL_8N1, RXD2, TXD2);
  rfid1Serial.begin(9600, SERIAL_8N1, RXD1, TXD1);
  Serial.print("Connecting to Adafruit IO");
  lcd.setCursor(0,0);
  lcd.print("SSID:");
  lcd.print(WIFI_SSID);
  lcd.setCursor(0,1);
  lcd.print("PWD:");
  lcd.print(WIFI_PASS);
  io.connect();
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CONNECTED..");
  delay(2000);
  lcd.clear();
  Serial.println();
  Serial.println(io.statusText());
  welcome_note();
}
void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
 /* check_parking_inout();
  sensors_event_t event;*/
  slot1->save(name1);
  // save humidity to Adafruit IO
  slot2->save(name2);
  Serial.print("slot1");
  Serial.print(name1);
  Serial.print(",slot2");
  Serial.println(name2);

  // wait 5 seconds (5000 milliseconds == 5 seconds)*/
  delay(1000);
  check_parking_inout();
  check_parking1();
  check_parking2();
  if(card1 > 1)
  {
    sec1 = sec1 + 1;
    delay(500);
  }
  if(card2 > 1)
  {
    sec2 = sec2 + 1;
    delay(500);
  }
}
void check_parking_inout()
{
while(Serial.available() && count < 12)          
    {
    input[count]=Serial.read();
    count++;
    delay(6);
    //Serial.println(String(input));
    if (count==12)
    {
      Serial.println(String(input));
      count = 0;
       rfid=input;
       if(rfid==c1)//tag[count]==input[count])
       {
    Serial.println("entry");
    if(card1 < 1)
    {
    lcd.setCursor(0,1);           
    lcd.print("HANEESH IN ");
    delay(1000);
    card1=2;
    if(ps1 < 1)
    {
    lcd.setCursor(0,1);           
    lcd.print("PARK SLOT 1");
    as=1;
    delay(1000);
    }
    else if(ps2 < 1)
    {
    lcd.setCursor(0,1);           
    lcd.print("PARK SLOT 2");
    delay(1000); 
    as =2;
    }
    else
    {
    lcd.setCursor(0,1);           
    lcd.print("NO PARKNG"); 
    }
    }
    else
    {
    lcd.setCursor(0,1);           
    lcd.print("exit wait for bill");
    bill_show1();
    card1=0;
    name1 = "None";
    delay(2000);
    welcome_note();
    }
    }
     else if(rfid==c2){
    Serial.println("entry");
    if(card2 < 1)
    {
    lcd.setCursor(0,1);           
    lcd.print("MANISH IN  ");
    delay(1000);
    card2=2;
    if(ps1 < 1)
    {
    lcd.setCursor(0,1);           
    lcd.print("PARK SLOT 1");
    as=1;
    delay(1000);
    }
    else if(ps2 < 1)
    {
    lcd.setCursor(0,1);           
    lcd.print("PARK SLOT 2");
    delay(1000); 
    as =2;
    }
    else
    {
    lcd.setCursor(0,1);           
    lcd.print("NO PARKNG"); 
    }
    }
    else
    {
    lcd.setCursor(0,1);           
    lcd.print("exit wait for bill");
    bill_show2();
    card2=0;
    name2 = "None";
    delay(2000);
    welcome_note();
    }
     }
    else
    {
     Serial.println("no");  
    }
  rfid.remove(0);
  count = 0;
  }
  }
}
void check_parking1()
{
while(rfid2Serial.available() && count < 12)          
    {
    input[count]=rfid2Serial.read();
    count++;
    delay(6);
    //Serial.println(String(input));
    if (count==12)
    {
      Serial.println(String(input));
      count = 0;
      rfid1=input;
      if(rfid1==c1)//tag[count]==input[count])
      {
    Serial.println("HANEESH");
    lcd.setCursor(0,1);           
    lcd.print("SLOT 1 FULL ");
    ps1 = 5;
    name1 = "HANEESH @ PARKING 1";
    }
    else if(rfid1==c2){
    Serial.println("MANISH ");
    lcd.setCursor(0,1);           
    lcd.print("SLOT 1 FULL "); 
    ps1 = 5;
    name1 = "MANISH @ PARKING 1";
     }
    else
    {
     Serial.println("no");  
    }
  rfid1.remove(0);
  count = 0;
  }
  }
}
void check_parking2()
{
while(rfid1Serial.available() && count < 12)          
    {
    input[count]=rfid1Serial.read();
    count++;
    delay(6);
    //Serial.println(String(input));
    if (count==12)
    {
      Serial.println(String(input));
      count = 0;
       rfid2=input;
       if(rfid2==c1)//tag[count]==input[count])
       {
    Serial.println("HANEESH");
    lcd.setCursor(0,1);           
    lcd.print("SLOT 2 FULL ");
    ps2 = 5;
    name2 = "HANEESH @ PARKING 2";
    }
     else if(rfid2==c2){
    Serial.println("HANEESH ");
    lcd.setCursor(0,1);           
    lcd.print("SLOT 2 FULL "); 
    ps2 = 2;
    name2 = "MANISH @ PARKING 2";
     }
    else
    {
     Serial.println("no");  
    }
  rfid2.remove(0);
  count = 0;
  }
  }
}
void welcome_note()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PARKING SLOT");
  lcd.setCursor(0,1);
  lcd.print("........");
  delay(1000);
}
void bill_show1()
{
    price = rs * sec1;
    delay(1000);
    lcd.setCursor(0,0);           
    lcd.print("BILL GENERATED  ");
    lcd.setCursor(0,1);           
    lcd.print("BILL = ");
    lcd.print(price);
    lcd.print("/-     ");
    ps1=0;
}
void bill_show2()
{
    price = rs * sec2;
    delay(1000);
    lcd.setCursor(0,0);           
    lcd.print("BILL GENERATED  ");
    lcd.setCursor(0,1);           
    lcd.print("BILL = ");
    lcd.print(price);
    lcd.print("/-     ");
    ps2 = 0;
}
