#include <SoftwareSerial.h>

SoftwareSerial softSerial(2, 3);

int arrayCounter = 0;
byte liveData[75];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }

  softSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  getData();
  sendDataPC();
}

void getData(){
  softSerial.write(0x6e); //Send 'n' to Speeduino to request live data
  while(!softSerial.available()); //Wait for the serial port to send data

  while (arrayCounter < 75) {
    if (softSerial.available() > 0) {
      liveData[arrayCounter] = softSerial.read();
      if (arrayCounter == 0 && liveData[arrayCounter] != 0x6e) {
        return;
      }
      arrayCounter++;
    }
  }
  
  arrayCounter = 0;
 }

void sendDataPC(){
   while (arrayCounter < 75) {
    if (Serial.availableForWrite() > 0){
      Serial.write(liveData[arrayCounter]);
      arrayCounter++;
    }
    arrayCounter = 0;
  }
}
