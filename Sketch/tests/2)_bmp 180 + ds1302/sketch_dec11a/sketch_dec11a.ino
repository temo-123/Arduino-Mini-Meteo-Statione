#include <DS1302.h>
#include <Wire.h> 
#include <BMP085.h>

DS1302 rtc(2, 3, 4);
BMP085 dps = BMP085(); 

long Temperature = 0, Pressure = 0;

void setup()
{

  Serial.begin(9600); 
  Wire.begin(); 
  delay(1000);
  dps.init();  
  
  rtc.halt(false);
  rtc.writeProtect(false);

  Serial.begin(9600);

  rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(01, 33, 00);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(11, 12, 2016);   // Set the date to August 6th, 2010
}


void loop(void) { 
  dps.getPressure(&Pressure); 
  dps.getTemperature(&Temperature);

  Serial.print("Pressure(mm Hg):"); 
  Serial.print(Pressure/133.3);      //Выводим давление в мм.рт ст
  Serial.print("Temp:"); 
  Serial.println(Temperature*0.1);   // Температуру в градусах Цельсия
  delay(1000); 
  
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating :)
  delay (1000);
}
