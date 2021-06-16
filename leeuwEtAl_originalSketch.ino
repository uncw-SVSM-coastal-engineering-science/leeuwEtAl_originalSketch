// code from Supplementary Info from https://www.mdpi.com/1424-8220/13/6/7872
// Leeuw, Boss, and Wright (2013) In situ Measurements of Phytoplankton Fluorescence Using Low Cost Electronics

#include "SD.h"
#include "Time.h"
int read1;
int read2;
int read3;
int read4;
int read5;
int val;
File myFile;

void setup() {
  
  pinMode(10, OUTPUT); // power up data logger
  
  if (!SD.begin(10)) {
    return;
  }
  
  pinMode(4,OUTPUT); // set LED pin to output
  digitalWrite(4,LOW);
  analogReference(DEFAULT); // will read analog inputs between 0 and 5 volts
  myFile = SD.open("data.txt", FILE_WRITE); // specify name of text file on SD card
  myFile.println("Start"); // prints initializer 'Start' at beginning of file
}

void loop() {
  if (myFile) {
    for (int j = 0; j < 50; j++) { // collect 50 measurements
      delay(510000); // delay until next measurement
      digitalWrite(4,HIGH);
      delay(90000); // allow LED to warm up for 1.5 minutes
      
      for (int x = 0; x < 10; x++) { 
        // collect ten measurements
        read1 = analogRead(0);
        delay(100);
        read2 = analogRead(0);
        delay(100);
        read3 = analogRead(0);
        delay(100);
        read4 = analogRead(0);
        delay(100);
        read5 = analogRead(0);

        // average 5 measurements taken 100ms apart
        val = (read1+read2+read3+read4+read5)/5; 

        // next 28 lines write the date and time to the SD card
        time_t t = now(); 
        
        if(month(t) < 10) {
          myFile.print(0);
        }
        
        myFile.print(month(t));
        myFile.print("/");
        
        if(day(t) < 10) {
          myFile.print(0);
        }
        
        myFile.print(day(t));
        myFile.print("/");
        myFile.print(year(t));
        myFile.print(" ");
        
        if(hour(t) < 10) {
          myFile.print(0);
        }
        
        myFile.print(hour(t));
        myFile.print(":");
        
        if(minute(t) < 10) {
          myFile.print(0);
        }
        
        myFile.print(minute(t));
        myFile.print(":");
        
        if(second(t) < 10) {
          myFile.print(0);
        }
        myFile.print(second(t));
        myFile.print(" @ ");
        myFile.println(val);
      }
      digitalWrite(4,LOW); // turn LED off
    }
  }
  myFile.close(); // closes file
  while(1) { 
    // LED blinks when measurements are done
    digitalWrite(4,HIGH);
    delay(1000);
    digitalWrite(4,LOW);
    delay(2000);
  }
}
