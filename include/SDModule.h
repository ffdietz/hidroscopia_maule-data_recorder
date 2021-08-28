#include <SD.h>
 
File myFile;
 
void SD_init()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(SDCSPin, OUTPUT);
 
  if (!SD.begin(SDCSPin)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done."); 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

}
 
void SD_update()
{
  if (myFile) {
    Serial.println("Writing to test.txt...");
    myFile.println(analogRead(analogPin));
  }

  if(millis() > 1000){
    Serial.println("done");
        myFile.close();
  }
}