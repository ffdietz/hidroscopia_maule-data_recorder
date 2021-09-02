#include <SD.h>
 
File myFile;
 
void sd_init(){
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(SD_CSPin, OUTPUT);
 
  if (!SD.begin(SD_CSPin)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done."); 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
    myFile = SD.open("hidroscopia.txt", FILE_WRITE);
}


void sd_write(uint16_t input_write){
  if (myFile) {
    myFile.println(input_write);
    myFile.flush();
  }
}

void sd_stop(){  
    myFile.close(); 
}