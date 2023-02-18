#include <OLED_I2C.h> 
OLED  myOLED(8, 9, 8); // SDA - 8pin, SCL - 9pin
void setup()
{
  myOLED.begin();
}
void loop()
{
  myOLED.print("hellow world !!!", CENTER, 0);

}
