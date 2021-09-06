// #include <SD.h>
#include "SdFat.h"
#include <SPI.h>
#include <avdweb_Switch.h>

#define SD_CSPin  10
#define recButton 4

#define FILE_BASE_NAME "hidros"

int BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char filename[] = FILE_BASE_NAME "00.txt";
File myFile;

SdFat sd;
SdFile file;

Switch pushButton = Switch(recButton);

#define error(msg) sd.errorHalt(F(msg))
 
void sd_init(){
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[13] = FILE_BASE_NAME "00.txt";

  Serial.begin(9600);
  
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin(SD_CSPin, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }

  // Find an unused file name.
  if (BASE_NAME_SIZE > 6) {
    error("FILE_BASE_NAME too long");
  }
  while (sd.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      error("Can't create file name");
    }
  }
  if (!file.open(fileName, O_WRONLY | O_CREAT | O_EXCL)) {
    error("file.open");
  }
  // Read any Serial data.
 
}

void sd_write(uint16_t input_write){

  // file = sd.open(filename, FILE_WRITE);

  if (file) {  
    file.println(input_write);
  }
}

void sd_stop(){  
    file.close(); 
}

void sd_test(){
  if(millis() < 50000){
     if (myFile) {
        Serial.println("Writing to test.txt...");
        myFile.println(analogRead(0));
      // close the file:
      }
  }
  else {
    Serial.println("done");
        myFile.close();
  }
}



//https://www.e-tinkers.com/2021/05/the-simplest-button-debounce-solution/