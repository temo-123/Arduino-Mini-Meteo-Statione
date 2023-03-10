#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



https://robotclass.ru/tutorials/arduino_oled/

vcc --- vcc
gnd --- gnd
scl --- D10
sda --- D9
res --- D13
cd  --- D11

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS); // https://robotclass.ru/tutorials/arduino_oled/

#include <DS1302.h>
#include <Wire.h> 
#include <BMP085.h>

DS1302 rtc(2, 3, 4);
BMP085 dps = BMP085(); 

long Temperature = 0, Pressure = 0;

void setup() {

  Serial.begin(9600);
  
  Wire.begin(); 
  dps.init(); 

  rtc.halt(false);
  rtc.writeProtect(false);

  rtc.setTime(01, 33, 00);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(11, 12, 2016);   // Set the date to August 6th, 2010
}

void loop() {
 // ������������� � ������� �������
 display.begin(SSD1306_SWITCHCAPVCC);
 display.clearDisplay();
 display.display();
 
 display.setTextSize(1); // ��������� ������� ������
 display.setTextColor(WHITE); // ��������� ����� ������
 display.setCursor(0,0); // ��������� �������
 
    dps.getPressure(&Pressure); 
    dps.getTemperature(&Temperature);
 
    display.print("(mm Hg):"); 
    display.print(Pressure/133.3);      //������� �������� � ��.�� ��
    display.print("       Temp:"); 
    display.println(Temperature*0.1);   // ����������� � �������� �������

    display.print(rtc.getDOWStr());
    display.print(" ");
    display.print(rtc.getDateStr());
    display.print("    ");
    display.println(rtc.getTimeStr());

 display.display();


  dps.getPressure(&Pressure); 
  dps.getTemperature(&Temperature);
  Serial.print("Pressure(mm Hg):"); 
  Serial.print(Pressure/133.3);      //������� �������� � ��.�� ��
  Serial.print("Temp:"); 
  Serial.println(Temperature*0.1);   // ����������� � �������� �������
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  Serial.println(rtc.getTimeStr());
  delay (1000);
}
