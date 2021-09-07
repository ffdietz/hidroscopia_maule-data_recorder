// #include <SD.h>
#include "SdFat.h"
#include <SPI.h>
#include <avdweb_Switch.h>

#define SD_CSPin  10
#define recButton 4

#define FILE_BASE_NAME "HM_"
const uint8_t BASE_NAME_SIZE= sizeof(FILE_BASE_NAME) - 1;
char filename[] = FILE_BASE_NAME "00.txt";

SdFat SD;
SdFile recording_file;

Switch pushButton = Switch(recButton);

#define error(msg) SD.errorHalt(F(msg))
 
void sd_init(){
  // Serial.begin(9600);

  if (!SD.begin(SD_CSPin, SD_SCK_MHZ(50)))  SD.initErrorHalt();

  if(BASE_NAME_SIZE > 6)  error("FILE_BASE_NAME too long");

  while (SD.exists(filename)) {
    if (filename[BASE_NAME_SIZE + 1] != '9') filename[BASE_NAME_SIZE + 1]++;
    else if (filename[BASE_NAME_SIZE] != '9') {
      filename[BASE_NAME_SIZE + 1] = '0';
      filename[BASE_NAME_SIZE]++;
    } else  error("Can't create file name");
  }
  if (!recording_file.open(filename, O_WRONLY | O_CREAT | O_EXCL)) {
    error("file.open");
  }
}

void sd_write(uint16_t input_write){
  // file = sd.open(filename, FILE_WRITE);
  if (recording_file) recording_file.println(input_write);
}

void sd_stop(){  
    recording_file.close(); 
}

void sd_test(){
  if(millis() < 50000){
     if (recording_file) {
        Serial.println("Writing to test.txt...");
        recording_file.println(analogRead(0));
      }
  }
  else {
    Serial.println("done");
        recording_file.close();
  }
}



//https://www.e-tinkers.com/2021/05/the-simplest-button-debounce-solution/